// prenderstate.cpp
// The rendering state
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "prenderstate.h"

#include <PSystem/pglstate.h>
#include <PSystem/pmemory.h>
#include <PSystem/pdebug.h>


PRenderState::PRenderState(pUint32 screenWidth, pUint32 screenHeight)
{
    m_state = pNew(PGlState(screenWidth, screenHeight));
}

PRenderState::~PRenderState()
{
    pDelete(m_state);
}
    
void PRenderState::useShader(PShader* shader)
{
    // TODO:
}

void PRenderState::useFrameBuffer(PFrameBuffer* frameBuffer)
{
    // TODO:
}

void PRenderState::useVertexBuffer(PVertexBuffer* vertexBuffer)
{
    // TODO:
}

void PRenderState::useTexture(PTexture* texture, pUint32 textureUnit)
{
    // TODO:
}

void PRenderState::clearFramebuffer(bool colorBuffer, bool depthBuffer, bool stencilBuffer)
{
    m_state->clearFramebuffer(colorBuffer, depthBuffer, stencilBuffer);
}