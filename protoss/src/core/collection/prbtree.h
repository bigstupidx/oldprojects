// prbtree.h
// A red black tree.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Jihao Xu xujihao@cooee.cn and Hongwei Li lihw81@gmail.com
//


#ifndef PRBTREE_H
#define PRBTREE_H

#include <PSystem/pmemory.h>


#define P_RBTREE_IS_VALID_ITERATOR(i) \
    {pAssertInfo(i.m_i != P_NULL, "invalid iterator");}


template<typename T>
class P_DLLEXPORT PRbTree
{
private:
    enum PRbColor
    {
        P_COLOR_RED,
        P_COLOR_BLACK,
    };

public:
    struct Node
    {
        Node        *m_left;
        Node        *m_right;
        Node        *m_parent;
        PRbColor     m_color;
        T            m_data;
        
        T& data() 
        {
            return m_data;
        }

        static Node* findSuccessor(Node *node) 
        {
            Node *ret = P_NULL;

            if (node == P_NULL)
            {
                return P_NULL;
            }

            if (node->m_right == P_NULL)
            {
                ret = node->m_parent;
                while (node == ret->m_right)
                {
                    node = ret;
                    ret = ret->m_parent;
                }
            }
            else
            {
                ret = node->m_right;
                while (ret->m_left != P_NULL)
                {
                    ret = ret->m_left;
                }
            }

            return ret;
        }
    };


    PRbTree();
    ~PRbTree();
    PRbTree(const PRbTree &other);
    const PRbTree &operator=(const PRbTree &other);

    Node* insert(const T &t);
    Node* insertUnique(const T &t);
    void erase(Node *node);

    Node* find(const T &t) const;
	P_INLINE Node *getHeader() const { return m_header; }
    P_INLINE pUint32 count() const { return m_count; }

    void clear();

    P_INLINE Node *getMin() const
    {
        if (m_root == P_NULL)
        {
            return P_NULL;
        }
        Node *ret = m_root;
        while (ret->m_left != P_NULL)
        {
            ret = ret->m_left;
        }
        return ret;
    }
    P_INLINE Node *getMax() const
    {
        if (m_root == P_NULL)
        {
            return P_NULL;
        }
        Node *ret = m_root;
        while (ret->m_right != P_NULL)
        {
            ret = ret->m_right;
        }
        return ret;
    }
    
private:
    Node* insert(Node *parent, const T &t);
    void rebalanceAfterInsert(Node *node);
    void rebalanceAfterErase(Node *node);
    void leftRotate(Node *node);
    void rightRotate(Node *node);
    Node *newNode(const T& key);
	void deleteTree(Node *node);

private:
    pUint32         m_count;
    Node            *m_header; // farther of root and its farther is root.
    Node            *m_root;  
};


template<typename T>
PRbTree<T>::PRbTree()
{
    m_count = 0;

    m_header = reinterpret_cast<Node*>(pNewArray(pUint8 [sizeof(Node)]));

    m_header->m_left = m_header;
    m_header->m_right = m_header;
    m_header->m_parent = m_root;

    m_root = P_NULL;
}

template<typename T>
PRbTree<T>::~PRbTree()
{
	pUint8 *headerData = reinterpret_cast<pUint8*>(m_header);
    pDeleteArray(headerData);
    deleteTree(m_root);
}

template<typename T>
PRbTree<T>::PRbTree(const PRbTree<T> &o)
{
    Node* t = o.getMin();
    while (t != P_NULL)
    {
        insert(t->data());
        t = Node::findSuccessor(t);
    }
}

template<typename T>
const PRbTree<T> &PRbTree<T>::operator=(const PRbTree<T> &o)
{
    if (this != &other)
    {
        Node* t = o.getMin();
        while (t != P_NULL)
        {
            insert(t->data());
            t = Node::findSuccessor(t);
        }
    }

    return *this;
}


template<typename T>
typename PRbTree<T>::Node *PRbTree<T>::insert(const T &t)
{
    Node *parent = m_header;
    Node *insertPos = m_root;

    while (insertPos != P_NULL)
    {
        parent = insertPos;
        if (t < insertPos->m_data)
        {
            insertPos = insertPos->m_left;
        }
        else
        {
            insertPos = insertPos->m_right;
        }
    }

    return insert(parent, t);
}

template<typename T>
typename PRbTree<T>::Node *PRbTree<T>::insertUnique(const T &t)
{
    Node *parent = m_header;
    Node *insertPos = m_root;
    bool isEqual = false;

    while (insertPos != P_NULL)
    {
        parent = insertPos;
        if (t > insertPos->m_data)
        {
            insertPos = insertPos->m_right;
        }
        else if (t < insertPos->m_data)
        {
            insertPos = insertPos->m_left;
        }
        else
        {
            return end();
        }
    }

    return insert(parent, t);
}

template<typename T>
typename PRbTree<T>::Node *PRbTree<T>::insert(Node *parent, const T &t)
{
    typename PRbTree<T>::Node *node = newNode(t);
    if (parent == m_header)
    {
        node->m_parent = parent;
        node->m_color = P_COLOR_BLACK;

        m_root = node;
        m_header->m_parent = m_root;
    }
    else
    {
        if (t < parent->m_data)
        {
            Node *oldLeft = parent->m_left;
            parent->m_left = node;
            node->m_left = oldLeft;
        }
        else
        {
            Node *oldRight = parent->m_right;
            parent->m_right = node;
            node->m_right = oldRight;			
        }
    }

    ++m_count;

    rebalanceAfterInsert(node);

    return node;
}

// FIXME+DONE(lihw): the algoirthm is revised according to 
// http://zh.wikipedia.org/wiki/%E7%BA%A2%E9%BB%91%E6%A0%91
template<typename T>
void PRbTree<T>::rebalanceAfterInsert(Node *node)
{
    // REVIEW+DONE(lihw): add three macros to increase code readability.
#define PARENT(node) (node->m_parent)
#define GRANDPARENT(node) (node->m_parent->m_parent)

    while (node != m_root && PARENT(node)->m_color == P_COLOR_RED)
    {  
        if (PARENT(node) == GRANDPARENT(node)->m_left)
        {  
            Node *uncle = GRANDPARENT(node)->m_right;
            if (uncle != P_NULL && uncle->m_color == P_COLOR_RED)
            {  
                // Flip the colors of two children of grandparent.
                // We does not change the number of black nodes after flipping
                // and thus ensure the crteria 4 of red-black tree. We can assure
                // uncle's children must be not be black otherwise it is break
                // criteria 3 before flipping.
                PARENT(node)->m_color = P_COLOR_BLACK;
                uncle->m_color = P_COLOR_BLACK;          
                GRANDPARENT(node)->m_color = P_COLOR_RED; 
                node = GRANDPARENT(node);
            }  
            else // No uncle or uncle is black
            {  
                if (node == PARENT(node)->m_right)
                {  
                    leftRotate(node->m_parent);
                    node = node->m_left;
                }  
                PARENT(node)->m_color = P_COLOR_BLACK;
                GRANDPARENT(node)->m_color = P_COLOR_RED;  
                rightRotate(GRANDPARENT(node));
            }  
        }  
        else // Mirror reflection.
        {  
            Node *uncle = GRANDPARENT(node)->m_left;
            if (uncle != P_NULL && uncle->m_color == P_COLOR_RED)
            {  
                PARENT(node)->m_color = P_COLOR_BLACK;
                uncle->m_color = P_COLOR_BLACK;          
                GRANDPARENT(node)->m_color = P_COLOR_RED;
                node = GRANDPARENT(node);
            }  
            else
            {  
                if (node == PARENT(node)->m_left)
                {  
                    rightRotate(PARENT(node));
                    node = node->m_right;  
                }  
                PARENT(node)->m_color = P_COLOR_BLACK;
                GRANDPARENT(node)->m_color = P_COLOR_RED;  
                leftRotate(GRANDPARENT(node));
            }  
        }  
    }

    m_root->m_color = P_COLOR_BLACK;

#undef PARENT
#undef GRANDPARENT
}


// FIXME+DONE(lihw): added illustration and revised the implemenation.
//         +---+                          +---+
//         | Q |                          | P |
//         +---+                          +---+
//        /     \     right rotation     /     \
//     +---+   +---+  ------------->  +---+   +---+
//     | P |   | Z |                  | X |   | Q |
//     +---+   +---+  <-------------  +---+   +---+
//    /     \          left rotation         /     \
// +---+   +---+                          +---+   +---+
// | X |   | Y |                          | Y |   | Z |
// +---+   +---+                          +---+   +---+

template<typename T>
void PRbTree<T>::leftRotate(Node *p)
{  
    // Swap the position p and q.
    Node *q = p->m_right;
    if (q == P_NULL)
    {
        return ;
    }

    if (p == m_root)
    {
        m_root = q;  
    }
    else if (p == p->m_parent->m_left)
    {
        p->m_parent->m_left = q;  
    }
    else
    {
        p->m_parent->m_right = q;  
    }

    q->m_parent = p->m_parent;
    p->m_parent = q;
    
    // Move y from q to p.
    Node *y = q->m_left;
    q->m_left = p;
    
    p->m_right = y;
    if (y != P_NULL)
    {
        y->m_parent = p;
    }
}  


// FIXME+DONE(lihw): revised the implemenation.
template<typename T>
void PRbTree<T>::rightRotate(Node *q)  
{  
    Node *p = q->m_left;
    if (p == P_NULL)
    {
        return ;
    }
    
    // Swap the q and p
    if (q == m_root)
    {
        m_root = p;  
    }
    else if (q== q->m_parent->m_right)
    {
        q->m_parent->m_right = p;
    }
    else
    {
        q->m_parent->m_left = p;  
    }
    p->m_parent = q->m_parent;
    q->m_parent = p;

    // Move x from p to q.
    Node *y = p->m_right;
    p->m_right = q;

    q->m_left = y;
    if (y != P_NULL)
    {
        y->m_parent = q;
    }
}  

template<typename T>
typename PRbTree<T>::Node *PRbTree<T>::find(const T &t) const
{
    Node *result = m_root;

    while (result != P_NULL)
    {
        if (result->m_data < t)
        {
            result = result->m_right;
        }
        else if (t < result->m_data)
        {
            result = result->m_left;
        }
        else
        {
            return result;
        }
    }
    
    return P_NULL;
}

template<typename T>
void PRbTree<T>::erase(Node *node)
{
    pAssert(node != P_NULL);
    
    // When this node has two children, replace this node with the smallest
    // node in its right subtree.
    if (node->m_left != P_NULL && node->m_right != P_NULL)
    {
        Node *succesor = Node::findSuccessor(node);
        node->m_key = succesor->m_key;
        node->m_value = succesor->m_value;

        node = succesor;
    }

    Node *balanceNode = P_NULL;
    Node *node = iter.m_i;
    if (node->m_right != P_NULL)
    {
        if (node->m_parent->m_left == node)
        {
            node->m_parent->m_left = node->m_right;
        }
        else
        {
            node->m_parent->m_right = node->m_right;
        }
        node->m_right->m_parent = node->m_parent;
        balanceNode = node->m_right;
    }    
    else if (node->m_left != P_NULL)
    {
        if (node->m_parent->m_left == node)
        {
            node->m_parent->m_left = node->m_left;
        }
        else
        {
            node->m_parent->m_right = node->m_left;
        }
        node->m_left->m_parent = node->m_parent;
        balanceNode = node->m_left;
    }
    

    if ((node->m_left != P_NULL || node->m_right != P_NULL) &&
        node->m_color == P_COLOR_BLACK)
    {
        rebalanceAfterErase(balanceNode);
    }
    
    pDelete(node);

    --m_count;
}

template<typename T>
void PRbTree<T>::rebalanceAfterErase(Node *node)
{
    while (node != m_root && node->m_color == P_COLOR_BLACK)    
    {    
        if (node == node->m_parent->m_left)    
        {    
            Node *brother = node->m_parent->m_right;    
            if (brother->m_color == P_COLOR_RED)
            {    
                leftRotate(node->m_parent);    
                brother->m_color = P_COLOR_BLACK;    
                node->m_parent->m_color = P_COLOR_RED;    
            }    
            else
            {    
                if (brother->m_left->m_color == P_COLOR_BLACK && 
                    brother->m_right->m_color == P_COLOR_BLACK)
                {    
                    brother->m_color = P_COLOR_RED;    
                    node = node->m_parent;    
                }    
                else  
                {  
                    if (brother->m_right->m_color == P_COLOR_BLACK)
                    {  
                        brother->m_color = P_COLOR_RED;  
                        brother->m_left->m_color = P_COLOR_BLACK;  
                        rightRotate(brother);  
                        brother = node->m_parent->m_right;
                    }  
                  
                    brother->m_color = node->m_parent->m_color;    
                    node->m_parent->m_color = P_COLOR_BLACK;    
                    brother->m_right->m_color = P_COLOR_BLACK;
                    leftRotate(node->m_parent);    
                    node = m_root;  
                } 
            }
        }    
        else
        {    
            Node *brother = node->m_parent->m_left;    
            if (brother->m_color == P_COLOR_RED)    
            {    
                brother->m_color = P_COLOR_BLACK;    
                node->m_parent->m_color = P_COLOR_RED;    
                rightRotate(node->m_parent);    
            }    
            else    
            {    
                if (brother->m_left->m_color==P_COLOR_BLACK && 
                    brother->m_right->m_color == P_COLOR_BLACK)    
                {    
                    brother->m_color = P_COLOR_RED;    
                    node = node->m_parent;    
                }    
                else  
                {  
                    if (brother->m_left->m_color==P_COLOR_BLACK)    
                    {    
                        brother->m_color = P_COLOR_RED;    
                        brother->m_right->m_color = P_COLOR_BLACK;    
                        leftRotate(brother);  
                        brother = node->m_parent->m_left;
                    }  
                    brother->m_color = node->m_parent->m_color;    
                    node->m_parent->m_color = P_COLOR_BLACK;    
                    brother->m_left->m_color = P_COLOR_BLACK;    
                    rightRotate(node->m_parent);    
                    node = m_root;    
                }    
            }    
        }    
    }
    node->m_color = P_COLOR_BLACK;
}

template<typename T>
void PRbTree<T>::clear()
{
    if (m_root != P_NULL)
    {
        deleteTree(m_root);
    }
    
    m_count = 0;
}

template<typename T>
void PRbTree<T>::deleteTree(Node *node)
{
    if (node->m_left != P_NULL)
    {
        deleteTree(node->m_left);
    }

    if (node->m_right != P_NULL)
    {
        deleteTree(node->m_right);
    }

    pDelete(node);
}
    
template <typename T>
typename PRbTree<T>::Node *PRbTree<T>::newNode(const T &t)
{
    Node* n = reinterpret_cast<Node*>(pNew(pUint8 [sizeof(Node)]));
    if (PTypeInfo<T>::isComplex)
    {
        new (&(n->m_data)) T(t);
    }
    else
    {
        n->m_data = t;
    }

    n->m_left = P_NULL;
    n->m_right = P_NULL;
    n->m_color = P_COLOR_RED;
    n->m_parent = P_NULL;

    return n;
}

#endif // !PRBTREE_H
