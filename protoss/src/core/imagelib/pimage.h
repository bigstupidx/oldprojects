// pimage.h
// The image object.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PIMAGE_H
#define PIMAGE_H

#include <PGlobal/pglobal.h>

enum PImagePixelFormatEnum 
{
    P_IMAGE_PIXELFORMAT_RGBA8888,
    P_IMAGE_PIXELFORMAT_RGB888,
    P_IMAGE_PIXELFORMAT_RA88,
    P_IMAGE_PIXELFORMAT_R8,
    P_IMAGE_PIXELFORMAT_UNKNOWN,

    P_IMAGE_PIXELFORMAT_FIRST = P_IMAGE_PIXELFORMAT_RGB888,
    P_IMAGE_PIXELFORMAT_LAST = P_IMAGE_PIXELFORMAT_UNKNOWN,
    P_IMAGE_PIXELFORMAT_NUMBER = P_IMAGE_PIXELFORMAT_LAST - P_IMAGE_PIXELFORMAT_LAST + 1,
};

class P_DLLEXPORT PImage
{
public:
    PImage();
    PImage(const pChar *path);
    PImage(const pUint8 *data, pUint32 width, pUint32 height, 
        PImagePixelFormatEnum pixelFormat);
    PImage(const PImage& other);
    ~PImage();
    
    const PImage& operator=(const PImage& other);

    P_INLINE pUint8* getData() const { return m_data; }
    P_INLINE pUint32 getWidth() const { return m_width; }
    P_INLINE pUint32 getHeight() const { return m_height; }
    P_INLINE pUint32 getPixelFormat() const { return m_pixelFormat; }
    P_INLINE pUint32 getBPP() const { return getBPP(m_pixelFormat); }

    static pUint32 getBPP(PImagePixelFormatEnum pixelFormat);


private:
    pUint8                *m_data;
    pUint32                m_width;
    pUint32                m_height;
    PImagePixelFormatEnum  m_pixelFormat;
};

#endif // !PIMAGE_H
