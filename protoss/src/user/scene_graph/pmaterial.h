// pmaterial.h
// The material describes the appearance of drawable objects. It is
// composed of a shader and a set of parameters.
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//
// 

#ifndef PMATERIAL_H
#define PMATERIAL_H


#include <PGlobal/pglobal.h>
    
// DESIGN GUIDELINE(to be deleted after finishing)
//
// Usage 1:
// PShader* shader = context->getResourceManager()->retainShader("vert.glsl", "frag.glsl");
// drawable->getMaterial()->setShader(shader);
// drawable->getMaterial()->setCameraMatrix(camera->getCameraMatrix());
// drawable->getMaterial()->setProjectionMatrix(camera->getWorldMatrix());
// drawable->getMaterial()->parameter("aUniform") = a;
// drawable->getMaterial()->parameter("bUniform") = b;
// PTexture* texture = context->getResourceManager()->retainTexture("texture.png");
// drawable->getMaterial()->texture("aTexture") = texture;
//
// Usage 2:
// PList<PMaterialParameter*> parameters = drawable->getMaterial()->listParameters();
// PList<PMaterialTexture*> textures = drawable->getMaterial()->listTextures();
//
// Usage 3(Inside PDrawable's render function):
// material->use(renderState);

class PRenderState;


class P_DLLEXPORT PMaterialParameter
{
    friend class PMaterial;

private:
    // The constructor can only be provoked by PMaterial.
    PMaterialParameter(const pChar *name);
    ~PMaterialParameter();
    PMaterialParameter(const PMaterialParameter &other) {};
    void operator=(const PMaterialParameter &other) {};

public:
    // Assign the value to the internal. If the current material
    // parameter's type is not for the input one, say a float 
    // parameter takes a 4-component vector, it can ignore the
    // request and print a warning. 
    // When the value is changed, a dirty bit is turned on to remind
    // us to upload this parameter to GPU next time.
    void operator=(pUint32 x);
    void operator=(const pIVector2 &v);
    void operator=(const pIVector3 &v);
    void operator=(const pIVector4 &v);
    void operator=(pFloat32 x);
    void operator=(const pVector2 &v);
    void operator=(const pVector3 &v);
    void operator=(const pVector4 &v);
    void operator=(const pMatrix4x4 &m);

    // Return the type of this parameter.
    PPropertyTypeEnum getType() const;

private:
    // Upload the parameter value from CPU to GPU. Only 
    // do those parameter which are marked dirty.
    void upload();

private:
    PProperty    *m_property;
    const pChar  *m_name;
    pUint32       m_location;
    bool          m_dirty;
};


class P_DLLEXPORT PMaterialTexture
{
    friend class PMaterial;

private:
    // PMaterialTexture constructor can only be called by PMaterial.
    PMaterialTexture(const pChar *name, pUint32 textureUint);
    ~PMaterialTexture();
    PMaterialTexture(const PMaterialTexture &other) {};
    void operator=(const PMaterialTexture &other) {};

public:
    void operator=(pTexture* texture);

private:
    // Upload the name
    void upload();

private:
    pTexture     *m_texture;
    const pChar  *m_name;
    pUint32       m_location;
    pUint32       m_textureUnit; // The texture unit this texture will bound to.
    bool          m_dirty;
};


class P_DLLEXPORT PMaterial 
{
    friend class PDrawable;

private:
    // The PMaterial can only be called by PDrawable 
    PMaterial();
    ~PMaterial();
    PMaterial(const PMaterial& other) {};
    void operator=(const PMaterial& other) {};

public:

    // Set the shader of this material. When material's shader is changed, its cached
    // parameters are also needed to be updated to those of the current one.
    void setShader(PShader *shader);

    // There three matrices can be set directly without resorting to parameter(). It is necessary
    // for shader writer to use pre-defined name for these three matrices.
    // E.g., pWorldMatrix pCameraMatrix and pProjectionMatrix.
    void setCameraMatrix(const pFloat32* matrix);
    void setProjectionMatrix(const pFloat32* matrix);
    void setWorldMatrix(const pFloat32* matrix);

    // Fetch the parameter with given name. It returns null when no such parameter exists or
    // shader is null in this material.
    PMaterialParameter* parameter(const pChar *name) const;
    // Ditto.
    PMaterialTexture* texture(const pChar *name) const;

private:
    // Use the current shader and upload parameters to GPU.
    void use(PRenderState* renderState);

private:
    // TODO: use a more effect data structure for searching, like map.
    PArray<PMaterialParameter*>  m_parameters;
    PArray<PMaterialTexture*>    m_textures;

    PMaterialParameter          *m_cameraMatrix;
    PMaterialParameter          *m_projectionMatrix;
    PMaterialParameter          *m_worldMatrix;
};


#endif // !PMATERIAL_H
