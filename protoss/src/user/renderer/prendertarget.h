// prendertarget.h
// The rendering target and parameters
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//
// 

#ifndef PRENDERTARGET_H
#define PRENDERTARGET_H

#include <PUser/pframebuffer.h>

#include <PSystem/pglstate.h>


class P_DLLEXPORT PRenderTarget
{
public:
    PRenderTarget();
    virtual ~PRenderTarget();

    P_INLINE void setFramebuffer(PFrameBuffer *framebuffer) { m_framebuffer = framebuffer; }
    void setColorWriteMode(PGlColorWriteModeEnum mode);
    void setDepthWriteMode(PGlDepthTestModeEnum mode);
    void setStencilWriteMode(PGlStencilTestModeEnum mode);
    void setBlendMode(PGlBlendModeEnum mode);
    void setScissorTestEnabled(bool enabled, pUint32 left, pUint32 bottom, pUint32 width, pUint32 height);
    // REVIEW+DONE(lihw): what does buffer refer to? Is it color buffer, depth buffer or stencil buffer?
    // I guess you might want to provide an interface to control clear of the buffers.
    // FEEDBACK; thanks.
    void setBufferClearEnabled(bool color, bool depth, bool stencil);
    // TODO: more about stencil manipulation.


    P_INLINE PGlColorWriteModeEnum getColorWriteMode() const { return m_colorWriteMode; }
    P_INLINE PGlDepthTestModeEnum getDepthWriteMode() const { return m_depthTestMode; }
    P_INLINE PGlStencilTestModeEnum getStencilWriteMode() const { return m_stencilWriteMode; }
    P_INLINE PGlBlendModeEnum getBlendMode() const { return m_blendMode; }
    P_INLINE bool isScissorTestEnabled() const { return m_scissorTestEnable; }

    void getScissorRect(pUint32 &left, pUint32 &bottom, pUint32 &width, pUint32 &height) const;

    // REVIEW+TODO(lihw): please refer to setBufferClearEnabled();
    // FEEDBACK: thanks.
    P_INLINE bool getColorBufferClearEnabled() const { return m_colorBufferClear; };
    P_INLINE bool getDepthBufferClearEnabled() const { return m_depthBufferClear; };
    P_INLINE bool getStencilBufferClearEnabled() const { return m_stencilBufferClear; };
    void setViewport(pUint32 x, pUint32 y, pUint32 w, pUint32 h);
    void getViewport(pUint32 &x, pUint32 &y, pUint32 &w, pUint32 &h) const;

protected:
    PGlColorWriteModeEnum   m_colorWriteMode;
    PGlDepthTestModeEnum    m_depthTestMode;
    PGlStencilTestModeEnum  m_stencilWriteMode;
    PGlBlendModeEnum        m_blendMode;
    bool                    m_scissorTestEnable;
    pUint32                 m_scissorLeft;
    pUint32                 m_scissorBottom;
    pUint32                 m_scissorWidth;
    pUint32                 m_scissorHeight;
    pUint32                 m_viewportLeft;
    pUint32                 m_viewportBottom;
    pUint32                 m_viewportWidth;
    pUint32                 m_viewportHeight;
    bool                    m_colorBufferClear;
    bool                    m_depthBufferClear;
    bool                    m_stencilBufferClear;
    PFrameBuffer    *m_framebuffer;
};


#endif // !PRENDERTARGET_H
