// presourcemanager.h
// Resource management, e.g., shader, texture, vertex buffer, and framebuffer
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PRESOURCEMANAGER_H
#define PRESOURCEMANAGER_H

#include <PUser/presourceobject.h>

#include <PCore/parray.h>

#include <PSystem/pgltexture.h>

class PContext;
class PMesh;
class PTexture;
class PShader;
class PFrameBuffer;



class P_DLLEXPORT PResourceManager
{
    friend class PResourceObject;

public:
    PResourceManager(PContext* context);
    ~PResourceManager();

    // Create the mesh object from project archive or extern storage.
    // When the path starts with ":", e.g., ":/object1.obj", it is 
    // created from project archive. Otherwise, it is from the external
    // storage. If the same mesh has already been created, there won't 
    // be a new instance of it. The old is returned with reference count
    // incremented by 1.
    PMesh* retainMesh(const pChar* path);
    PTexture* retainTexture(const pChar* path);
    PShader* retainShader(const pChar* vertexSourcePath, 
        const pChar* fragmentSourcePath);
    PFrameBuffer* retainFrameBuffer(const pChar* name,
        pUint32 width = 0xffffffff, 
        pUint32 height = 0xffffffff, 
        PGlTextureFormatEnum colorBufferFormat = P_GLTEXTURE_FORMAT_UNKNOWN, 
        PGlTextureFormatEnum depthBufferFormat = P_GLTEXTURE_FORMAT_UNKNOWN, 
        PGlTextureFormatEnum stencilBufferFormat = P_GLTEXTURE_FORMAT_UNKNOWN);

    // Delete the recently unused objects and release memory.
    void cleanup();

    // Restore the resource object when activity resumes from background.
    void resume();

    // Discard resource objects when activity goes to background (paused)
    void pause();

private:
    // Search the resource object with given name.
    PResourceObject* findResourceObject(const pChar* name);
    // Insert the resource object into the database. Note that we
    // don't check the resource name duplication.
    void insertResourceObject(PResourceObject* object);
    // Delete all resource objects.
    void deleteResourceObjects();
    // Remove given resource object. 
    void removeResourceObject(PResourceObject* object);

    PMesh* createMesh(const pChar* path);
    PTexture* createTexture(const pChar* path);
    PShader* createShader(const pChar* name, const pChar* vertexSourcePath,
        const pChar* fragmentSourcePath);
    PFrameBuffer* createFrameBuffer(const pChar* name,
        pUint32 width, 
        pUint32 height,
        PGlTextureFormatEnum colorBufferFormat,
        PGlTextureFormatEnum depthBufferFormat,
        PGlTextureFormatEnum stencilBufferFormat);

private:
    PContext* m_context;
    PArray<PResourceObject*> m_objects; // TODO: replace array with hash map or something faster.
};


#endif // !PRESOURCEMANAGER_H
