// pglstate_es20.cpp
// The OpenGL render state
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com

#include "../pglstate.h"

#include <PSystem/pdebug.h>
#include <PSystem/pglerror.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h> 


PGlState::PGlState(pUint32 screenWidth, pUint32 screenHeight)
{
    m_screenWidth  = screenWidth;
    m_screenHeight = screenHeight;

    reset();
    
    const GLubyte* vendor = glGetString(GL_VENDOR);
    pLogInfo("Running on %s display card", (pChar*)(vendor));
}

PGlState::~PGlState()
{
}

void PGlState::reset()
{
    setViewport(0, 0, m_screenWidth, m_screenHeight);

    setColorWriteMode(P_GLCOLORWRITE_DEFAULT);
    pUint8 clearColor[] = {127, 127, 127, 0};
    setClearColor(clearColor);  
    setDepthTestMode(P_GLDEPTHTEST_DEFAULT);
    setClearDepth(1.0f);
    setScissorTestEnabled(false, 0, 0, 0, 0);
    setBlendMode(P_GLBLEND_DEFAULT);
    setCullMode(P_GLCULL_DEFAULT);
    
    // FIXME: depth func
    glDepthFunc(GL_LEQUAL);
    
    // FIXME: stencil
    glDisable(GL_STENCIL_TEST);
    
    pGlErrorCheckError();
}

void PGlState::getViewport(pUint32* viewport) const
{
    viewport[0] = m_viewport[0];
    viewport[1] = m_viewport[1];
    viewport[2] = m_viewport[2];
    viewport[3] = m_viewport[3];
}

void PGlState::setViewport(pUint32 x, pUint32 y, pUint32 width, pUint32 height)
{
    // FIXME: We are still at 4K age.
    pAssert(x < 4096 &&
             y < 4096 &&
             x + width <= 4096 &&
             y + height <= 4096);
    if (x >= 4096 || y >= 4096 || x + width > 4096 || y + height > 4096)
    {
        pLogError("invalid viewport values: (%d, %d, %d, %d)", x, y, width, height);

        // FIXME: it is good to let application crash at OpenGL so we don't return here.
    }

    // Cache the viewport value.
    if (m_viewport[0] == x && m_viewport[1] == y && 
        m_viewport[2] == width && m_viewport[3] == height)  
    {
        return ;
    }

    m_viewport[0] = x;
    m_viewport[1] = y;
    m_viewport[2] = width;
    m_viewport[3] = height;

    glViewport(x, y, width, height);
}

void PGlState::setColorWriteMode(PGlColorWriteModeEnum mode)
{
    if (m_colorWriteMode == mode)
    {
        return ;
    }

    m_colorWriteMode = mode;

    pUint32 mask = (pUint32)m_colorWriteMode;
    GLboolean red, green, blue, alpha;
    if (mask & 0x01)
    {
        red = GL_TRUE;
    }
    if (mask & 0x02)
    {
        green = GL_TRUE;
    }
    if (mask & 0x04)
    {
        blue = GL_TRUE;
    }
    if (mask & 0x08)
    {
        alpha = GL_TRUE;
    }

    glColorMask(red, green, blue, alpha);
}

void PGlState::setClearColor(const PColorRGBA& color)
{
    if (color == m_clearColor)
    {
        return ;
    }

    m_clearColor = color;

    glClearColor(m_clearColor.getRFloat(),
                 m_clearColor.getGFloat(),
                 m_clearColor.getBFloat(),
                 m_clearColor.getAFloat());
}
    
void PGlState::setClearDepth(pFloat32 depth)
{
    if (depth == m_clearDepth)
    {
        m_clearDepth = depth;
        glClearDepthf(depth);
    }
}

void PGlState::setCullMode(PGlCullModeEnum mode)
{
    if (m_cullMode == mode)
    {
        return;
    }

    m_cullMode = mode;

    switch (pUint32(mode))
    {
        case P_GLCULL_NONE:
            glDisable(GL_CULL_FACE);
            break;
        case P_GLCULL_BACK:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            break;
        case P_GLCULL_FRONT:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            break;
        default:
            pAssertNotReachable();
            break;
    }
}

void PGlState::setDepthTestMode(PGlDepthTestModeEnum mode)
{
    if (mode == m_depthTestMode)
    {
        return ;
    }

    m_depthTestMode = mode;

    switch (pUint32(mode))
    {
        case P_GLDEPTHTEST_DISABLED:
            glDisable(GL_DEPTH_TEST);
            break;
        case P_GLDEPTHTEST_UNWRITABLE:
            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_FALSE);
            break;
        case P_GLDEPTHTEST_WRITABLE:
            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_TRUE);
            break;
        default:
            pAssertNotReachable();
            break;
    }
}
    
void PGlState::setStencilTestMode(PGlStencilTestModeEnum mode)
{
    if (mode == m_stencilMode)
    {
        return ;
    }

    m_stencilMode = mode;

    // TODO: Implement this function.
}

void PGlState::setScissorTestEnabled(bool enabled, pInt32 left, pInt32 bottom, pInt32 width, pInt32 height)
{
    if (enabled != m_scissorTestEnabled || enabled)
    {
        m_scissorTestEnabled = enabled;

        if (m_scissorTestEnabled)
        {
            glEnable(GL_SCISSOR_TEST);
            glScissor(left, bottom, width, height);

            m_scissor[0] = left;
            m_scissor[1] = bottom;
            m_scissor[2] = width;
            m_scissor[3] = height;
        }
        else
        {
            glDisable(GL_SCISSOR_TEST);
        }
    }
}

void PGlState::setBlendMode(PGlBlendModeEnum mode)
{
    if (m_blendMode == mode)
    {
        return ;
    }

    m_blendMode = mode;

    switch (pUint32(mode))
    {
        case P_GLBLEND_OPAQUE:
            glDisable(GL_BLEND);
            break;
        case P_GLBLEND_ALPHA: 
            glEnable(GL_BLEND);
            glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case P_GLBLEND_ADDITIVE:
            glEnable(GL_BLEND);
            glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
            glBlendFunc(GL_ONE, GL_ONE);
            break;
    }
}

pUint32 PGlState::query(PGlStateQueryEnum flag)
{
    GLint ret;
    switch (flag)
    {
        case P_GLTEXTURE_UNIT_NUMBER:
            glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &ret);
            break;
        default:
            pLogWarning("unsupported query flag");
            break;
    }

    pGlErrorCheckError();

    return ret; 
}
    
void PGlState::clearFramebuffer(bool colorBuffer, bool depthBuffer, bool stencilBuffer)
{
    GLbitfield bits = 0;
    if (colorBuffer)
    {
        bits |= GL_COLOR_BUFFER_BIT;
    }
    if (depthBuffer)
    {
        bits |= GL_DEPTH_BUFFER_BIT;
    }
    if (stencilBuffer)
    {
        bits |= GL_STENCIL_BUFFER_BIT;
    }

    glClear(bits);
}


