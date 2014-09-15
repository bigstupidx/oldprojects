// pcomboproperty.h
// The base class of combo properties, like int, float, etc.
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PCOMBOPROPERTY_H
#define PCOMBOPROPERTY_H

class <PUser/pabstractproperty.h>


class P_DLLEXPORT PComboProperty : public PAbstractProperty
{
public:
    PComboProperty(PPropertyTypeEnum type); 
    PComboProperty(const PComboProperty& other);
    virtual ~PComboProperty();
    const PComboProperty& operator=(const PComboProperty& other);
    
    virtual bool isPrimitive() const;
    
    virtual void setValue(const PProperty& property) = 0;
    virtual void setValue(const void* value) = 0;
    virtual void reset() = 0;
    
    KW_INLINE kwUint32 getNumberOfSubProperties() const { return m_properties.count(); }

    PSimpleProperty* getSubProperty(pUint32 index) const;
    PSimpleProperty* getSubProperty(const pChar* name) const;
    PSimpleProperty* operator[](const pChar* name) const;
    PSimpleProperty* operator[](pUint32 index) const;
};


#endif // !PCOMBOPROPERTY_H
