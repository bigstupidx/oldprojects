// ptexture.h
// The texture resource
// 
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PTEXTURE_H
#define PTEXTURE_H


#include <PUser/presourceobject.h>

#include <PCore/pstring.h>
#include <PCore/pimage.h>


class PGlTexture;


class P_DLLEXPORT PTexture : public PResourceObject
{
    friend class PResourceManager;

private:
    PTexture(const pChar* path, PResourceManager* resourceManager); 
    virtual ~PTexture();
    PTexture(const PTexture& other) : PResourceObject(P_NULL, P_NULL) {};
    void operator=(PTexture& other) {};

public:
    bool isMipmap() const;
    void setMipmapEnabled(bool enabled);
    bool isLinearFiltering() const; 
    void setLinearFilteringEnabled(bool enabled);
    pUint32 getTextureBytes() const;

    // TODO: use

protected:
    virtual void discardResource();
    virtual void restoreResource();

private:
    PGlTexture* createTexture();
    PGlTexture* createDefaultTexture();
    PGlTexture* createTexture(const PImage& image);

private:
    PGlTexture    *m_textureObject;
#if defined P_TEXTURE_CACHE_IMAGE
    PImage         m_image;
#endif 
};



#endif // !PTEXTURE_H



