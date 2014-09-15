// pdata.h
// The base class of all protoss objects which needs property interface.
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//
// 

#ifndef PDATA_H
#define PDATA_H

// REVIEW(lihw): the order of including headers should be from higher layer
// to lower layer, i.e., platform, user, core, system.
// FEEDBACK: thanks.
// move Puser header up.
#include <PUser/pabstractproperty.h>

#include <PCore/pstring.h>
#include <PCore/plist.h>
#include <PCore/pmap.h>
// REVIEW(lihw): usually, when we included headers under PCore or PSystem, we 
// don't need to include pglobal.h again as the former headers must have this
// one included already.
// FEEDBACK: thanks.
// remove pglobal.h.

//#define PDATA_HAS_MAP

class PAbstractProperty;

class P_DLLEXPORT PData
{
public:
    PData();
    virtual ~PData();

    // REVIEW(lihw): I notice we have defined property's property, like x
    // coordinate of a 3D position.  Then, if the return value in PData of
    // querying a property is a pointer, I'm worried about its usage. For
    // example,
    // PData data;
    // data["position"]->operator[]("x");
    //
    // I don't know if users will be fond of this usage.
    //
    // I'd like to see the property related interface design in PData is user
    // friendly and like a natural language. Anything close to data["position"]["x"] or
    // data.property("position").("x") will be adorable from my angle.
    //
    // I suggest we can shoot for this direction.
    // FEEDBACK: change the type of return value from pointer to reference,
    // and add getter functions to class PAbstractProperty as well.
    // so the usage would be:
    // PData *pData;
    // (*pData)["position"]["x"];
    PAbstractProperty &operator[](const pChar *name);
    PAbstractProperty &getProperty(const pChar *name);
    void addProperty(const pChar *name, PAbstractProperty *property);
    
    pUint32 getNumberOfProperties() const;
    PArray<PString> &getPropertyNames() const;
    PArray<PAbstractProperty> &getProperties() const;

protected:
    // REVIEW(lihw): a very interesting design here and worthy discussion.
    // Now we put all properties purely inside a map, so that all access
    // to properties must be through map query. It could introduce some performance
    // issue in the derived classes of PData. For example, in PDrawable,
    // if we have a function called getX(), which is to get the x coordinate
    // of position of this object, we need to dive into the map data and 
    // find the corresponding property and return the value to the caller.
    // The map query takes time. When getX() is called very frequently, say 
    // 1000 times per frame, the accumulated time invested in map query is
    // not ignorable.
    //
    // Instead, if we save a pointer in the map data structure for name-to-
    // property mapping and have its memory some place else, we can realize the direct
    // access as well. Take PDrawable::getX() for illustration. We can define
    // PProperty m_x, and put pointer to m_x inside the map. Then, in PDrawable::getX(),
    // we use m_x and in getProperty("x"), we refer to m_properties["x"]. The
    // philosophy is we define separated interface for popular functionalities,
    // like getX, getRotationX and etc. By accessing the data directly, we
    // won't waste time on map query.
    //
    // FEEDBACK: thanks.
    // it would be better that the type of pmap's value is pointer, not class.

    // REVIEW(lihw): after a second thought, I am thinking if we need a complex
    // data structure as map for fast searching property. Consider this. Properties
    // are determined at the construction of this object and queried later. In other
    // words, we can design a particular data structure so that we optimize the 
    // searching/querying speed. From this angle, I think a sorted array plus binary
    // search will be the best choice. It provides the fast searching speed undoubtedly. 
    //
    // FEEDBACK: thanks and i think the same.
    // get the index from m_propertiesName use binary searh,
    // and get property from m_properties use the index directly.
    PArray<PString>             m_propertiesName;
    PArray<PAbstractProperty>   m_properties;
};




#endif // !PDATA_H
