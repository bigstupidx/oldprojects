// pstring.h
// Ascii string in C++.
//
// Copyright 2012 by Hongwei Li. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PSTRING_H
#define PSTRING_H

#include <PCore/parray.h>

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>

class P_DLLEXPORT PString
{
public:
    P_INLINE PString() { m_s = P_NULL; m_l = 0; }
    explicit PString(const PArray<pChar>& o);
    explicit PString(const pChar* o, pInt32 l = -1);
    PString(const PString& o);
    explicit PString(pUint32 l);
    PString(pChar c, pUint32 n);

    ~PString();

    P_INLINE const pChar* data() const { return m_s; }
    P_INLINE pChar* data() {return m_s; }
    P_INLINE pUint32 length() const { return m_l; }
    P_INLINE bool empty() const { return m_l == 0; }

    PString left(pUint32 n) const;
    PString right(pUint32 n) const;
    PString mid(pUint32 position, pInt32 n = -1) const;
    
    void insert(pChar* before, pChar* str, pInt32 length = -1);
    void insert(pChar* before, const PString& str);

    pInt32 find(pChar c) const; // return -1 if not found
    pInt32 find(const PString& str) const; // return -1 if not found
    pInt32 find(const char* str) const; // return -1 if not found.

    pInt32 rfind(pChar c) const;
    pInt32 rfind(const PString& str) const;
    pInt32 rfind(const char* str) const;
    
    void append(const pChar* str, pInt32 length = -1); // length = -1 when it is a c string.
    void append(const PString& str); // length = -1 when it is a c string.
    void prepend(const pChar* str, pInt32 length = -1); // length = -1 when it is a c string.
    void prepend(const PString& str); 

    bool isEqual(const pChar* str, pInt32 length = -1) const;
    P_INLINE bool isEqual(const PString& str) const
    { return m_l == str.m_l? isEqual(str.m_s, str.m_l) : false; }
    
    P_INLINE bool operator==(const pChar* o) const
    { return isEqual(o, -1); }
    P_INLINE bool operator==(const PString& o) const
    { return isEqual(o.m_s); }
    P_INLINE bool operator==(const PArray<pChar>& o) const
    { return isEqual(&o[0], o.size()); }
    P_INLINE bool operator!=(const pChar* o) const
    { return !isEqual(o, -1); }
    P_INLINE bool operator!=(const PString& o) const
    { return !isEqual(o.m_s); }
    P_INLINE bool operator!=(const PArray<pChar>& o) const
    { return !isEqual(&o[0], o.size()); }

    P_INLINE const PString& operator=(const pChar* o)
    { assign(o, getLength(o)); return *this; }
    P_INLINE const PString& operator=(const PString& o)
    { if (&o != this) assign(o.m_s, o.length()); return *this; }
    P_INLINE const PString& operator=(const PArray<pChar>& o)
    { assign(&o[0], o.size()); return *this; }

    P_INLINE const PString& operator+=(const pChar* o)
    { append(o, -1); return *this; }
    P_INLINE const PString& operator+=(const PString& o)
    { append(o); return *this; }
    P_INLINE const PString& operator+=(const PArray<pChar>& o)
    { append(&o[0], o.size()); return *this; }

    pChar& operator[](pUint32 i) { pAssertInfo(i <= m_l, "index out of range"); return m_s[i]; }
    pChar operator[](pUint32 i) const { pAssertInfo(i <= m_l, "index out of range"); return m_s[i]; }
    
    P_INLINE PString operator+(const pChar* o) const
    { PString ret(*this); ret += o; return ret; }
    P_INLINE PString operator+(const PString& o) const
    { PString ret(*this); ret += o; return ret; }
    P_INLINE PString operator+(const PArray<pChar>& o) const
    { PString ret(*this); ret += o; return ret; }

    // Compatible with STL
    pChar* c_str() { return m_s; }
    const pChar* c_str() const { return m_s; }

    const PString& sprintf(const pChar *format, ...);

    pUint32  toUint() const;
    pInt32   toInt() const;
    pFloat32 toFloat() const;

    static PString fromUint(pUint32 value);
    static PString fromInt(pInt32 value);
    static PString fromFloat(pFloat32 value);

    PString& toLower();
    PString& toUpper();

    PString& replace(const pChar old, const pChar replacement);

private:
    pChar* m_s;
    pUint32 m_l;

    void assign(const pChar* string, pUint32 length);
    pInt32 getLength(const pChar* s);
};
    
#endif // !PSTRING_H
