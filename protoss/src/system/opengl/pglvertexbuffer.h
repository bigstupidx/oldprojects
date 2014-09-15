// pglvertexbuffer.h
// The wrapper of OpenGL vertex buffer object.
// 
// Copyright 2012 by Hongwei Li. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
//

#ifndef PGLVERTEXBUFFER_H
#define PGLVERTEXBUFFER_H

#include <PGlobal/pglobal.h>


// The data description of each vertex.
struct PGlVertexBufferFormat
{
    pInt32 m_size;    // The number of the elements in this vertex attribute. 
    pInt32 m_type;   // The type of the element in this vertex attribute. 
    pInt32 m_dataSize; // The data size of this vertex attribute in bytes or the buffer size if it is an index buffer entry.
};

class P_DLLEXPORT PGlVertexBuffer
{
public:
    // Constructor.
    PGlVertexBuffer();
    
    // Destructor
    ~PGlVertexBuffer();

    // Create a vertex array object. 
    bool create(PGlVertexBufferFormat* formats, pUint32 formatCount, 
        void* vertexBuffer, pUint32 vertexNumber, void* indexBuffer, 
        bool isGPUResident);

    // Render the vertex array. 
    void render();

    // The VBO will be set to the current rendering VBO.
    void enable();

    // The VBO will be disabled.
    void disable();

    // Use default VBO 0.
    void useDefault();

    // The number of triangles of this VBO.
    pUint32 getNumberOfTriangles() const;

    // The number of vertices of this VBO.
    pUint32 getNumberOfVertices() const;

private:
    pUint32 m_vbo; // The vertex buffer object. It is zero when CPU copy is only needed.
    void* m_vbb; // The vertex buffer in CPU. It is NULL when VBO is only needed. 
    pInt32 m_vertexSize; // The total size of one vertex. 
    PGlVertexBufferFormat* m_vertexFormats; // The description of each vertex attribute. 
    pUint32 m_formatCount; // The number of attributes. 
    pUint32 m_verticesCount; // The number of vertices.
    pUint32 m_ibo; // The index buffer in GPU. It is zero when buffer is stored in GPU. 
    void* m_ibb; // The index buffer in CPU. It is NULL when buffer is in GPU. 
    pUint32 m_indicesType; // The type of indices. 
    pUint32 m_indicesCount; // The number of indices. 
    bool m_enabled; // If it is the current VBO.
};


#endif // !PGLVERTEXBUFFER_H
