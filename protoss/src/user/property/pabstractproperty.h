// pabstractproperty.h
// The base class of all properties
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PABSTRACTPROPERTY_H
#define PABSTRACTPROPERTY_H

#include <PGlobal/pglobal.h>

enum PPropertyTypeEnum
{
    P_PROPERTY_BOOL,
    P_PROPERTY_COLOR,
    P_PROPERTY_DATA,
    P_PROPERTY_ENUM,
    P_PROPERTY_FLOAT,
    P_PROPERTY_INT,
    P_PROPERTY_OBJECT,
    P_PROPERTY_MATRIX3X3,
    P_PROPERTY_MATRIX4X4,
    P_PROPERTY_RTMATRIX,
    P_PROPERTY_SRTMATRIX,
    P_PROPERTY_CAMERA,
    P_PROPERTY_STRING,
    P_PROPERTY_TEXTURE,
    P_PROPERTY_UINT,
    P_PROPERTY_VECTOR2,
    P_PROPERTY_VECTOR3,
    P_PROPERTY_VECTOR4,
    P_PROPERTY_VIEWPORT,
    
    P_PROPERTY_UNKNOWN,

    P_PROPERTY_TYPE_FIRST = P_PROPERTY_BOOL,
    P_PROPERTY_TYPE_LAST = P_PROPERTY_VIEWPORT,
    P_PROPERTY_NUMBER = P_PROPERTY_TYPE_LAST - P_PROPERTY_TYPE_FIRST + 1,
};

typedef union
{
    pBool  boolData;
    pInt32 intData;
} PPropertyData;

class P_DLLEXPORT PAbstractProperty
{
public:
    PAbstractProperty(PPropertyTypeEnum type, 
        PAbstractProperty *parent = P_NULL);
    PAbstractProperty(const PAbstractProperty& other);
    virtual ~PAbstractProperty();

    PAbstractProperty &operator[](const pChar *name);
    PAbstractProperty &getProperty(const pChar *name);
    
    const PAbstractProperty& operator=(const PAbstractProperty& other);
    
    P_INLINE PPropertyTypeEnum getType() const { return m_type; }

    virtual bool isPrimitive() const = 0;
    
    virtual void setValue(const PAbstractProperty& property) = 0;
    virtual void setValue(const void* value) = 0;
    virtual void reset() = 0;

private:
    PPropertyTypeEnum   m_type;
    PPropertyData       m_data;
};


#endif // !PABSTRACTPROPERTY_H
