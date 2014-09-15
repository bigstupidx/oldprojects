// pimage.cpp
// The image object.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pimage.h"

#include "pimagepng_private.h"

#include <PCore/pinputstream.h>

#include <PSystem/pcrt.h>


PImage::PImage()
{
    m_width = 0;
    m_height = 0;
    m_data = P_NULL;
    m_pixelFormat = P_IMAGE_PIXELFORMAT_UNKNOWN;
}
    
PImage::PImage(const pChar *path)
{
    // Find the type of image by checking the prefix of the path.
    const pChar* prefix = pstrrchr(path, '.');
    if (pstrcmp(prefix, ".png") == 0)
    {
        PInputStream inputStream;
        if (inputStream.createFromFile(path, P_STREAM_ENDIANNESS_PLATFORM))
        {
            // Load PNG if it is.
            if (!pImagePNGRead(inputStream, m_width, m_height, m_pixelFormat, m_data))
            {
                pLogError("Failed to read PNG image %s", path);

                m_width = 0;
                m_height = 0;
                m_pixelFormat = P_IMAGE_PIXELFORMAT_UNKNOWN;
                m_data = P_NULL;
            }
        }
        else
        {
            pLogError("Failed to open %s for loading image", path);       
        }
        
    }
    // TODO: other image formats
    //else 
    //{
    //}
}


PImage::PImage(const pUint8 *data, pUint32 width, pUint32 height, 
    PImagePixelFormatEnum pixelFormat)
{
    pUint32 bpp = getBPP(pixelFormat);
    pUint32 size = width * height * bpp;
    m_data = pNewArray(pUint8 [size]);
    pmemcpy(m_data, data, size);

    m_width = width;
    m_height = height;
    m_pixelFormat = pixelFormat;
}

PImage::PImage(const PImage& other)
{
    m_width = other.m_width;
    m_height = other.m_height;
    m_pixelFormat = other.m_pixelFormat;
    m_data = P_NULL;

    if (other.m_data != P_NULL)
    {
        pUint32 bpp = getBPP(m_pixelFormat);
        pUint32 size = m_width * m_height * bpp;
        m_data = pNewArray(pUint8 [size]);
        pmemcpy(m_data, other.m_data, size);
    }
}

PImage::~PImage()
{
    pDeleteArray(m_data);
}
    
const PImage& PImage::operator=(const PImage& other)
{
    if (this != &other)
    {
        m_width = other.m_width;
        m_height = other.m_height;
        m_pixelFormat = other.m_pixelFormat;
        m_data = P_NULL;

        if (other.m_data != P_NULL)
        {
            pUint32 bpp = getBPP(m_pixelFormat);
            pUint32 size = m_width * m_height * bpp;
            m_data = pNewArray(pUint8 [size]);
            pmemcpy(m_data, other.m_data, size);
        }
    }

    return *this;
}

pUint32 PImage::getBPP(PImagePixelFormatEnum pixelFormat)
{
    switch (pixelFormat)
    {
        case P_IMAGE_PIXELFORMAT_RGBA8888: return 4;
        case P_IMAGE_PIXELFORMAT_RGB888: return 2;
        case P_IMAGE_PIXELFORMAT_R8: return 1;
        case P_IMAGE_PIXELFORMAT_UNKNOWN: return 0;
        default:
            pLogError("Unknown image pixel format");
            return 0;
    }

    return 0;
}
