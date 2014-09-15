// pdrawble.h
// The drawable objects
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//
// 

#ifndef PDRAWABLE_H
#define PDRAWABLE_H

#include <PUser/pobject.h>
#include <PUser/pmaterial.h>
#include <PUser/pgeometry.h>

//
// DESIGN GUIDE (will be removed after design review):
// - about transformation interface PDrawable.
//  Transformation of PDrawable defines the local matrix of
//  the PDrawable object. A PDrawable should provide an
//  interface that can
//
//  * set 3D position of the object; set the x coordinate of 
//  3D position separatedly; set the y coordinate; set the z
//  coordinate;
//  * get current 3D position of the object.
//  * set the orientation of the object with Euler angle;
//  set the rotation angle of object with x axis; set the angle y;
//  set the angle z.
//  * get the orientation angle, in x, y, z.
//  * set size of the PDrawable object; set the width, height and
//  depth of the object seperatedly.
//  * get the size of the PDrawable object.
//  * get the local 4x4 transformation matrix of this PDrawable object.
//
// - about the geometry and material interface, they are done already.

class P_DLLEXPORT PDrawable
{
public:
    PDrawable(PDrawable* parent = P_NULL);
    virtual ~PDrawable();

    bool isVisible() const;
    void setVisible(bool visible);
    bool isPickable() const;
    void setPickable(bool pickable);

    PGeometry* getGeometry();
    PMaterial* getMaterial();
    const PGeometry* getGeometry() const;
    const PMaterial* getMaterial() const;

private:
    PGeometry m_geometry;
    PMaterial m_material;
};

#endif  //!PDRAWABLE_H

