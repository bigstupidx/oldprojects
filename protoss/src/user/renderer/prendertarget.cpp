// prendertarget.cpp
// The rendering target. 
//
// Copyright 2013 Cooee. All rights reserved.
//
// Jihao Xu xujiao@cooee.cn
//
// 

#include "prendertarget.h"

void PRenderTarget::setColorWriteMode(PGlColorWriteModeEnum mode)
{
    m_colorWriteMode = mode;
}

void PRenderTarget::setDepthWriteMode(PGlDepthTestModeEnum mode)
{
    m_depthTestMode = mode;
}

void PRenderTarget::setStencilWriteMode(PGlStencilTestModeEnum mode)
{
    m_stencilWriteMode = mode;
}

void PRenderTarget::setScissorTestEnabled(bool enabled, pUint32 left, pUint32 bottom, pUint32 width, pUint32 height)
{
    m_scissorTestEnable = enabled;
    m_scissorLeft = left;
    m_scissorBottom = bottom;
    m_scissorWidth = width;
    m_scissorHeight = height;
}

void PRenderTarget::setBlendMode(PGlBlendModeEnum mode)
{
    m_blendMode =  mode;
}

void PRenderTarget::setBufferClearEnabled(bool color, bool depth, bool stencil)
{
    m_colorBufferClear = color;
    m_depthBufferClear = depth;
    m_stencilBufferClear = stencil;
}

void PRenderTarget::setViewport(pUint32 x, pUint32 y, pUint32 w, pUint32 h)
{
    m_viewportLeft = x;
    m_viewportBottom = y;
    m_viewportWidth = w;
    m_viewportHeight = h;
}

void PRenderTarget::getScissorRect(pUint32 &left, pUint32 &bottom, pUint32 &width, pUint32 &height) const
{
    left = m_scissorLeft;
    bottom = m_scissorBottom;
    width = m_scissorWidth;
    height = m_scissorHeight;
}

void PRenderTarget::getViewport(pUint32 &x, pUint32 &y, pUint32 &w, pUint32 &h) const
{   
    x = m_viewportLeft;
    y = m_viewportBottom;
    w = m_viewportWidth;
    h = m_viewportHeight;
}
