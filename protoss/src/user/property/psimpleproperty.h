// psimpleproperty.h
// The base class of simple properties, like int, float, etc.
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PSIMPLEPROPERTY_H
#define PSIMPLEPROPERTY_H

class <PUser/pabstractproperty.h>


class P_DLLEXPORT PSimpleProperty : public PAbstractProperty
{
public:
    PSimpleProperty(PPropertyTypeEnum type); 
    PSimpleProperty(const PSimpleProperty& other);
    virtual ~PSimpleProperty();
    const PSimpleProperty& operator=(const PSimpleProperty& other);
    
    virtual bool isPrimitive() const;
    
    virtual void setValue(const PSimpleProperty& property) = 0;
    virtual void setValue(const void* value) = 0;
    virtual void reset() = 0;
};


#endif // !PSIMPLEPROPERTY_H
