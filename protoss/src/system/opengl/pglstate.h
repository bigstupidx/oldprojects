// pglstate.h
// The OpenGL render state
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com


#ifndef PGLSTATE_H 
#define PGLSTATE_H 

#include <PCore/pcolorrgba.h>

enum PGlColorWriteModeEnum
{
    P_GLCOLORWRITE_NONE = 0x00,    ///< Color buffer is disabled.
    P_GLCOLORWRITE_R    = 0x01,
    P_GLCOLORWRITE_RG   = 0x03,
    P_GLCOLORWRITE_RGB  = 0x07,
    P_GLCOLORWRITE_RGBA = 0x0f,
    
    P_GLCOLORWRITE_DEFAULT = P_GLCOLORWRITE_RGBA,

    P_GLCOLORWRITE_FIRST = P_GLCOLORWRITE_NONE,
    P_GLCOLORWRITE_LAST = P_GLCOLORWRITE_RGBA,
    P_GLCOLORWRITE_MODE_NUMBER = P_GLCOLORWRITE_LAST - P_GLCOLORWRITE_FIRST + 1,
};

enum PGlDepthTestModeEnum
{
    P_GLDEPTHTEST_DISABLED,      ///< No depth testing.
    P_GLDEPTHTEST_UNWRITABLE,    ///< Enable the testing but depth buffer is not writable.
    P_GLDEPTHTEST_WRITABLE,     ///< Enable the testing and depth buffer is writable.

    P_GLDEPTHTEST_DEFAULT = P_GLDEPTHTEST_WRITABLE,

    P_GLDEPTHTEST_FIRST = P_GLDEPTHTEST_DISABLED,
    P_GLDEPTHTEST_LAST = P_GLDEPTHTEST_WRITABLE,
    P_GLDEPTHTEST_MODE_NUMBER = P_GLDEPTHTEST_LAST - P_GLDEPTHTEST_FIRST + 1,
};


// FIXME: As we do not have to implement stencil for the first Protoss version,
// leave the codes here and will fix them later.
// Conversations:
// // lihw: in my opinion, operation about stencil testing is more complex
// than depth testing. It might need more modes. See 4.1.4 of OpenGL ES 2.0 spec.
// xjh: thanks.
// lihw: I still have some doubts about the current design of stencil
// mode, but we can come back to this problem later. You know the stencil usage
// is complex.  I left this comment here and you can convert the whole comment
// conversation to a FIXME or TODO. 
enum PGlStencilTestModeEnum
{
    P_GLSTENCILTEST_DISABLED,      
    P_GLSTENCILTEST_BACK,    // Back stencil status set
    P_GLSTENCILTEST_FRONT,   // Front stencil status set  

    P_GLSTENCILTEST_DEFAULT = P_GLSTENCILTEST_DISABLED,

    P_GLSTENCILTEST_FIRST = P_GLSTENCILTEST_DISABLED,
    P_GLSTENCILTEST_LAST = P_GLSTENCILTEST_BACK,
    P_GLSTENCILTEST_MODE_NUMBER = P_GLSTENCILTEST_LAST - P_GLSTENCILTEST_FIRST + 1,
};

enum PGlCullModeEnum
{
    P_GLCULL_NONE,    ///< No culling. 
    P_GLCULL_BACK,    ///< Backface culling. 
    P_GLCULL_FRONT,   ///< Frontface culling. 
    
    P_GLCULL_DEFAULT = P_GLCULL_BACK,

    P_GLCULL_FIRST = P_GLCULL_NONE,
    P_GLCULL_LAST = P_GLCULL_FRONT,
    P_GLCULL_MODE_NUMBER = P_GLCULL_LAST - P_GLCULL_FIRST + 1,
};

enum PGlBlendModeEnum
{
    P_GLBLEND_OPAQUE,   ///< No blending. 
    P_GLBLEND_ALPHA,    ///< Blend source and destination color. 
    P_GLBLEND_ADDITIVE, ///< Add source to destination color

    P_GLBLEND_DEFAULT = P_GLBLEND_OPAQUE,

    P_GLBLEND_FIRST = P_GLBLEND_OPAQUE,
    P_GLBLEND_LAST = P_GLBLEND_ADDITIVE,
    P_GLBLEND_MODE_NUMBER = P_GLBLEND_LAST - P_GLBLEND_FIRST + 1,
};

enum PGlStateQueryEnum
{
    P_GLTEXTURE_UNIT_NUMBER, ///< The maximum texture unit number.
};

class P_DLLEXPORT PGlState
{
public:
    PGlState(pUint32 screenWidth, pUint32 screenHeight);
    ~PGlState();

    // Initialize or reset the state to default.
    void reset();

    void setViewport(pUint32 x, pUint32 y, pUint32 width, pUint32 height);
    void setColorWriteMode(PGlColorWriteModeEnum mode);
    void setClearColor(const PColorRGBA& color);
    void setCullMode(PGlCullModeEnum mode);
    void setScissorTestEnabled(bool enabled, pInt32 left, pInt32 bottom, pInt32 width, pInt32 height);
    void setDepthTestMode(PGlDepthTestModeEnum mode);
    void setClearDepth(pFloat32 depth);
    void setBlendMode(PGlBlendModeEnum mode);
    void setStencilTestMode(PGlStencilTestModeEnum mode);

    // TODO:
    // about stencil testing.

    void getViewport(pUint32* viewport) const;
    P_INLINE PGlColorWriteModeEnum getColorWriteMode() const
    { return m_colorWriteMode; }
    P_INLINE PGlDepthTestModeEnum getDepthTestMode() const 
    { return m_depthTestMode; }
    P_INLINE PColorRGBA getClearColor() const
    { return m_clearColor; }
    P_INLINE PGlBlendModeEnum getBlendMode() const
    { return m_blendMode; }
    P_INLINE PGlStencilTestModeEnum getStencilMode() const
    { return m_stencilMode; }



    pUint32 query(PGlStateQueryEnum flag);

    // Clear the current frame buffer.
    // TODO: move this function to PGLFrameBuffer
    void clearFramebuffer(bool colorBuffer, bool depthBuffer, bool stencilBuffer);

protected:
    pUint32                      m_screenWidth; // The surface width and height
    pUint32                      m_screenHeight;
    pUint32                      m_viewport[4]; // The viewport
    PGlColorWriteModeEnum        m_colorWriteMode; // Color mask 
    PColorRGBA                   m_clearColor; // Clear color
    PGlDepthTestModeEnum         m_depthTestMode; // Depth 
    pFloat32                     m_clearDepth;
    bool                         m_scissorTestEnabled; /// Scissor 
    pInt32                       m_scissor[4];
    PGlBlendModeEnum             m_blendMode; /// Blend 
    PGlCullModeEnum              m_cullMode; /// Cull
    PGlStencilTestModeEnum      m_stencilMode;  // Stencil
};



#endif // !PGLSTATE_H

