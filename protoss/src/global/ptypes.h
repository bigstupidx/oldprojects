// ptypes.h
// The basic data types in Protoss.
// 
// Copyright 2013 by Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 


#ifndef PTYPES_H
#define PTYPES_H

typedef char            pInt8;
typedef unsigned char   pUint8;
typedef short           pInt16;
typedef unsigned short  pUint16;
typedef int             pInt32;
typedef unsigned int    pUint32;
typedef float           pFloat32;
typedef double          pFloat64;
typedef char            pChar;
typedef bool            pBool;

enum PTypeEnum
{
    P_BYTE,            ///< pInt8
    P_UNSIGNED_BYTE,   ///< pUint8
    P_SHORT,           ///< pInt16
    P_UNSIGNED_SHORT,  ///< pUint16
    P_INT,             ///< pInt32
    P_UNSIGNED_INT,    ///< pUint32
    P_FLOAT32,         ///< pFloat32
    P_FLOAT64,         ///< pFloat64
    P_CHAR,            ///< pChar
    P_BOOLEAN,         ///< bool
};

#if !defined P_NULL
# define P_NULL 0       
#endif

template<typename T>
class PTypeInfo
{
public:
    enum 
    {
        isPointer = false,
        isComplex = true,
        isLarge   = (sizeof(T) > sizeof(void*)),
        isDummy   = false,
    };
};

template <typename T>
class PTypeInfo<T*>
{
public:
    enum 
    {
        isPointer = true,
        isComplex = false,
        isLarge   = false,
        isDummy   = false,
    };
};

enum 
{
    P_PRIMITIVE_TYPE = 0x01,
    P_DUMMY_TYPE     = 0x02,
};

#define P_DECLARE_TYPEINFO(TYPE, ENUM, FLAGS) \
template<> \
class PTypeInfo<TYPE> \
{ \
public: \
    enum \
    { \
        isComplex = (((FLAGS) & P_PRIMITIVE_TYPE) == 0), \
        isLarge = (sizeof(TYPE)>sizeof(void*)), \
        isPointer = false, \
        isDummy = (((FLAGS) & P_DUMMY_TYPE) != 0) \
    }; \
    static P_INLINE const pChar* name() { return #TYPE; } \
    static P_INLINE const PTypeEnum type() { return ENUM; } \
};

P_DECLARE_TYPEINFO(pInt8,    P_BYTE,           P_PRIMITIVE_TYPE)
P_DECLARE_TYPEINFO(pUint8,   P_UNSIGNED_BYTE,  P_PRIMITIVE_TYPE)
P_DECLARE_TYPEINFO(pInt16,   P_SHORT,          P_PRIMITIVE_TYPE)
P_DECLARE_TYPEINFO(pUint16,  P_UNSIGNED_SHORT, P_PRIMITIVE_TYPE)
P_DECLARE_TYPEINFO(pInt32,   P_INT,            P_PRIMITIVE_TYPE)
P_DECLARE_TYPEINFO(pUint32,  P_UNSIGNED_INT,   P_PRIMITIVE_TYPE)
P_DECLARE_TYPEINFO(pFloat32, P_FLOAT32,        P_PRIMITIVE_TYPE)
P_DECLARE_TYPEINFO(pFloat64, P_FLOAT64,        P_PRIMITIVE_TYPE)
P_DECLARE_TYPEINFO(bool,     P_BOOLEAN,        P_PRIMITIVE_TYPE)

template<typename T> struct PTypeTrait           { typedef T data_type; };
template<typename T> struct PTypeTrait<const T>  { typedef T data_type; };
template<typename T> struct PTypeTrait<T&>       { typedef T data_type; };
template<typename T> struct PTypeTrait<T*>       { typedef T data_type; };
template<typename T> struct PTypeTrait<const T*> { typedef T data_type; };
template<typename T> struct PTypeTrait<T* const> { typedef T data_type; };
template<typename T> struct PTypeTrait<const T&> { typedef T data_type; };


#endif // !PTYPES_H 
