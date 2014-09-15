// pgeometry.h 
// The geometry data of a drawable.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//
// 

#ifndef PGEOMETRY_H
#define PGEOMETRY_H

// DESIGN GUIDELINE:
// Usage 1:
// drawable->getGeometry()->setMesh(mesh); 
//
// Usage 2:
// pFloat32 w = drawable->getGeometry()->getWidth();
// pFloat32 h = drawable->getGeometry()->getHeight();
// pFloat32 d = drawable->getGeometry()->getDepth();
//
//

#include <PGlobal/pgloba.h>

class PMesh;

class PGeometry
{
    friend class PDrawable;

private:
    PGeometry();
    ~PGeometry();

public:
    void setMesh(PMesh *mesh);
    P_INLINE PMesh *getMesh() const
    { return m_mesh; }

    pFloat32 getWidth() const;
    pFloat32 getHeight() const;
    pFloat32 getDepth() const;

private:
    PBoundingBox m_bbox; // Bounding box.
    PMesh       *m_mesh;
};


#endif // !PGEOMETRY_H

