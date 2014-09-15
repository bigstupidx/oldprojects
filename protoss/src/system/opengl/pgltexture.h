// pgltexture.h
// The OpenGL texture
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com

#ifndef PGLTEXTURE_H
#define PGLTEXTURE_H


#include <PGlobal/pglobal.h>

enum PGlTextureFilteringEnum
{
    P_GLTEXTURE_FILTERING_NEAREST,
    P_GLTEXTURE_FILTERING_LINEAR,
};

enum PGlTextureFormatEnum 
{
    P_GLTEXTURE_FORMAT_RGBA8888,
    P_GLTEXTURE_FORMAT_RGB888,
    P_GLTEXTURE_FORMAT_RA88,
    P_GLTEXTURE_FORMAT_R8,
    P_GLTEXTURE_FORMAT_UNKNOWN,

    P_GLTEXTURE_FORMAT_FIRST = P_GLTEXTURE_FORMAT_RGBA8888,
    P_GLTEXTURE_FORMAT_LAST = P_GLTEXTURE_FORMAT_UNKNOWN,
    P_GLTEXTURE_FORMAT_NUMBER = P_GLTEXTURE_FORMAT_LAST - P_GLTEXTURE_FORMAT_FIRST,
};

class P_DLLEXPORT PGlTexture
{
public:
    PGlTexture();
    ~PGlTexture();

    bool create(pUint8 *data, pUint32 width, pUint32 height, PGlTextureFormatEnum format);
    bool create(pUint8 *data, pUint32 size, PGlTextureFormatEnum foramt);
    bool create(pUint8 **data, pUint32 width, pUint32 height, PGlTextureFormatEnum format);
    bool create(pUint8 **data, pUint32 size, PGlTextureFormatEnum foramt);
    void setMipmapEnabled(bool enabled);
    void setFiltering(PGlTextureFilteringEnum minFiltering, 
        PGlTextureFilteringEnum magFiltering);

    P_INLINE bool isCompressed() const { return m_compressed; }
    P_INLINE bool isMipmap() const { return m_mipmap; }
    P_INLINE pUint32 getBytes() const { return m_bytes; }
    P_INLINE pUint32 getTextureHandle() const { return m_texture; }

    bool isCubeMap() const; 

    void enable(pUint32 textureUnit);
    void disable();

private:
    void setFilteringInternal(PGlTextureFilteringEnum minFiltering, 
        PGlTextureFilteringEnum magFiltering);
    void setMipmapInternal(bool mipmap);
    void interpretFormat(PGlTextureFormatEnum format, 
        pUint32 &internalFormat,
        pUint32 &dataFormat);

private:
    pUint32 m_texture;  
    pUint32 m_target; // E.g., GL_TEXTURE_2D
    bool    m_compressed; // Is it a compressed texture?
    pUint32 m_bytes; // The size of texture data.
    PGlTextureFilteringEnum m_minFiltering;
    PGlTextureFilteringEnum m_magFiltering;
    bool    m_mipmap; // Is it a mipmap texture?
    bool    m_enabled; // If this texture is used by some shader right now.
};


#endif // !PGLTEXTURE_H
