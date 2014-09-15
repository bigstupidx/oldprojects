// pstring.h
// Ascii string in C++.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pstring.h"

#include <PSystem/pcrt.h>

#include <ctype.h>

PString::PString(const pChar* o, pInt32 l)
{
    if (o != P_NULL)
    {
        if (l < 0)
        {
            l = getLength(o);
        }

        m_l = l; 
        m_s = pNewArray(pChar [m_l + 1]);
        pmemcpy(m_s, o, m_l);
        m_s[m_l] = 0;
    }
    else
    {
        m_s = P_NULL;   
        m_l = -1;
    }
}

PString::PString(const PArray<pChar>& o)
{
    m_l = o.size();
    m_s = pNewArray(pChar [m_l + 1]);
    pmemcpy(m_s, &o[0], m_l);
    m_s[m_l] = 0;
}

PString::PString(const PString& o)
{
    m_l = o.m_l;
    m_s = pNewArray(pChar [m_l + 1]);
    pmemcpy(m_s, o.m_s, o.m_l);
    m_s[m_l] = 0;
}
    
PString::PString(pUint32 l)
{
    m_l = l;
    m_s = pNewArray(pChar [l + 1]);
    pmemset(m_s, 0, m_l + 1);
}

PString::PString(pChar c, pUint32 n)
{
    m_l = n;
    m_s = pNewArray(pChar [m_l + 1]);
    pmemset(m_s, *(pUint8*)&c, m_l);
    m_s[m_l] = 0;
}

PString::~PString()
{
    pDeleteArray(m_s);
}

PString PString::left(pUint32 n) const
{
    pAssertInfo(n <= m_l, "not enough characters in the string");
    return PString(m_s, n);
}

PString PString::right(pUint32 n) const
{
    pInt32 position = pInt32(m_l) - pInt32(n);
    pAssertInfo(position >= 0, "not enough characters in the string");
    return PString(m_s, n);
}

PString PString::mid(pUint32 position, pInt32 n) const
{
    pAssertInfo(position + n <= m_l, "not enough characters in the string");
    return PString(m_s + position, n);
}

pInt32 PString::find(pChar c) const
{
    for (pUint32 i = 0; i < m_l; ++i)
    {
        if (m_s[i] == c)
        {
            return i;
        }
    }

    return -1;
}

pInt32 PString::find(const PString& str) const
{
    pAssertNotImplemented();
    return -1;
}

pInt32 PString::find(const char* str) const
{
    pAssertNotImplemented();
    return -1;
}

pInt32 PString::rfind(pChar c) const
{
    for (pUint32 i = m_l; i >= 0; --i)
    {
        if (m_s[i] == c)
        {
            return i;
        }
    }

    return -1;
}

pInt32 PString::rfind(const PString& str) const
{
    pAssertNotImplemented();
    return -1;
}

pInt32 PString::rfind(const char* str) const
{
    pAssertNotImplemented();
    return -1;
}

void PString::append(const pChar* str, pInt32 length)
{
    if (length < 0)
    {
        length = getLength(str);
    }

    pChar* newString = pNewArray(pChar [length + m_l + 1]);
    pmemcpy(newString, m_s, m_l);
    pmemcpy(newString + m_l, str, length);
    newString[length + m_l] = 0;

    pDeleteArray(m_s);
    m_s = newString;
    m_l += pUint32(length);
}

void PString::append(const PString& str)
{
    pChar* newString = pNewArray(pChar [str.m_l + m_l + 1]);
    pmemcpy(newString, m_s, m_l);
    pmemcpy(newString + m_l, str.m_s, str.m_l);
    newString[str.m_l + m_l] = 0;

    pDeleteArray(m_s);
    m_s = newString;
    m_l += str.m_l;
}

void PString::prepend(const pChar* str, pInt32 length)
{
    if (length < 0)
    {
        length = getLength(str);
    }

    pChar* newString = pNewArray(pChar [length + m_l + 1]);
    pmemcpy(newString, str, length);
    pmemcpy(newString + length, m_s, m_l);
    newString[length + m_l] = 0;

    pDeleteArray(m_s);
    m_s = newString;
}

void PString::prepend(const PString& str) 
{
    pChar* newString = pNewArray(pChar [str.m_l + m_l + 1]);
    pmemcpy(newString, str.m_s, str.m_l);
    pmemcpy(newString + str.m_l, m_s, m_l);
    newString[str.m_l + m_l] = 0;

    pDeleteArray(m_s);
    m_s = newString;
}

bool PString::isEqual(const pChar* str, pInt32 length) const
{
    pUint32 l = pMin(m_l, *(pUint32*)&length);

    if (length >= 0)
    {
        for (pUint32 i = 0; i < l; ++i)
        {
            if (str[i] != m_s[i])
            {
                return false;
            }
        }
    }
    else
    {
        pUint32 i;
        for (i = 0; i < m_l && str[i] != 0; ++i)
        {
            if (str[i] != m_s[i])
            {
                return false;
            }
        }
        
        // The input string has the different length
        // as this one.
        if (!(i == l && str[i] == 0))
        {
            return false;
        }
    }

    return true;
}
    
const PString& PString::sprintf(const pChar *format, ...)
{
    pAssertNotImplemented();
    return *this;
}

void PString::assign(const pChar* string, pUint32 length)
{
    pDeleteArray(m_s);
    m_s = pNewArray(pChar [length + 1]);
    pmemcpy(m_s, string, length);
    m_s[length] = 0;
    m_l = pInt32(length);
}

pInt32 PString::getLength(const pChar* s)
{
    // FIXME: optimize this function.
    pInt32 l = 0;
    const pChar* p = s;
    while (*p)
    {
        l++;
        p++;
    }

    return l;
}

pUint32 PString::toUint() const
{
    const pChar* p = m_s;
    while (isdigit(*p) && *p != 0)
    {
        p++;
    }

    pUint32 ret = 0;
    // It is a hex
    if (*p == '0' && *(p + 1) == 'x')
    {
        p += 2;
        while (*p != 0 && *p != ' ' && *p != '\t')
        {
            if ((*p >= 'a' && *p <= 'f'))
            { 
                ret += ret * 16 + (*p - 'a' + 10);
            }
            else if (*p >= 'A' && *p <= 'F')
            {
                ret += ret * 16 + (*p - 'a' + 10);
            }
            else if (*p >= '0' && *p <= '9')
            {
                ret += ret * 16 + (*p - '0');
            }
            else
            {
                break;
            }
        }

    }
    else
    {
        // It is an oct.
        pInt32 x = patoi(m_s);
        if (x < 0)
        {
            ret = *((pUint32*)&x);
        }
        else
        {
            ret = x;
        }
    }

    return ret;
}

pInt32 PString::toInt() const
{
    return patoi(m_s);
}

pFloat32 PString::toFloat() const
{
    return patof(m_s);
}

PString PString::fromUint(pUint32 value)
{
    pChar buffer[64];
    psprintf(buffer, 64, "%u", value);
    return PString(buffer);
}

PString PString::fromInt(pInt32 value)
{
    pChar buffer[64];
    psprintf(buffer, 64, "%d", value);
    return PString(buffer);
}

PString PString::fromFloat(pFloat32 value)
{
    pChar buffer[64];
    psprintf(buffer, 64, "%f", value);
    return PString(buffer);
}
    
PString& PString::toLower()
{
    if (m_s == P_NULL)
    {
        return *this;
    }

    for (pUint32 i = 0 ; i < m_l; ++i)
    {
        if (m_s[i] >= 'A' && m_s[i] <= 'Z')
        {
            m_s[i] = m_s[i] - 'A' + 'a';
        }
    }
    
    return *this;
}

PString& PString::toUpper()
{
    if (m_s == P_NULL)
    {
        return *this;
    }

    for (pUint32 i = 0 ; i < m_l; ++i)
    {
        if (m_s[i] >= 'a' && m_s[i] <= 'z')
        {
            m_s[i] = m_s[i] - 'a' + 'A';
        }
    }

    return *this;
}

PString& PString::replace(const pChar old, const pChar replacement)
{
    if (m_s == P_NULL)
    {
        return *this;
    }

    for (pUint32 i = 0 ; i < m_l; ++i)
    {
        if (m_s[i] == old)
        {
            m_s[i] = replacement;
        }
    }

    return *this;
}

