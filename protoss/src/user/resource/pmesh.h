// pmesh.h
// The mesh resource
// 
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PMESH_H
#define PMESH_H


#include <PUser/presourceobject.h>


class PGlVertexBuffer;


class P_DLLEXPORT PMesh : public PResourceObject
{
    friend class PResourceManager;

private:
    PMesh(const pChar *name, PResourceManager *resourceManager, PResourceFlagEnum flag);
    virtual ~PMesh();
    PMesh(const PMesh& other) : PResourceObject(P_NULL, P_NULL) {};
    void operator=(const PMesh& other) {};

public:
    void use();

protected:
    virtual void discardResource();
    virtual void restoreResource();

private:
    PGlVertexBuffer* createMesh();

    PGlVertexBuffer *createMesh(const pChar *name);
    PGlVertexBuffer *createPlane();
    PGlVertexBuffer *createSphere();
    PGlVertexBuffer *createCylinder();
    PGlVertexBuffer *createCube();

private:
    PGlVertexBuffer    *m_vertexBufferObject;
    // TODO: bounding box, used for picking.
};



#endif // !PMESH_H


