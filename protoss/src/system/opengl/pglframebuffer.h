// pglframebuffer.h
// The framebuffer object.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Jihao Xu xujihao@cooee.cn
// 


#ifndef PGLFRAMEBUFFER_H
#define PGLFRAMEBUFFER_H

#include <PSystem/pgltexture.h>


class PGlTexture;

class P_DLLEXPORT PGlFramebuffer
{
public:
    PGlFramebuffer();
    ~PGlFramebuffer();

    // Create the framebuffer and the texture with the given size.
    // Create depthbuffer and stencilbuffer for depth and stencil storage.
    // Check framebuffer status if error.
    bool create(pUint32 width, pUint32 height, PGlTextureFormatEnum colorFormat, 
             PGlTextureFormatEnum depthFormat, PGlTextureFormatEnum stencilFormat);

    // Enable the framebuffer when render.
    void enable();
    void disable();
    
    P_INLINE const PGlTexture *getColorBuffer() const { return m_colorBuffer; }
    P_INLINE const PGlTexture *getDepthBuffer() const  { return m_depthBuffer; }   
    P_INLINE const PGlTexture *getStencilBuffer() const { return m_stencilBuffer; } 

private:
    pUint32 getDefaultFramebufferHandle() const;
    bool checkFramebufferStatus();
private:
    PGlTexture      *m_colorBuffer;
    PGlTexture      *m_depthBuffer;
    PGlTexture      *m_stencilBuffer;

    pUint32         m_framebuffer;
    
    // REVIEW+DONE(lihw): add a enable flag.
    bool            m_enabled;
};

#endif // !PGLFRAMEBUFFER_H
