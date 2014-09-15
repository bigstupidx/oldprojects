// pglvertexbuffer_es20.cpp
// The wrapper of OpenGL vertex array.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 


#include "../pglvertexbuffer.h"

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>
#include <PSystem/pcrt.h>
#include <PSystem/pglerror.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h> 


PGlVertexBuffer::PGlVertexBuffer()
{
    m_vbo = 0;
    m_vbb = P_NULL;
    m_ibo = 0;
    m_ibb = P_NULL;
    m_vertexFormats = P_NULL;
    m_enabled = false;
}

PGlVertexBuffer::~PGlVertexBuffer()
{
    if (m_vbo != 0)
    {   
        glDeleteBuffers(1, &m_vbo);       
        m_vbo = 0;
    }
    if (m_ibo != 0)
    {
        glDeleteBuffers(1, &m_ibo);
        m_ibo = 0;
    }

    if (m_vbb != P_NULL)
    {
        pUint8* v = (pUint8*)(m_vbb);
        pDeleteArray(v);
    }
    if (m_ibb != P_NULL)
    {
        pUint8* i = (pUint8*)(m_ibb);
        pDeleteArray(i);
    }
    if (m_vertexFormats != P_NULL)
    {
        pDeleteArray(m_vertexFormats);
    }
    
    pGlErrorCheckWarning();
}

bool PGlVertexBuffer::create(PGlVertexBufferFormat* formats, pUint32 formatCount, 
    void* vertexBuffer, pUint32 vertexNumber, void* indexBuffer, bool isGPUResident)
{
    const GLenum dataTypes[] =
    {
        GL_BYTE,
        GL_UNSIGNED_BYTE,
        GL_SHORT,
        GL_UNSIGNED_SHORT,
        GL_INT,
        GL_UNSIGNED_INT,
        GL_FLOAT,
    };

    pAssert(m_vertexFormats == P_NULL);
    pAssert(m_vbo == 0 && m_ibb == 0);
    pAssert(m_vbb == P_NULL && m_ibb == P_NULL);

    // Sanity check
    if (formats == P_NULL || vertexBuffer == P_NULL || indexBuffer == P_NULL)
    {
        pLogWarning("some parameters are NULL");
        return false;
    }

    // Save the vertex attributes. 

    // The last element of formats is about index.
    m_formatCount = formatCount - 1;

    m_vertexFormats = pNewArray(PGlVertexBufferFormat [m_formatCount]);

    m_vertexSize = 0;
    for (pUint32 i = 0; i < m_formatCount; ++i)
    {
        m_vertexFormats[i].m_size = formats[i].m_size;
        m_vertexFormats[i].m_type = dataTypes[formats[i].m_type];
        m_vertexFormats[i].m_dataSize = formats[i].m_dataSize;

        m_vertexSize += formats[i].m_dataSize;
    }

    m_verticesCount = vertexNumber;

    // Compute the buffer size to hold all vertex data. 
    GLuint vertexBufferSize = m_vertexSize * vertexNumber;
    GLuint indexBufferSize = formats[formatCount - 1].m_dataSize; 

    m_indicesType = dataTypes[formats[formatCount - 1].m_type];
    m_indicesCount = formats[formatCount - 1].m_size;

    // Copy the vertex and index data to GPU and CPU if needed.
    if (isGPUResident)
    {
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ibo);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertexBuffer, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBuffer, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
    {
        m_vbb = pNewArray(pUint8 [vertexBufferSize]);
        pmemcpy(m_vbb, vertexBuffer, vertexBufferSize);

        m_ibb = pNewArray(pUint8 [indexBufferSize]);
        (m_ibb, indexBuffer, indexBufferSize);
    }


    pGlErrorCheckAbort();

    return true;
}

void PGlVertexBuffer::render()
{
    pAssert(m_enabled);
    pAssert(m_vbo > 0 || m_vbb != P_NULL);

    if (m_enabled)
    {
        glDrawElements(GL_TRIANGLES, m_indicesCount, m_indicesType, m_ibb);
        pGlErrorCheckError();
    }
}

void PGlVertexBuffer::enable()
{
    // FIXME: GL error at CPU buffer mode.

    // PRenderEngine will ensure the same VBO won't be enabled twice consecutively.
    //pAssert(!m_enabled);
    if (m_enabled)
    {
        return ;
    }

    GLubyte* offset = (GLubyte *)m_vbb;

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // TODO: we can fix the vertex format throughout the whole protoss program, so
    // that we don't need to remember the format in each PGlVertexBuffer object.
    // Enable each vertex attribute. 
    for (pUint32 i = 0; i < m_formatCount; ++i)
    {
        glVertexAttribPointer(i, 
            m_vertexFormats[i].m_size, 
            m_vertexFormats[i].m_type, 
            GL_FALSE, 
            m_vertexSize,
            (void *)offset);
        glEnableVertexAttribArray(i);

        offset += m_vertexFormats[i].m_dataSize; 
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    m_enabled = true;

    pGlErrorCheckError();
}

void PGlVertexBuffer::disable()
{
    // PRenderEngine will ensure the same VBO won't be disabled twice consecutively.
    pAssert(m_enabled);
    m_enabled = false;
}

void PGlVertexBuffer::useDefault()
{
    pAssert(!m_enabled);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    for (pUint32 i = 0; i < m_formatCount; ++i)
    {
        glDisableVertexAttribArray(i);
    }
}

pUint32 PGlVertexBuffer::getNumberOfTriangles() const
{
    return m_indicesCount / 3;
}

pUint32 PGlVertexBuffer::getNumberOfVertices() const
{
    return m_verticesCount;
}

