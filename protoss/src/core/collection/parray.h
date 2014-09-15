// parray.h
// Dynamic array implementation in C++ template. 
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PARRAY_H
#define PARRAY_H

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>
#include <PSystem/pcrt.h>

template <typename T>
struct PArrayData 
{ 
    pInt32  m_capacity;     // The size of the pool in number of T
    pInt32  m_size;         // The number of T in the array.
    T*      m_data;
    pInt32  m_threshold[2]; // The reallocation threshold (downsize and upsize)

    T* alloc(pInt32 size);
    void release(T* p);
    void realloc(pInt32 increase);

    static const pInt32 m_initialDataCapacity = 32;
};

template <typename T>
class P_DLLEXPORT PArray
{
    friend class iterator;
    friend class const_iterator;

public:
    PArray();
    PArray(pUint32 size);
    PArray(const T& t, pUint32 size);
    PArray(const PArray<T>& o);
    ~PArray();

    class iterator 
    {
    public:
        T* m_ptr;

        typedef T  value_type;
        typedef T* pointer;
        typedef T& reference;

        P_INLINE iterator()                  : m_ptr(P_NULL) {}
        P_INLINE iterator(T* n)              : m_ptr(n)       {}
        P_INLINE iterator(const iterator& o) : m_ptr(o.m_ptr)  {}

        P_INLINE T& operator*() const                { return *m_ptr;            }
        P_INLINE T* operator->() const               { return m_ptr;             }
        P_INLINE T& operator[](pInt32 offset) const { return *(m_ptr + offset); }

        P_INLINE bool operator==(const iterator& o) const { return m_ptr == o.m_ptr; }
        P_INLINE bool operator!=(const iterator& o) const { return m_ptr != o.m_ptr; }
        P_INLINE bool operator< (const iterator& o) const { return m_ptr < o.m_ptr;  }
        P_INLINE bool operator<=(const iterator& o) const { return m_ptr <= o.m_ptr; }
        P_INLINE bool operator> (const iterator& o) const { return m_ptr > o.m_ptr;  }
        P_INLINE bool operator>=(const iterator& o) const { return m_ptr >= o.m_ptr; }
    
        P_INLINE iterator& operator++()                     { ++m_ptr; return *this;                }
        P_INLINE iterator  operator++(pInt32)              { T* n = m_ptr; ++m_ptr; return n;       }
        P_INLINE iterator& operator--()                     { m_ptr--; return *this;                }
        P_INLINE iterator  operator--(pInt32)              { T* n = m_ptr; m_ptr--; return n;       }
        P_INLINE iterator& operator+=(pInt32 offset)       { m_ptr += offset; return *this;        }
        P_INLINE iterator& operator-=(pInt32 offset)       { m_ptr -= offset; return *this;        }
        P_INLINE iterator  operator+ (pInt32 offset) const { return iterator(m_ptr + offset);      }
        P_INLINE iterator  operator- (pInt32 offset) const { return iterator(m_ptr - offset);      }
        P_INLINE pInt32   operator-(iterator o)      const { return m_ptr - o.m_ptr;                }
    };

    class const_iterator 
    {
    public:
        T* m_ptr;

        typedef T  value_type;
        typedef T* pointer;
        typedef T& reference;

        P_INLINE const_iterator()                        : m_ptr(P_NULL) {}
        P_INLINE const_iterator(T* n)                    : m_ptr(n)       {}
        P_INLINE const_iterator(const const_iterator& o) : m_ptr(o.m_ptr)  {}

        P_INLINE const T& operator*() const                { return *m_ptr;            }
        P_INLINE const T* operator->() const               { return m_ptr;             }
        P_INLINE const T& operator[](pInt32 offset) const { return *(m_ptr + offset); }

        P_INLINE bool operator==(const const_iterator& o) const { return m_ptr == o.m_ptr; }
        P_INLINE bool operator!=(const const_iterator& o) const { return m_ptr != o.m_ptr; }
        P_INLINE bool operator< (const const_iterator& o) const { return m_ptr < o.m_ptr;  }
        P_INLINE bool operator<=(const const_iterator& o) const { return m_ptr <= o.m_ptr; }
        P_INLINE bool operator> (const const_iterator& o) const { return m_ptr > o.m_ptr;  }
        P_INLINE bool operator>=(const const_iterator& o) const { return m_ptr >= o.m_ptr; }
    
        P_INLINE const_iterator& operator++()                      { ++m_ptr; return *this;                 }
        P_INLINE const_iterator  operator++(pInt32)               { T* n = m_ptr; ++m_ptr; return n;        }
        P_INLINE const_iterator& operator--()                      { m_ptr--; return *this;                 }
        P_INLINE const_iterator  operator--(pInt32)               { T* n = m_ptr; m_ptr--; return n;        }
        P_INLINE const_iterator& operator+=(pInt32 offset)        { m_ptr += offset; return *this;         }
        P_INLINE const_iterator& operator-=(pInt32 offset)        { m_ptr -= offset; return *this;         }
        P_INLINE const_iterator  operator+ (pInt32 offset)  const { return const_iterator(m_ptr + offset); }
        P_INLINE const_iterator  operator- (pInt32 offset)  const { return const_iterator(m_ptr - offset); }
        P_INLINE pInt32         operator-(const_iterator o) const { return m_ptr - o.m_ptr;                 }
    };

    P_INLINE iterator       begin()       { return m_p.m_data; }
    P_INLINE const_iterator begin() const { return m_p.m_data; }
    P_INLINE iterator       end()         { return m_p.m_data + m_p.m_size; }
    P_INLINE const_iterator end()   const { return m_p.m_data + m_p.m_size; }

    iterator insert(iterator before, pInt32 n, const T& item);
    P_INLINE iterator insert(iterator before, const T& item)  { return insert(before, 1, item); }
    iterator erase(iterator begin, iterator end);    
    P_INLINE iterator erase(iterator pos)                     { return erase(pos, pos + 1); }

    P_INLINE T&       first()       {pAssertInfo(!isEmpty(), "empty array"); return *begin();     }
    P_INLINE const T& first() const {pAssertInfo(!isEmpty(), "empty array"); return *begin();     }
    P_INLINE T&       last()        {pAssertInfo(!isEmpty(), "empty array"); return *(end() - 1); }
    P_INLINE const T& last()  const {pAssertInfo(!isEmpty(), "empty array"); return *(end() - 1); }

    P_INLINE pUint32 count() const                                { return m_p.m_size;                      } 
    P_INLINE void prepend(const T& t)                              { insert(begin(), 1, t);                }
    P_INLINE void insert(pUint32 i, const T& t)                   { insert(begin() + i, 1, t);            }
    P_INLINE void insert(pUint32 i, pUint32 n, const T& t)       { insert(begin() + i, n, t);            }
    P_INLINE void remove(pUint32 i, pUint32 n)                   { erase(begin() + i, begin() + i + n);  }
    P_INLINE void remove(pUint32 i)                               { erase(begin() + i);                   }
    T& operator[](pUint32 i)                                       { return value(i);                      }
    const T& operator[](pUint32 i) const                           { return value(i);                      }
    P_INLINE bool isEmpty() const                                  { return count() == 0;                  }
    P_INLINE pUint32 count(const T& t) const;
    void append(const T& t);

    pUint32 find(const T& t, pUint32 from = 0) const; 
    pUint32 reverseFind(const T& t, pInt32 from = -1) const;
    bool contains(const T& t) const;

    void clear();
    void reserve(pInt32 size);
    void fill(const T& t);
    void resize(pInt32 size);

    T& value(pUint32 i);
    const T& value(pUint32 i) const;

    // STL compatibility.
    P_INLINE void     push_back(const T& t)  { append(t);                                                  }
    P_INLINE void     push_front(const T& t) { prepend(t);                                                 }
    P_INLINE void     pop_back()             { pAssertInfo(!isEmpty(), "empty array"); erase(end() - 1);  }
    P_INLINE void     pop_front()            { pAssertInfo(!isEmpty(), "empty array"); erase(begin());    }
    P_INLINE bool     empty() const          { return isEmpty();                                           }
    P_INLINE T&       front()                { return first();                                             }
    P_INLINE const T& front() const          { return first();                                             }
    P_INLINE T&       back()                 { return last();                                              }
    P_INLINE const T& back() const           { return last();                                              }
    void               swap(PArray<T>& o);
    pUint32           size() const           { return count();                                             }
    
    const PArray<T>&     operator=  (const PArray<T>& o);
    PArray<T>&           operator+= (const PArray<T>& l);
    PArray<T>            operator+  (const PArray<T>& l) const { PArray n = *this; n += l; return n; }
    P_INLINE PArray<T>& operator+= (const T& t)                { append(t); return *this;             }
    P_INLINE PArray<T>& operator<< (const T& t)                { append(t); return *this;             }
    P_INLINE PArray<T>& operator<< (const PArray<T>& l)       { *this += l; return *this;            }

private:
    PArrayData<T> m_p; 
};
 

template<typename T>
PArray<T>::PArray()
{
    m_p.m_data         = P_NULL;
    m_p.m_size         = 0;
    m_p.m_capacity     = 0;
    m_p.m_threshold[0] = 0;
    m_p.m_threshold[1] = 0;
}

template<typename T>
PArray<T>::PArray(pUint32 size)
{
    m_p.m_data         = P_NULL;
    m_p.m_size         = 0;
    m_p.m_capacity     = 0;
    m_p.m_threshold[0] = 0;
    m_p.m_threshold[1] = 0;

    m_p.realloc(size);

    m_p.m_size = size;
}

template<typename T>
PArray<T>::PArray(const T& t, pUint32 size)
{
    m_p.m_data         = P_NULL;
    m_p.m_size         = 0;
    m_p.m_capacity     = 0;
    m_p.m_threshold[0] = 0;
    m_p.m_threshold[1] = 0;

    m_p.realloc(size);

    if (PTypeInfo<T>::isComplex)
    {
        for (pUint32 i = 0; i < size; ++i)
        {
            new (m_p.m_data + i) T(t);
        }
    }
    else
    {
        for (pUint32 i = 0; i < size; ++i)
        {
            m_p.m_data[i] = t;
        }
    }

    m_p.m_size = size;
}

template<typename T>
PArray<T>::PArray(const PArray<T>& o)
{
    m_p.m_data         = P_NULL;
    m_p.m_size         = 0;
    m_p.m_capacity     = 0;
    m_p.m_threshold[0] = 0;
    m_p.m_threshold[1] = 0;

    pInt32 increase = o.m_p.m_size; 
    m_p.realloc(increase);

    if (PTypeInfo<T>::isComplex)
    {
        for (pInt32 i = 0; i < o.m_p.m_size; i++)
        {
            new (m_p.m_data + i) T(o[i]);
        }
    }
    else
    {
        for (pInt32 i = 0; i < o.m_p.m_size; i++)
        {
            m_p.m_data[i] = o.m_p.m_data[i];
        }
    }

    m_p.m_size += increase;
}

template<typename T>
PArray<T>::~PArray()
{
    T* i = m_p.m_data;
    T* j = m_p.m_data + m_p.m_size;
    while (i != j) 
    {
        ++i;
        i->~T();
    }
    m_p.release(m_p.m_data);
}

template<typename T>
typename PArray<T>::iterator PArray<T>::insert(iterator before, pInt32 n, const T& item)
{
    if (n > 0)
    {
        pInt32 offset = before - m_p.m_data;
        m_p.realloc(n);

        const T copy(item);

        if (PTypeInfo<T>::isComplex)
        {
            T* b = m_p.m_data + m_p.m_size;
            T* i = m_p.m_data + m_p.m_size + n;
            while (i != b)
            {
                new (--i) T;
            }

            i = m_p.m_data + m_p.m_size;
            T* j = i + n;
            b = m_p.m_data + offset;
            while (i != b)
            {
                *--j = *--i;
            }
            
            i = b + n;
            while (i != b)
            {
                *--i = copy;
            }
        }
        else
        {
            T* b = m_p.m_data + offset;
            T* i = b + n;
            pSystem_memcpy(i, b, (m_p.m_size - offset) * sizeof(T));
            while (i != b)
            {
                *(--i) = item;
            }
        }
        m_p.m_size += n;
        return m_p.m_data + offset;
    }
    else if (n < 0)
    {
        pAssertInfo(n >= 0, "invalid element number");
    }

    return m_p.m_data;     
}

template<typename T>
typename PArray<T>::iterator PArray<T>::erase(iterator begin, iterator end)
{
    pInt32 h = pInt32(begin - m_p.m_data);
    pInt32 t = pInt32(end - m_p.m_data);
    pInt32 n = t - h;

    pAssertInfo(h < m_p.m_size && t <= m_p.m_size, "index out of array range");
    
    if (PTypeInfo<T>::isComplex) 
    {
        T* i;
        T* j;
        T* k;
        i = m_p.m_data + t;
        j = m_p.m_data + h;
        k = m_p.m_data + m_p.m_size;
        while (i < k)
        {
            *j++ = *i++;
        } 

        i = m_p.m_data + m_p.m_size;
        j = m_p.m_data + m_p.m_size - n;
        while (i != j) 
        {
            --i;
            i->~T();
        }
    } 
    else 
    {
        pmemcpy(m_p.m_data + h, m_p.m_data + t, (m_p.m_size - t) * sizeof(T));
    }

    m_p.realloc(-n);

    m_p.m_size -= n;

    return m_p.m_data + h;
}
    
template<typename T>
void PArray<T>::append(const T& t)
{
    m_p.realloc(1);

    if (PTypeInfo<T>::isComplex)
    {
        new (m_p.m_data + m_p.m_size) T(t);
    }
    else
    {
        m_p.m_data[m_p.m_size] = t;
    }
    ++m_p.m_size;
}

template<typename T>
pUint32 PArray<T>::find(const T& t, pUint32 from) const
{
    pAssertInfo(from < pUint32(m_p.m_size), "index out of array range");
    T* i = m_p.m_data + from;
    T* e = m_p.m_data + m_p.m_size;
    while (i != e)
    {
        if (*i == t)
        {
            return pUint32(i - m_p.m_data);
        }
        ++i;
    }

    return m_p.m_size;
}

template<typename T>
pUint32 PArray<T>::reverseFind(const T& t, pInt32 from) const
{
    pAssertInfo(from < -m_p.m_size, "index out of array range");
    const T* i = m_p.m_data + m_p.m_size + from;
    const T* e = m_p.m_data; 
    while (i != e)
    {
        if (*i == t)
        {
            return pUint32(i - m_p.m_data);
        }
        --i;
    }

    return m_p.m_size;
}

template<typename T>
bool PArray<T>::contains(const T& t) const
{
    const T* i = m_p.m_data;
    const T* e = m_p.m_data + m_p.m_size; 
    while (i != e)
    {
        if (*i == t)
        {
            return true;
        }
        ++i;
    }

    return false;
}

template<typename T>
pUint32 PArray<T>::count(const T& t) const
{
    pUint32 c = 0;
    T* i = m_p.m_data;
    T* e = m_p.m_data + m_p.m_size; 
    while (i != e)
    {
        if (*i == t)
        {
            ++c;
        }
        ++i;
    }

    return c;
}

template<typename T>
void PArray<T>::clear()
{
    if (PTypeInfo<T>::isComplex)
    {
        for (pInt32 i = 0; i < m_p.m_size; ++i)
        {
            m_p.m_data[i].~T();
        }
    }

    m_p.realloc(-m_p.m_size);
    m_p.m_size = 0;
}

template<typename T>
void PArray<T>::reserve(pInt32 size)
{
    pInt32 increase = pMax(size, m_p.m_capacity) - m_p.m_capacity;
    m_p.realloc(increase);
}

template<typename T>
void PArray<T>::resize(pInt32 size)
{
    pAssertInfo(size >= 0, "invalid array size");
    pInt32 increase = size - m_p.m_size;
    if (increase > 0)
    {
        m_p.realloc(increase);
        
        if (PTypeInfo<T>::isComplex)
        {
            T* b = m_p.m_data + m_p.m_size;
            T* i = m_p.m_data + m_p.m_size + increase;
            while (i != b)
            {
                new (--i) T;
            }
        }
        else
        {
            pSystem_memset(m_p.m_data + m_p.m_size, 0, sizeof(T) * increase);
        }
        m_p.m_size += increase;
    }
    else if (increase < 0)
    {
        for (pInt32 i = size; i < m_p.m_size; ++i)
        {
            m_p.m_data[i].~T();
        }
        m_p.m_size = size;
    }
}

template<typename T>
void PArray<T>::fill(const T& t)
{
    const T copy(t);
    T* b = m_p.m_data;
    T* i = m_p.m_data + m_p.m_size;

    while (i != b)
    {
        new (--i) T(copy);
    }
    
}
    
template<typename T>
T& PArray<T>::value(pUint32 i)
{
    pAssertInfo(i < pUint32(m_p.m_size), "index out of array range");
    return m_p.m_data[i];
}

template<typename T>
const T& PArray<T>::value(pUint32 i) const
{
    pAssertInfo(i < pUint32(m_p.m_size), "index out of array range");
    return m_p.m_data[i];
}
    
template<typename T>
const PArray<T>& PArray<T>::operator=(const PArray<T> &o)
{
    if (&o != this)
    {
        pInt32 increase = m_p.m_size - o.m_p.m_size; 
        m_p.realloc(increase);

        if (PTypeInfo<T>::isComplex)
        {
            for (pInt32 i = 0; i < o.m_p.m_size; i++)
            {
                new (m_p.m_data + i) T(o[i]);
            }
        }
        else
        {
            for (pInt32 i = 0; i < o.m_p.m_size; i++)
            {
                m_p.m_data[i] = o.m_p.m_data[i];
            }
        }

        m_p.m_size += increase;
    }
    return *this;
}

template<typename T>
PArray<T>& PArray<T>::operator+=(const PArray<T>& l)
{
    pInt32 increase = l.m_p.m_size; 
    m_p.realloc(increase);

    if (PTypeInfo<T>::isComplex)
    {
        for (pInt32 i = 0; i < l.m_p.m_size; i++)
        {
            new (m_p.m_data + m_p.m_size + i) T(l[i]);
        }
    }
    else
    {
        for (pInt32 i = 0; i < l.m_p.m_size; i++)
        {
            m_p.m_data[m_p.m_size + i] = l.m_p.m_data[i];
        }
    }

    m_p.m_size += increase;
}
    
template<typename T>
void PArray<T>::swap(PArray<T>& o)
{
    if (&o != this)
    {
        pSwap(m_p.m_data, o.m_p.m_data);
        pSwap(m_p.m_capacity, o.m_p.m_capacity);
        pSwap(m_p.m_size, o.m_p.m_size);
        pSwap(m_p.m_threshold[0], o.m_p.m_threshold[0]);
        pSwap(m_p.m_threshold[1], o.m_p.m_threshold[1]);
    }
}
    
template<typename T>
void PArrayData<T>::realloc(pInt32 increase)
{
    if (increase == 0)
    {
        return ;
    }

    pInt32 newSize = m_size + increase;
    pAssertInfo(newSize >= 0, "invalid array new size");
    if (newSize <= 0)
    {
        return ;
    }

    pInt32 newCapacity = 0;

    if ((increase > 0 && newSize < m_threshold[1]) ||
        (increase < 0 && newSize > m_threshold[0]))
    {
        return ;
    }
    else if (increase > 0 && newSize >= m_threshold[1])
    {
        if (m_capacity == 0)
        {
            newCapacity = pMax(m_initialDataCapacity, newSize);
        }
        else
        {
            newCapacity = newSize * 3 / 2; // 0.5 times more.
            if (newCapacity - newSize > 128)
            {
                newCapacity = newSize + 128;
            }
        }
    }
    else if (increase < 0 && newSize <= m_threshold[0])
    {
        newCapacity = pMax(newSize, m_capacity / 2); 
        if (newCapacity < m_initialDataCapacity)
        {
            newCapacity = m_initialDataCapacity;
        }
    }
    else
    {
        pAssertNotReachable();
    }

    pAssert(newCapacity > 0 && newSize <= newCapacity);

    // Allocate the memory for the resized table.
    T* newData = alloc(newCapacity);

    // Copy the content to the new array.
    if (m_size != 0)
    {
        pmemcpy(newData, m_data, newSize * sizeof(T));
    }

    m_capacity = newCapacity;
    release(m_data);
    
    m_data = newData;
    
    m_threshold[0] = m_capacity / 4;
    m_threshold[1] = m_capacity * 7 / 8;
}

template<typename T>
T* PArrayData<T>::alloc(pInt32 size)
{
    pUint8* p = pNewArray(pUint8 [size * sizeof(T)]);
    return reinterpret_cast<T*>(p);
}

template<typename T>
void PArrayData<T>::release(T* p)
{
    pUint8* d = reinterpret_cast<pUint8*>(p);
    pDeleteArray(d);
}


#endif // !PARRAY_H
