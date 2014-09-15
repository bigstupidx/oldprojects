// pcolorrgba.h
// The RGBA color structure
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PCOLORRGBA_H
#define PCOLORRGBA_H

#include <PGlobal/pglobal.h>


class P_DLLEXPORT PColorRGBA 
{
public:
    // Constructors
    PColorRGBA();
    PColorRGBA(pFloat32 r, pFloat32 g, pFloat32 b, pFloat32 a);
    PColorRGBA(pUint8 r, pUint8 g, pUint8 b, pUint8 a);
    PColorRGBA(const pFloat32* rgba);
    PColorRGBA(const pUint8* rgba);

    // operator.
    bool operator==(const PColorRGBA& right) const;

    // Get color component.
    pUint8 getR() const;
    pUint8 getG() const;
    pUint8 getB() const;
    pUint8 getA() const;

    pFloat32 getRFloat() const;
    pFloat32 getGFloat() const;
    pFloat32 getBFloat() const;
    pFloat32 getAFloat() const;

    // Set the color component.
    void setR(pUint8 r);
    void setG(pUint8 g);
    void setB(pUint8 b);
    void setA(pUint8 a);
    
    void setRFloat(pFloat32 r);
    void setGFloat(pFloat32 g);
    void setBFloat(pFloat32 b);
    void setAFloat(pFloat32 a);

    // Get the whole color value
    void getRGBA(pUint8* c) const;
    void getRGBAFloat(pFloat32* c) const;
    const pUint8* getRGBA() const;
    pUint8* getRGBA();

    // Set the whole color value.
    void setRGBA(const pUint8* c);
    void setRGBAFloat(const pFloat32* c);
    void setRGBA(pUint8 red, pUint8 green, pUint8 blue, pUint8 alpha);
    void setRGBAFloat(pFloat32 red, pFloat32 green, pFloat32 blue, pUint8 alpha);


private:
    pUint8 m_rgba[4];  
};


extern const PColorRGBA KW_COLOR_BLACK_TRANSPARENT;
extern const PColorRGBA KW_COLOR_BLACK;
extern const PColorRGBA KW_COLOR_DARK_GRAY;
extern const PColorRGBA KW_COLOR_GRAY;
extern const PColorRGBA KW_COLOR_WHITE;
extern const PColorRGBA KW_COLOR_RED;
extern const PColorRGBA KW_COLOR_GREEN;
extern const PColorRGBA KW_COLOR_BLUE;
extern const PColorRGBA KW_COLOR_YELLOW;
extern const PColorRGBA KW_COLOR_ORANGE;
extern const PColorRGBA KW_COLOR_LIME;
extern const PColorRGBA KW_COLOR_TEAL;
extern const PColorRGBA KW_COLOR_PURPLE;
extern const PColorRGBA KW_COLOR_PINK;
extern const PColorRGBA KW_COLOR_CYAN;



#endif // !PCOLORRGBA_H

