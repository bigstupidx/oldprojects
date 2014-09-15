// presourcemanager.cpp
// Resource management, e.g., shader, texture, vertex buffer, and framebuffer
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "presourcemanager.h"

#include <PUser/pcontext.h>
#include <PUser/pmesh.h>
#include <PUser/ptexture.h>
#include <PUser/pframebuffer.h>
#include <PUser/pshader.h>


PResourceManager::PResourceManager(PContext* context)
{
    m_context = context;
}

PResourceManager::~PResourceManager()
{
    deleteResourceObjects();
}


PMesh* PResourceManager::retainMesh(const pChar* path)
{
    PResourceObject* ret = findResourceObject(path);
    if (ret == P_NULL)
    {
        // Create the mesh
        PMesh* mesh = createMesh(path);
        insertResourceObject(mesh);
        return mesh;
    }

    ret->retain();

    return dynamic_cast<PMesh*>(ret);
}

PTexture* PResourceManager::retainTexture(const pChar* path)
{
    PResourceObject* ret = findResourceObject(path);
    if (ret == P_NULL)
    {
        // Create the texture
        PTexture* texture = createTexture(path);
        insertResourceObject(texture);
        return texture;
    }

    ret->retain();

    return dynamic_cast<PTexture*>(ret);
}

PShader* PResourceManager::retainShader(const pChar* vertexSourcePath, 
    const pChar* fragmentSourcePath)
{
    PString name(vertexSourcePath);
    name += PString(fragmentSourcePath);

    PResourceObject* ret = findResourceObject(name.c_str());
    if (ret == P_NULL)
    {
        // Create the shader
        PShader* shader = createShader(name.c_str(), vertexSourcePath, fragmentSourcePath);
        insertResourceObject(shader);
        return shader;
    }

    ret->retain();

    return dynamic_cast<PShader*>(ret);
}

PFrameBuffer* PResourceManager::retainFrameBuffer(const pChar* name,
        pUint32 width, 
        pUint32 height,
        PGlTextureFormatEnum colorBufferFormat,
        PGlTextureFormatEnum depthBufferFormat,
        PGlTextureFormatEnum stencilBufferFormat)
{
    PResourceObject* ret = findResourceObject(name);
    if (ret == P_NULL)
    {
        // Create the frame buffer
        pAssert(width != 0xffffffff && height != 0xffffffff &&
            colorBufferFormat != P_GLTEXTURE_FORMAT_UNKNOWN);
        if (width == 0xffffffff || height != 0xffffffff ||
            colorBufferFormat == P_GLTEXTURE_FORMAT_UNKNOWN)
        {
            pLogError("Invalid framebuffer parameters");
            return P_NULL;
        }
        PFrameBuffer* frameBuffer = createFrameBuffer(name, width, height,
                colorBufferFormat, depthBufferFormat, stencilBufferFormat);
        insertResourceObject(frameBuffer);
        return frameBuffer;
    }

    ret->retain();

    return dynamic_cast<PFrameBuffer*>(ret);
}
    
void PResourceManager::cleanup()
{
}

void PResourceManager::resume()
{
    pUint32 nobjects = m_objects.count();
    for (pUint32 i = 0; i < nobjects; ++i)
    {
        if (m_objects[i]->getFlag() != P_RESOURCE_SYSTEM)
        {
            m_objects[i]->restore();
        }
    }
}

void PResourceManager::pause()
{
    pUint32 nobjects = m_objects.count();
    for (pUint32 i = 0; i < nobjects; ++i)
    {
        if (m_objects[i]->getFlag() != P_RESOURCE_SYSTEM)
        {
            m_objects[i]->discard();
        }
    }
}

PResourceObject* PResourceManager::findResourceObject(const pChar* name)
{
    pUint32 nobjects = m_objects.count();
    for (pUint32 i = 0; i < nobjects; ++i)
    {
        if (m_objects[i]->getName() == name)
        {
            return m_objects[i];
        }
    }

    return P_NULL;
}
    
void PResourceManager::insertResourceObject(PResourceObject* object)
{
    m_objects.append(object);
}
    
void PResourceManager::deleteResourceObjects()
{
    pUint32 nobjects = m_objects.count();
    for (pUint32 i = 0; i < nobjects; ++i)
    {
        pDelete(m_objects[i]);
    }
}

void PResourceManager::removeResourceObject(PResourceObject* object)
{
    pUint32 pos = m_objects.find(object);
    if (pos != m_objects.count())
    {
        m_objects.remove(pos);
    }
}
    
PMesh* PResourceManager::createMesh(const pChar* path)
{
    // FIXME: consider using system sometime.
    PMesh* ret = pNew(PMesh(path, this, P_RESOURCE_DEFAULT));
    return ret;
}

PTexture* PResourceManager::createTexture(const pChar* path)
{
    PTexture* ret = pNew(PTexture(path, this));
    return ret;
}

PShader* PResourceManager::createShader(const pChar* name, const pChar* vertexSourcePath,
    const pChar* fragmentSourcePath)
{
    PShader* ret = pNew(PShader(name, vertexSourcePath, fragmentSourcePath, this));
    return ret;
}

PFrameBuffer* PResourceManager::createFrameBuffer(const pChar* name,
        pUint32 width, 
        pUint32 height,
        PGlTextureFormatEnum colorBufferFormat,
        PGlTextureFormatEnum depthBufferFormat,
        PGlTextureFormatEnum stencilBufferFormat)
{
    PFrameBuffer* ret = pNew(PFrameBuffer(width, height, colorBufferFormat, 
        depthBufferFormat, stencilBufferFormat, name, this));
    return ret;
}

