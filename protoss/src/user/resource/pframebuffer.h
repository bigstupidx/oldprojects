// pframebuffer.h
// The framebuffer resource
// 
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PFRAMEBUFFER_H
#define PFRAMEBUFFER_H


#include <PUser/presourceobject.h>

#include <PSystem/pgltexture.h>


class PGlFramebuffer;
class PRenderState;

class P_DLLEXPORT PFrameBuffer : public PResourceObject
{
    friend class PResourceManager;
private:
    PFrameBuffer(pUint32 width, 
        pUint32 height, 
        PGlTextureFormatEnum colorBufferFormat, 
        PGlTextureFormatEnum depthBufferFormat, 
        PGlTextureFormatEnum stencilBufferFormat, 
        const pChar* name, 
        PResourceManager* resourceManager); 
    PFrameBuffer(const PFrameBuffer& other) : PResourceObject(P_NULL, P_NULL) {};
    void operator=(PFrameBuffer& other) {};
    virtual ~PFrameBuffer();

    void enable(PRenderState* renderState);
    void disable(PRenderState* renderState);

protected:
    virtual void discardResource();
    virtual void restoreResource();

private:
    void createFramebuffer();

private:
    PGlFramebuffer         *m_framebufferObject;
    pUint32                 m_width;
    pUint32                 m_height;
    PGlTextureFormatEnum    m_colorBufferFormat; 
    PGlTextureFormatEnum    m_depthBufferFormat; 
    PGlTextureFormatEnum    m_stencilBufferFormat; 

};



#endif // !PFRAMEBUFFER_H


