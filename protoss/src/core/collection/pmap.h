// pmap.h
// A set of key value pairs
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PMAP_H
#define PMAP_H

#include "prbtree.h"

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>

template<typename Key, typename Value>
class P_DLLEXPORT PMap
{
public:
    PMap();
    ~PMap();
    PMap(const PMap<Key, Value> &other);
    const PMap<Key, Value> &operator=(const PMap<Key, Value> &other); 

private:
    struct Node
    {
        Key key;
        Value value;

		Node(const Key &k, const Value &v)
			: key(k)
			, value(v)
		{
		}

		bool operator<(const Node &other) const
		{
			return key < other.key;
		}
    };

    PRbTree<Node> m_rbTree;

public:
    class iterator
    {
    public:
        typename PRbTree<Node>::Node *m_i;
        PRbTree<Node>                *m_tree;

        P_INLINE iterator() 
        { m_tree = P_NULL; m_i = P_NULL; }
        P_INLINE iterator(typename PRbTree<Node>::Node *n, PRbTree<Node> *tree)    
        { m_i = n;  m_tree = tree; }
        P_INLINE iterator(const iterator &o)        
        { m_i = o.m_i;  m_tree = o.m_tree; }

        P_INLINE Key &key()           { return m_i->data().key;  }
        P_INLINE Value &value()       { return m_i->data().value; }

        P_INLINE bool operator==(const iterator &o) const { return m_i == o.m_i; }
        P_INLINE bool operator!=(const iterator &o) const { return m_i != o.m_i; }

        P_INLINE void increment()
        {
            pAssertInfo(m_i != P_NULL, "invalid iterator");
            m_i = PRbTree<Node>::Node::findSuccessor(m_i);
        }

        P_INLINE iterator &operator++() 
        {
            pAssertInfo(m_i != P_NULL && m_i != m_tree->getHeader(), 
                "invalid iterator");
            increment();
            return *this;
        }
        P_INLINE iterator operator++(int) 
        {
            pAssertInfo(m_i != P_NULL && m_i != m_tree->getHeader(), 
                "invalid iterator");
            iterator ret(*this);
            increment();
            return ret;
        }
    };

    class const_iterator
    {
    public:
        PRbTree::Node *m_i;
        PRbTree *m_tree;

        P_INLINE const_iterator() 
        { m_tree = P_NULL; m_i = P_NULL; }
        P_INLINE const_iterator(PRbTree::Node *n, PRbTree *tree)    
        { m_i = n;  m_tree = tree; }
        P_INLINE const_iterator(const iterator &o)        
        { m_i = o.m_i;  m_tree = o.m_tree; }

        P_INLINE const Key &key()  const         { return m_i->data().key;  }
        P_INLINE const Value &value() const      { return m_i->data().value; }

        P_INLINE bool operator==(const const_iterator &o) const { return m_i == o.m_i; }
        P_INLINE bool operator!=(const const_iterator &o) const { return m_i != o.m_i; }

        P_INLINE void increment()
        {
            pAssertInfo(m_i != P_NULL, "invalid iterator");
            m_i = PRbTree::Node::findSuccessor(m_i);
        }

        P_INLINE const_iterator &operator++() 
        {
            pAssertInfo(m_i != P_NULL && m_i != m_tree->getHeader(), 
                "invalid const_iterator");
            increament();
            return *this;
        }
        P_INLINE const_iterator operator++(int) 
        {
            pAssertInfo(m_i != P_NULL && m_i != m_tree->getHeader(), 
                "invalid const_iterator");
            const_iterator ret(*this);
            increament();
            return ret;
        }
    };


    P_INLINE iterator begin() 
    { return iterator(m_rbTree.getMin(), &m_rbTree); }
    P_INLINE const_iterator begin() const 
    { return const_iterator(getMin(), &m_rbTree); }
    P_INLINE iterator end() 
    { return iterator(P_NULL, &m_rbTree); }
    P_INLINE const_iterator end() const 
    { return const_iterator(P_NULL, &m_rbTree); }

    iterator insert(const Key &k, const Value &v);
    void erase(iterator iter);
    iterator find(const Key &k);
    const_iterator find(const Key &k) const;
    P_INLINE const Value& operator[](const Key &k) const;
    P_INLINE Value& operator[](const Key &k);

    void clear();

    P_INLINE pUint32 count() const { return m_rbTree.count(); }
    P_INLINE bool isEmpty() const { return m_rbTree.count() == 0; }

    // STL compatible
    P_INLINE bool empty() const { return isEmpty(); }
    P_INLINE pUint32 size() const { return count(); }
    void swap(PMap<Key, Value> &other);
};
    
template<typename Key, typename Value>
PMap<Key, Value>::PMap()
{
}

template<typename Key, typename Value>
PMap<Key, Value>::~PMap()
{
}

template<typename Key, typename Value>
PMap<Key, Value>::PMap(const PMap<Key, Value> &other)
    : m_rbTree<Node>(other.m_rbTree)
{
    
}

template<typename Key, typename Value>
const PMap<Key, Value> &PMap<Key, Value>::operator=(const PMap<Key, Value> &other)
{
    if (this != &other)
    {
        m_rbTree = other.m_rbTree;
    }

    return *this;
}
    
template<typename Key, typename Value>
typename PMap<Key, Value>::iterator PMap<Key, Value>::insert(const Key &k, const Value &v)
{
    Node node(k, v);
	typename PRbTree<Node>::Node *ret = m_rbTree.insert(node);
	return iterator(ret, &m_rbTree);
}

template<typename Key, typename Value>
void PMap<Key, Value>::erase(iterator iter)
{
    m_rbTree.erase(iter.m_i);
}

template<typename Key, typename Value>
typename PMap<Key, Value>::iterator PMap<Key, Value>::find(const Key &k)
{
    Node* n = reinterpret_cast<Node*>(pNewArray(pUint8 [sizeof(Node)]));	
    new (&(n->key)) Key(k);
    PRbTree<Node>::Node *ret = m_rbTree.find(*n);        
    return iterator(ret, &m_rbTree);
}

template<typename Key, typename Value>
typename PMap<Key, Value>::const_iterator PMap<Key, Value>::find(const Key &k) const
{
    Node* n = reinterpret_cast<Node*>(pNewArray(pUint8 [sizeof(Node)]));
    new &(n->k) Key(k);
    PRbTree::Node ret = m_rbTree.find(*n);        
    return const_iterator(ret, m_rbTree);
}

template<typename Key, typename Value>
const Value& PMap<Key, Value>::operator[](const Key &k) const
{
    const_iterator it = find(k);
    pAssert(it != end());
    return it->value();
}

template<typename Key, typename Value>
Value& PMap<Key, Value>::operator[](const Key &k)
{
    iterator it = find(k);
    pAssert(it != end());
    return it.value();
}
    
template<typename Key, typename Value>
void PMap<Key, Value>::swap(PMap<Key, Value> &other)
{
    m_rbTree.swap(other.m_rbTree);
}

#endif // !PMAP_H
