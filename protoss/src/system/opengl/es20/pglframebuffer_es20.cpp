// pglframebuffer.cpp
// The framebuffer object.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Jihao Xu xujihao@cooee.cn and Hongwei Li lihw81@gmail.com
// 


#include "../pglframebuffer.h"

#include <PSystem/pgltexture.h>
#include <PSystem/pglerror.h>
#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h> 


PGlFramebuffer::PGlFramebuffer()
{
    m_colorBuffer = P_NULL;
    m_depthBuffer = P_NULL;
    m_stencilBuffer = P_NULL;

    m_enabled = false;

    m_framebuffer = 0;
}

PGlFramebuffer::~PGlFramebuffer()
{
    pDelete(m_colorBuffer);
    pDelete(m_depthBuffer);
    pDelete(m_stencilBuffer);

    if (m_framebuffer != 0)
    {
        glDeleteFramebuffers(1, &m_framebuffer);
    }
}

bool PGlFramebuffer::create(pUint32 width, pUint32 height, PGlTextureFormatEnum colorFormat, 
            PGlTextureFormatEnum depthFormat, PGlTextureFormatEnum stencilFormat)
{
    pAssert(m_colorBuffer != P_NULL);
    if (m_colorBuffer != P_NULL)
    {
        pLogWarning("Framebuffer has a color buffer already");
        return false;
    }
    
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glActiveTexture(GL_TEXTURE0);
    
    pAssert(colorFormat < P_GLTEXTURE_FORMAT_UNKNOWN);

    m_colorBuffer = pNew(PGlTexture);
    if (!m_colorBuffer->create((pUint8 *)P_NULL, width, height, colorFormat))
    {
        pLogWarning("Failed to create color buffer");
        return false;
    }

    // Bind color buffer.
    glBindTexture(GL_TEXTURE_2D, m_colorBuffer->getTextureHandle());
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
        m_colorBuffer->getTextureHandle(), 0);

    if (depthFormat != P_GLTEXTURE_FORMAT_UNKNOWN)
    {
        if (!m_depthBuffer->create((pUint8 *)P_NULL, width, height, depthFormat))
        {
            // REVIEW+DONE(lihw): delete color buffer before return.
            // FEEDBACK: thanks.
            pDelete(m_colorBuffer);
            pLogWarning("Failed to create depth buffer");
            return false;
        }
        // REVIEW+DONE(lihw): move code here as we need to ensure the depth
        // buffer is available before binding.
        // FEEDBACK: thanks.
        // Bind depth buffer.
        glBindTexture(GL_TEXTURE_2D, m_depthBuffer->getTextureHandle());
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                m_depthBuffer->getTextureHandle(), 0);
    }

    if (stencilFormat != P_GLTEXTURE_FORMAT_UNKNOWN)
    {
        if (!m_stencilBuffer->create((pUint8 *)P_NULL, width, height, stencilFormat))
        {
            // REVIEW+DONE(lihw): delete color and depth buffer before return.
            // FEEDBACK: thanks.
            pDelete(m_colorBuffer);
            pDelete(m_depthBuffer);
            pLogWarning("Failed to create stencil buffer");
            return false;
        }
        // REVIEW+DONE(lihw): move code here as we need to ensure the stencil
        // buffer is available before binding.
        // FEEDBACK: thanks.

        // Bind stencil buffer.
        glBindTexture(GL_TEXTURE_2D, m_stencilBuffer->getTextureHandle());
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
                m_stencilBuffer->getTextureHandle(), 0);
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // REVIEW+DONE(lihw): put the checkFramebufferStatus() after finishing
    // binding.
    // FEEDBACK: thanks.
    if (!checkFramebufferStatus())
    {
        pDelete(m_colorBuffer);
        pDelete(m_depthBuffer);
        pDelete(m_stencilBuffer);
    
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, getDefaultFramebufferHandle());
    
    // REVIEW+DONE(lihw): should better check if the OpenGL has internal
    // error 
    // FEEDBACK: thanks.
    if (!pGlErrorCheckError())
    {
        pDelete(m_colorBuffer);
        pDelete(m_depthBuffer);
        pDelete(m_stencilBuffer);

        return false;
    }
    
    // REVIEW+DONE(lihw): the return value is missing.
    // FEEDBACK: thanks.
    return true;
}

pUint32 PGlFramebuffer::getDefaultFramebufferHandle() const
{
    // REVIEW+DONE(lihw): interesting as I learned from OpenGL spec, it is always 0.
    // FEEDBACK: I saw it on Libgdx code. We just leave a interface here if needs.
    // TODO: It seems that IOS's default framebuffer handle is different with others.
    return 0;
}

bool PGlFramebuffer::checkFramebufferStatus()
{
    pUint32 result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    bool ret = true;

    if (result != GL_FRAMEBUFFER_COMPLETE)
    {
        glDeleteFramebuffers(1, &m_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, getDefaultFramebufferHandle());

        if (result == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
        {
            pLogError("Frame buffer couldn't be constructed: incomplete attachment");
        }
        if (result == GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS)
        {
            pLogError("Frame buffer couldn't be constructed: incomplete dimensions");
        }    
        if (result == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
        {
            pLogError("Frame buffer couldn't be constructed: missing attachment");
        }
        
        ret = false;
    }

    return ret;
}

void PGlFramebuffer::enable()
{
    if (!m_enabled)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
        m_enabled = false;
    }
}

void PGlFramebuffer::disable()
{
    if (m_enabled)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, getDefaultFramebufferHandle());
        m_enabled = false;
    }
}
