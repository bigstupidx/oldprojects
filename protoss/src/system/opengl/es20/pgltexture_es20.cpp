// pgltexture_es20.cpp
// The OpenGL texture
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com

#include "../pgltexture.h"

#include <PSystem/pglerror.h>
#include <PSystem/pdebug.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h> 


PGlTexture::PGlTexture()
{
    m_texture = 0;
    m_target = 0;
    m_compressed = false;
    m_mipmap = false;
    m_minFiltering = P_GLTEXTURE_FILTERING_NEAREST;
    m_magFiltering = P_GLTEXTURE_FILTERING_NEAREST;
    m_enabled = false;
    m_bytes = 0;
}

PGlTexture::~PGlTexture()
{
    if (m_texture != 0)
    {
        glDeleteTextures(1, &m_texture);

        pGlErrorCheckWarning();
    }
}

bool PGlTexture::create(pUint8* data, pUint32 size, PGlTextureFormatEnum format)
{
    m_target = GL_TEXTURE_2D;
    m_compressed = true;

    return false;
}

bool PGlTexture::create(pUint8* data, pUint32 width, pUint32 height, 
    PGlTextureFormatEnum format)
{
    // We can't overwrite an existing texture.
    if (m_texture != 0)
    {
        pLogWarning("Texture can't be overwritten");
        return false;
    }

    glGenTextures(1, &m_texture);

    m_target = GL_TEXTURE_2D;
    m_compressed = false;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(m_target, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Use the same texture format for internalFormat and format in OpenGL ES 2.0.
    pUint32 internalFormat;
    pUint32 dataFormat;
    interpretFormat(format, internalFormat, dataFormat);

    // Compute the size of the texture
    switch (format)
    {
        case P_GLTEXTURE_FORMAT_R8: m_bytes = width * height; break;
        case P_GLTEXTURE_FORMAT_RA88: m_bytes = width * height * 2; break;
        case P_GLTEXTURE_FORMAT_RGB888: m_bytes = width * height * 3; break;
        case P_GLTEXTURE_FORMAT_RGBA8888: m_bytes = width * height * 4; break;
        default:
            pAssert(!"Unsupported OpenGL texture format");
            pLogError("Unsupported OpenGL texture format");
            glDeleteTextures(1, &m_texture);
            return false;
    }

    if (m_mipmap)
    {
        m_bytes += m_bytes / 3;
    }

    // Create the OpenGL texture object.
    glTexImage2D(GL_TEXTURE_2D, 
                 0, 
                 internalFormat, 
                 width, 
                 height, 
                 0, 
                 dataFormat, 
                 GL_UNSIGNED_BYTE, 
                 data);
    
    setMipmapInternal(m_mipmap);
    
    setFilteringInternal(m_minFiltering, m_magFiltering);

    glBindTexture(m_target, 0);

    pGlErrorCheckAbort();

    return true;
}
    
bool PGlTexture::create(pUint8 **data, pUint32 width, pUint32 height, PGlTextureFormatEnum format)
{
    m_target = GL_TEXTURE_CUBE_MAP;
    m_compressed = false;

    return true;
}

bool PGlTexture::create(pUint8 **data, pUint32 size, PGlTextureFormatEnum foramt)
{
    m_target = GL_TEXTURE_CUBE_MAP;
    m_compressed = true;

    return false;
}
    
bool PGlTexture::isCubeMap() const
{
    return m_target == GL_TEXTURE_CUBE_MAP;
}

void PGlTexture::setMipmapEnabled(bool enabled)
{
    if (m_texture != 0)
    {
        if (!m_mipmap && enabled)
        {
            if (!m_enabled)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(m_target, m_texture);
            }

            setMipmapInternal(enabled);

            if (!m_enabled)
            {
                glBindTexture(m_target, 0);
            }

            m_bytes += m_bytes / 3;

            m_mipmap = true;
        }
    }
    else
    {
        m_mipmap = enabled;
    }
}

void PGlTexture::setFiltering(PGlTextureFilteringEnum minFiltering, 
    PGlTextureFilteringEnum magFiltering)
{
    if (m_texture != 0)
    {
        if (m_minFiltering != minFiltering ||
            m_magFiltering != magFiltering)
        {
            if (!m_enabled)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(m_target, m_texture);
            }

            setFilteringInternal(minFiltering, magFiltering);

            if (!m_enabled)
            {
                glBindTexture(m_target, 0);
            }
        }
    }

    m_minFiltering = minFiltering;
    m_magFiltering = magFiltering;
}

void PGlTexture::enable(pUint32 textureUnit)
{
    pAssert(!m_enabled);

    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(m_target, m_texture);

    m_enabled = true;

    pGlErrorCheckError();
}

void PGlTexture::disable()
{
    pAssert(m_enabled);

    m_enabled = false;
}

void PGlTexture::setFilteringInternal(PGlTextureFilteringEnum minFiltering, 
    PGlTextureFilteringEnum magFiltering)
{
    if (m_mipmap)
    {
        if (minFiltering == P_GLTEXTURE_FILTERING_NEAREST)
        {
            glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        }
        else
        {
            glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }

        if (magFiltering == P_GLTEXTURE_FILTERING_NEAREST)
        {
            glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        else
        {
            glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    }
    else
    {
        if (minFiltering == P_GLTEXTURE_FILTERING_NEAREST)
        {
            glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        }
        else
        {
            glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        if (magFiltering == P_GLTEXTURE_FILTERING_NEAREST)
        {
            glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        else
        {
            glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    }
            
    pGlErrorCheckError();
}

void PGlTexture::setMipmapInternal(bool mipmap)
{
    if (mipmap && mipmap != m_mipmap)
    {
        glGenerateMipmap(m_target);
        pGlErrorCheckError();
    }
}
    
void PGlTexture::interpretFormat(PGlTextureFormatEnum format, 
    pUint32 &internalFormat,
    pUint32 &dataFormat)
{
    switch (format)
    {
        case P_GLTEXTURE_FORMAT_RGBA8888: 
            internalFormat = GL_RGBA;
            dataFormat = GL_RGBA;
            break;
        case P_GLTEXTURE_FORMAT_RGB888: 
            internalFormat = GL_RGB;
            dataFormat = GL_RGB;
            break;
        case P_GLTEXTURE_FORMAT_R8:
            internalFormat = GL_LUMINANCE;
            dataFormat = GL_LUMINANCE;
            break;
        case P_GLTEXTURE_FORMAT_RA88:
            internalFormat = GL_LUMINANCE_ALPHA;
            dataFormat = GL_LUMINANCE_ALPHA;
            break;
        default:
            pAssert(!"Unsupported texture format");
            pLogError("Unsupported texture format");
            break;
    }
}
