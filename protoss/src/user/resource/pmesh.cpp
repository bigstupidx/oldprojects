// pmesh.cpp
// The mesh resource
// 
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pmesh.h"

#include <PUser/pmeshloader.h>

#include <PSystem/pglvertexbuffer.h>

    
PMesh::PMesh(const pChar *name, PResourceManager* resourceManager,
        PResourceFlagEnum flag)
    : PResourceObject(name, resourceManager, flag, P_RESOURCE_MESH)
{
    m_vertexBufferObject = createMesh();
}

PMesh::~PMesh()
{
    pDelete(m_vertexBufferObject);
}
    
void PMesh::discardResource()
{
    pDelete(m_vertexBufferObject);
}

void PMesh::restoreResource()
{
    pAssert(m_vertexBufferObject == P_NULL);
    if (m_vertexBufferObject == P_NULL)
    {
        m_vertexBufferObject = createMesh();
    }
    else
    {
        pLogError("VBO %s resumed but old vertexBuffer is not discarded");
    }
}
    
PGlVertexBuffer* PMesh::createMesh()
{
    if (m_name == "plane")
    {
        return createPlane();
    }
    else if (m_name == "sphere")
    {
        return createSphere();
    }
    else if (m_name == "cylinder")
    {
        return createCylinder();
    }
    else if (m_name == "cube")
    {
        return createCube();
    }
    
    return createMesh(m_name.c_str());
}

PGlVertexBuffer* PMesh::createMesh(const pChar *name)
{
    PMeshLoader meshLoader(name);

    pFloat32* vertexBuffer = meshLoader.getVertexBuffer();
    pUint16* indexBuffer = meshLoader.getIndexBuffer();
    if (vertexBuffer == P_NULL || indexBuffer == P_NULL)
    {
        pLogError("Failed to load mesh file %s", name);
        return P_NULL;
    }

    // FEEDBACK: should we use pUint16 to define index attribute?
    PGlVertexBufferFormat attributes[] = 
    {
        {3, P_FLOAT32, sizeof(pFloat32) * 3}, // position
        {2, P_FLOAT32, sizeof(pFloat32) * 2}, // texture coordinate
        {3, P_FLOAT32, sizeof(pFloat32) * 3}, // normal
        {6, P_UNSIGNED_INT, sizeof(pUint32) * meshLoader.getFaceCount() * 3}, // index
    };

    PGlVertexBuffer* vbo = pNew(PGlVertexBuffer);
    if (!vbo->create(attributes, 4, vertexBuffer, meshLoader.getVertexCount(), 
                indexBuffer, m_flag == P_RESOURCE_SYSTEM? false : true))
    {
        pDelete(vbo);
        return P_NULL;
    }

    return vbo;
}

PGlVertexBuffer* PMesh::createPlane()
{
    // Vertex format.
    PGlVertexBufferFormat attributes[] = 
    {
        {3, P_FLOAT32, sizeof(pFloat32) * 3}, // position
        {2, P_FLOAT32, sizeof(pFloat32) * 2}, // texture coordinate
        {3, P_FLOAT32, sizeof(pFloat32) * 3}, // normal
        {6, P_UNSIGNED_INT, sizeof(pUint32) * 6}, // index
    };

    // Vertex buffer and index buffer data.
    pFloat32 vertexBuffer[32];
    pUint32 indexBuffer[6]; 

    vertexBuffer[0] = -0.5f;  vertexBuffer[1] = -0.5f; vertexBuffer[2] = 0.0f;
    vertexBuffer[3] = 0.0f;   vertexBuffer[4] = 0.0f; 
    vertexBuffer[5] = 0.0f;   vertexBuffer[6] = 1.0f;  vertexBuffer[7] = 0.0f;
    
    vertexBuffer[8] = 0.5f;   vertexBuffer[9] = -0.5f; vertexBuffer[10] = 0.0f;
    vertexBuffer[11] = 1.0f;  vertexBuffer[12] = 0.0f; 
    vertexBuffer[13] = 0.0f;  vertexBuffer[14] = 1.0f;  vertexBuffer[15] = 0.0f;
    
    vertexBuffer[16] = 0.5f;  vertexBuffer[17] = 0.5f;  vertexBuffer[18] = 0.0f;
    vertexBuffer[19] = 1.0f;  vertexBuffer[20] = 1.0f; 
    vertexBuffer[21] = 0.0f;  vertexBuffer[22] = 1.0f;  vertexBuffer[23] = 0.0f;
    
    vertexBuffer[24] = -0.5f; vertexBuffer[25] = 0.5f;  vertexBuffer[26] = 0.0f;
    vertexBuffer[27] = 0.0f;  vertexBuffer[28] = 1.0f; 
    vertexBuffer[29] = 0.0f;  vertexBuffer[30] = 1.0f;  vertexBuffer[31] = 0.0f;

    indexBuffer[0] = 0; indexBuffer[1] = 1; indexBuffer[2] = 2;
    indexBuffer[3] = 2; indexBuffer[4] = 3; indexBuffer[5] = 0;

    PGlVertexBuffer* vbo = pNew(PGlVertexBuffer);
    if (!vbo->create(attributes, 4, vertexBuffer, 4, indexBuffer, 
            m_flag == P_RESOURCE_SYSTEM? false : true))
    {
        pDelete(vbo);
        return P_NULL;
    }

    return vbo;
}

PGlVertexBuffer* PMesh::createSphere()
{
    return P_NULL;
}

PGlVertexBuffer* PMesh::createCylinder()
{
    return P_NULL;
}

PGlVertexBuffer* PMesh::createCube()
{
    return P_NULL;
}
