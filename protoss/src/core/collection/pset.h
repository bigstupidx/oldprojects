// pset.h
// A set of unique values.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PSET_H
#define PSET_H

#include "prbtree.h"

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>

// REVIEW+TODO(lihw): move PRbTree's implementation here. 

template<typename T>
class P_DLLEXPORT PSet
{
public:
    PSet();
    ~PSet();
    PSet(const PSet<T> &other);
    const PSet<T> &operator=(const PSet<T> &other); 

private:
    typedef PRbTree<T> pRbTree;
    pRbTree m_rbTree;

public:
    class iterator
    {
    public:
        typename PRbTree<T>::Node *m_i;
        PRbTree<T>                *m_tree;

        P_INLINE iterator() 
        { m_tree = P_NULL; m_i = P_NULL; }
        P_INLINE iterator(typename PRbTree<T>::Node *n, PRbTree<T> *tree)    
        { m_i = n;  m_tree = tree; }
        P_INLINE iterator(const iterator &o)        
        { m_i = o.m_i;  m_tree = o.m_tree; }

        P_INLINE T &operator*() { return m_i->data(); };
        P_INLINE T *operator->() { return &(m_i->data()); };
        P_INLINE bool operator==(const iterator &o) const { return m_i == o.m_i; }
        P_INLINE bool operator!=(const iterator &o) const { return m_i != o.m_i; }

        P_INLINE void increment()
        {
            pAssertInfo(m_i != P_NULL, "invalid iterator");
            m_i = typename PRbTree<T>::Node::findSuccessor(m_i);
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

        P_INLINE const T &operator*() { return m_i->data(); };
        P_INLINE const T *operator->() { return &(m_i->data()); };
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
    { return const_iterator(m_rbTree.getMin(), &m_rbTree); }
    P_INLINE iterator end() 
    { return iterator(P_NULL, &m_rbTree); }
    P_INLINE const_iterator end() const 
    { return const_iterator(P_NULL, &m_rbTree); }

    iterator insert(const T &t);
    void erase(iterator iter);
    iterator find(const T &t);
    const_iterator find(const T &t) const;

    void clear();

    P_INLINE pUint32 count() const { return m_rbTree.count(); }
    P_INLINE bool isEmpty() const { return m_rbTree.count() == 0; }

    // STL compatible
    P_INLINE bool empty() const { return isEmpty(); }
    P_INLINE pUint32 size() const { return count(); }
    void swap(PSet<T> &other);
};

template<typename T>
PSet<T>::PSet()
{
}

template<typename T>
PSet<T>::~PSet()
{
}

template<typename T>
PSet<T>::PSet(const PSet<T> &other)
    : m_rbTree<Node>(other.m_rbTree)
{
    
}

template<typename T>
const PSet<T> &PSet<T>::operator=(const PSet<T> &other)
{
    if (this != &other)
    {
        m_rbTree = other.m_rbTree;
    }

    return *this;
}
    
template<typename T>
typename PSet<T>::iterator PSet<T>::insert(const T &t)
{
    iterator(m_rbTree.insert(t), &m_rbTree);
}

template<typename T>
void PSet<T>::erase(iterator iter)
{
    m_rbTree.erase(iter.m_i);
}

template<typename T>
typename PSet<T>::iterator PSet<T>::find(const T &t)
{
    PRbTree::Node *ret = m_rbTree.find(t);        
    return iterator(ret, m_rbTree);
}

template<typename T>
typename PSet<T>::const_iterator PSet<T>::find(const T &t) const
{
    PRbTree::Node *ret = m_rbTree.find(t);        
    return const_iterator(ret, m_rbTree);
}

template<typename T>
void PSet<T>::swap(PSet<T> &other)
{
    m_rbTree.swap(other.m_rbTree);
}

#endif // !PSET_H
