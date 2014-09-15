// pcolorrgba.cpp
// The RGBA color structure
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pcolorrgba.h"

#include <PSystem/pdebug.h>

const PColorRGBA P_COLOR_BLACK_TRANSPARENT = PColorRGBA((pUint8)0, 0, 0, 0);
const PColorRGBA P_COLOR_BLACK             = PColorRGBA((pUint8)0, 0, 0, 255);
const PColorRGBA P_COLOR_DARK_GRAY         = PColorRGBA((pUint8)50, 50, 50, 255);
const PColorRGBA P_COLOR_GRAY              = PColorRGBA((pUint8)100, 100, 100, 255);
const PColorRGBA P_COLOR_WHITE             = PColorRGBA((pUint8)255, 255, 255, 255);
const PColorRGBA P_COLOR_RED               = PColorRGBA((pUint8)255, 0, 0, 255);
const PColorRGBA P_COLOR_GREEN             = PColorRGBA((pUint8)0, 255, 0, 255); 
const PColorRGBA P_COLOR_BLUE              = PColorRGBA((pUint8)0, 0, 255, 255); 
const PColorRGBA P_COLOR_YELLOW            = PColorRGBA((pUint8)255, 255, 0, 255); 
const PColorRGBA P_COLOR_ORANGE            = PColorRGBA((pUint8)255, 127, 0, 255); 
const PColorRGBA P_COLOR_LIME              = PColorRGBA((pUint8)127, 255, 0, 255);
const PColorRGBA P_COLOR_TEAL              = PColorRGBA((pUint8)0, 255, 255, 255); 
const PColorRGBA P_COLOR_PURPLE            = PColorRGBA((pUint8)255, 0, 255, 255); 
const PColorRGBA P_COLOR_PINK              = PColorRGBA((pUint8)255, 0, 127, 255); 
const PColorRGBA P_COLOR_CYAN              = PColorRGBA((pUint8)0, 255, 255, 255); 

#define FLOAT32_TO_UINT8(a) ((pUint8)((a) * 255.0f))

PColorRGBA::PColorRGBA()
{
    m_rgba[0] = 0;
    m_rgba[1] = 0;
    m_rgba[2] = 0;
    m_rgba[3] = 0;
}

PColorRGBA::PColorRGBA(pFloat32 r, pFloat32 g, pFloat32 b, pFloat32 a)
{
    pAssert(r >= 0 && r <= 1);
    pAssert(g >= 0 && g <= 1);
    pAssert(b >= 0 && b <= 1);
    pAssert(a >= 0 && a <= 1);

    m_rgba[0]   = FLOAT32_TO_UINT8(r);
    m_rgba[1] = FLOAT32_TO_UINT8(g);
    m_rgba[2]  = FLOAT32_TO_UINT8(b);
    m_rgba[3] = FLOAT32_TO_UINT8(a);
}

PColorRGBA::PColorRGBA(pUint8 r, pUint8 g, pUint8 b, pUint8 a)
{
    m_rgba[0] = r;
    m_rgba[1] = g;
    m_rgba[2] = b;
    m_rgba[3] = a;
}

PColorRGBA::PColorRGBA(const pFloat32* rgba)
{
    pAssert(rgba[0] >= 0 && rgba[0] <= 1);
    pAssert(rgba[1] >= 0 && rgba[1] <= 1);
    pAssert(rgba[2] >= 0 && rgba[2] <= 1);
    pAssert(rgba[3] >= 0 && rgba[3] <= 1);

    m_rgba[0] = FLOAT32_TO_UINT8(rgba[0]);
    m_rgba[1] = FLOAT32_TO_UINT8(rgba[1]);
    m_rgba[2] = FLOAT32_TO_UINT8(rgba[2]);
    m_rgba[3] = FLOAT32_TO_UINT8(rgba[3]);
}

PColorRGBA::PColorRGBA(const pUint8* rgba)
{
    m_rgba[0]  = rgba[0];
    m_rgba[1]  = rgba[1];
    m_rgba[2]  = rgba[2];
    m_rgba[3]  = rgba[3];
}

bool PColorRGBA::operator==(const PColorRGBA& right) const
{
    return m_rgba[0] == right.m_rgba[0] && m_rgba[1] == right.m_rgba[1] &&
        m_rgba[2] == right.m_rgba[2] && m_rgba[3] == right.m_rgba[3];
}

pUint8 PColorRGBA::getR() const
{
    return m_rgba[0];
}

pUint8 PColorRGBA::getG() const
{
    return m_rgba[1];
}

pUint8 PColorRGBA::getB() const
{
    return m_rgba[2];
}

pUint8 PColorRGBA::getA() const
{
    return m_rgba[3];
}

pFloat32 PColorRGBA::getRFloat() const
{
    return (pFloat32)m_rgba[0] * (1.0f / 255.0f);
}

pFloat32 PColorRGBA::getGFloat() const
{
    return (pFloat32)m_rgba[1] * (1.0f / 255.0f);
}

pFloat32 PColorRGBA::getBFloat() const
{
    return (pFloat32)m_rgba[2] * (1.0f / 255.0f);
}

pFloat32 PColorRGBA::getAFloat() const
{
    return (pFloat32)m_rgba[3] * (1.0f / 255.0f);
}

void PColorRGBA::setR(pUint8 red)
{
    m_rgba[0] = red;
}

void PColorRGBA::setG(pUint8 green)
{
    m_rgba[1] = green;
}

void PColorRGBA::setB(pUint8 blue)
{
    m_rgba[2] = blue;
}

void PColorRGBA::setA(pUint8 alpha)
{
    m_rgba[3] = alpha;
}

void PColorRGBA::setRFloat(pFloat32 red)
{
    m_rgba[0] = FLOAT32_TO_UINT8(red);
}

void PColorRGBA::setGFloat(pFloat32 green)
{
    m_rgba[1] = FLOAT32_TO_UINT8(green);
}

void PColorRGBA::setBFloat(pFloat32 blue)
{
    m_rgba[2] = FLOAT32_TO_UINT8(blue);
}

void PColorRGBA::setAFloat(pFloat32 alpha)
{
    m_rgba[3] = FLOAT32_TO_UINT8(alpha);
}

void PColorRGBA::getRGBA(pUint8* c) const
{
    c[0] = m_rgba[0];
    c[1] = m_rgba[1];
    c[2] = m_rgba[2];
    c[3] = m_rgba[3];
}

void PColorRGBA::getRGBAFloat(pFloat32* c) const
{
    c[0] = (pFloat32)m_rgba[0] * (1.0f / 255.0f);
    c[1] = (pFloat32)m_rgba[1] * (1.0f / 255.0f);
    c[2] = (pFloat32)m_rgba[2] * (1.0f / 255.0f);
    c[3] = (pFloat32)m_rgba[3] * (1.0f / 255.0f);
}

void PColorRGBA::setRGBA(const pUint8* c)
{
    m_rgba[0] = c[0];
    m_rgba[1] = c[1];
    m_rgba[2] = c[2];
    m_rgba[3] = c[3];
}

void PColorRGBA::setRGBAFloat(const pFloat32* c)
{
    m_rgba[0] = FLOAT32_TO_UINT8(c[0]);
    m_rgba[1] = FLOAT32_TO_UINT8(c[1]);
    m_rgba[2] = FLOAT32_TO_UINT8(c[2]);
    m_rgba[3] = FLOAT32_TO_UINT8(c[3]);
}
    
void PColorRGBA::setRGBA(pUint8 red, pUint8 green, pUint8 blue, pUint8 alpha)
{
    m_rgba[0] = red;
    m_rgba[1] = green;
    m_rgba[2] = blue;
    m_rgba[3] = alpha;
}

void PColorRGBA::setRGBAFloat(pFloat32 red, pFloat32 green, pFloat32 blue, pUint8 alpha)
{
    m_rgba[0] = FLOAT32_TO_UINT8(red);
    m_rgba[1] = FLOAT32_TO_UINT8(green);
    m_rgba[2] = FLOAT32_TO_UINT8(blue);
    m_rgba[3] = FLOAT32_TO_UINT8(alpha);
}

const pUint8* PColorRGBA::getRGBA() const
{
    return m_rgba;
}

pUint8* PColorRGBA::getRGBA()
{
    return m_rgba;
}


#undef FLOAT32_TO_UINT8
