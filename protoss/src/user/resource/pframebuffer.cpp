// pframebuffer.cpp
// The framebuffer resource
// 
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pframebuffer.h"

#include <PSystem/pglframebuffer.h>


PFrameBuffer::PFrameBuffer(pUint32 width, 
        pUint32 height, 
        PGlTextureFormatEnum colorBufferFormat, 
        PGlTextureFormatEnum depthBufferFormat, 
        PGlTextureFormatEnum stencilBufferFormat, 
        const pChar* name, 
        PResourceManager* resourceManager)
    : PResourceObject(name, resourceManager, P_RESOURCE_DEFAULT, P_RESOURCE_FRAMEBUFFER)
{
    m_width = width;
    m_height = height;
    m_colorBufferFormat = colorBufferFormat;
    m_depthBufferFormat = depthBufferFormat;
    m_stencilBufferFormat = stencilBufferFormat;

    createFramebuffer();
}

PFrameBuffer::~PFrameBuffer()
{
    pDelete(m_framebufferObject);
}

void PFrameBuffer::discardResource()
{
    pDelete(m_framebufferObject);
}

void PFrameBuffer::restoreResource()
{
    createFramebuffer();
}

void PFrameBuffer::createFramebuffer()
{
    m_framebufferObject = pNew(PGlFramebuffer);
    if (!m_framebufferObject->create(m_width, m_height, m_colorBufferFormat,
                m_depthBufferFormat, m_stencilBufferFormat))
    {
        pDelete(m_framebufferObject);
        pLogError("Failed to create framebuffer object %s", m_name.c_str());
    }
}
