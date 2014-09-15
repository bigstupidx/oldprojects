// ptexture.h
// The texture resource
// 
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "ptexture.h"

#include <PCore/pimage.h>

#include <PSystem/pgltexture.h>


PTexture::PTexture(const pChar *path, PResourceManager* resourceManager) 
    : PResourceObject(path, resourceManager, P_RESOURCE_MANAGED, P_RESOURCE_TEXTURE)
#if defined P_TEXTURE_CACHE_IMAGE
    , m_image(path)
#endif
{
    m_textureObject = createTexture();
    if (m_textureObject == P_NULL)
    {
        m_textureObject = createDefaultTexture();
    }
}

PTexture::~PTexture()
{
    pDelete(m_textureObject);
}

pUint32 PTexture::getTextureBytes() const
{
    if (m_textureObject != P_NULL)
    {
        return m_textureObject->getBytes();
    }

    return 0;
}
    
void PTexture::setMipmapEnabled(bool enabled)
{
    if (m_textureObject != P_NULL && enabled)
    {
        m_textureObject->setMipmapEnabled(enabled);
    }
}

bool PTexture::isMipmap() const
{
    if (m_textureObject != P_NULL)
    {
        return m_textureObject->isMipmap();
    }

    return false;
}

void PTexture::setLinearFilteringEnabled(bool enabled)
{
    if (m_textureObject != P_NULL)
    {
        if (enabled)
        {
            m_textureObject->setFiltering(P_GLTEXTURE_FILTERING_LINEAR, 
                                          P_GLTEXTURE_FILTERING_LINEAR);
        }
        else 
        {
            m_textureObject->setFiltering(P_GLTEXTURE_FILTERING_NEAREST, 
                                          P_GLTEXTURE_FILTERING_NEAREST);
        }
    }
}

void PTexture::discardResource()
{
    pDelete(m_textureObject);
}

void PTexture::restoreResource()
{
    pAssert(m_textureObject == P_NULL);
    if (m_textureObject == P_NULL)
    {
        m_textureObject = createTexture();
    }
    else
    {
        pLogError("Texture %s resumed but old texture is not discarded");
    }
}
    
PGlTexture* PTexture::createTexture(const PImage& image)
{
    PGlTexture* ret = pNew(PGlTexture);
    switch (image.getPixelFormat())
    {
        case P_IMAGE_PIXELFORMAT_RGBA8888:
            if (!ret->create(image.getData(), image.getWidth(), image.getHeight(),
                    P_GLTEXTURE_FORMAT_RGBA8888))
            {
                pDelete(ret);
                return P_NULL;
            }
            break;
        case P_IMAGE_PIXELFORMAT_RGB888:
            if (!ret->create(image.getData(), image.getWidth(), image.getHeight(),
                    P_GLTEXTURE_FORMAT_RGB888))
            {
                pDelete(ret);
                return P_NULL;
            }
            break;
        case P_IMAGE_PIXELFORMAT_R8:
            if (!ret->create(image.getData(), image.getWidth(), image.getHeight(),
                    P_GLTEXTURE_FORMAT_R8))
            {
                pDelete(ret);
                return P_NULL;
            }
            break;
        default:
            pLogError("Unsupported image pixel format");
            pDelete(ret);
            return P_NULL;
    }

    return ret;
}

PGlTexture* PTexture::createTexture()
{
    // FIXME: Caching image will double the memory footprint as we have one GPU
    // and one CPU copy of image. It will likely slow down the runtime speed
    // because of memory thrusting. However, I agree with you it might be a
    // useful optimization when less restoring time is more valuable than the
    // larger memory consumption. I left another branch of image caching here.
#if defined P_TEXTURE_CACHE_IMGAE
    if (m_image.getData() == P_NULL)
    {
        pLogError("Failed to open %s for creating texture", m_name.c_str());
        return P_NULL;
    }

#else
    PImage image(m_name.c_str());
    if (image.getData() == P_NULL)
    {
        pLogError("Failed to open %s for creating texture", m_name.c_str());
        return P_NULL;
    }
    
    PGlTexture* ret = createTexture(image);
#endif // P_TEXTURE_CACHE_IMGAE

    if (ret == P_NULL)
    {
        pLogError("Failed to create texture %s", m_name.c_str());
    }

    return ret;
}

PGlTexture* PTexture::createDefaultTexture()
{
    const pUint32 imageWidth = 64;
    const pUint32 imageHeight = 64;
    pUint8* imageData = pNewArray(pUint8 [imageWidth * imageHeight * 3]);

    // Create a chessboard pattern.
    for (pUint32 i = 0; i < imageHeight / 8; ++i)
    {
        for (pUint32 j = 0; j < imageWidth / 8; ++j)
        {
            for (pUint32 y = 0; y < 8; ++y)
            {
                for (pUint32 x = 0; x < 8; ++x)
                {
                    pUint32 posx = j * 8 + x;
                    pUint32 posy = i * 8 + y;

                    pUint32 index = posy * 64 + posx;

                    pUint8 c = 255;
                    if ((i + j) % 2 == 0)
                    {
                        c = 127;
                    }

                    imageData[index * 3] = c;
                    imageData[index * 3 + 1] = c;
                    imageData[index * 3 + 2] = c;
                }
            }
        }
    }


    PImage image(imageData, imageWidth, imageHeight, P_IMAGE_PIXELFORMAT_RGB888);

    pDeleteArray(imageData);

    PGlTexture* ret = createTexture(image);
    if (ret == P_NULL)
    {
        pLogError("Failed to create default texture");
    }

    return ret;
}
