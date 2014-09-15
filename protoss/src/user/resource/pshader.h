// pshader.h
// The shader resource
// 
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PSHADER_H
#define PSHADER_H


#include <PUser/pdata.h>
#include <PUser/presourceobject.h>

#include <PCore/pstring.h>


class PGlShader;
struct PGlShaderUniform;

class P_DLLEXPORT PShader : public PResourceObject, public PData 
{
    friend class PResourceManager;

private:
    PShader(const pChar *name, const pChar* vertexSourcePath, 
        const pChar *fragmentSourcePath, PResourceManager *resourceManager); 
    virtual ~PShader();
    PShader(const PShader& other) : PResourceObject(P_NULL, P_NULL) {};
    void operator=(PShader& other) {};

protected:
    virtual void discardResource();
    virtual void restoreResource();

private:
    PGlShader *m_shaderObject;
    PString    m_vertexSourcePath;
    PString    m_fragmentSourcePath;

    // Compile shader from the vertex and fragment source path.
    PGlShader* compileShader();
    // Compile shader from the vertex and fragmenh source.
    PGlShader* compileShader(const pChar* vertexSource, const pChar *fragmentSource, 
        const pChar **attributes);
    // Compile a default shader when the one failed to compile
    PGlShader* compileDefaultShader();
    // Create a property from the OpenGL uniform information.
    PAbstractProperty* createUniformProperty(const PGlShaderUniform *uniform);
};



#endif // !PSHADER_H



