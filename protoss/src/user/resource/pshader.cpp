// pshader.cpp
// The shader resource
// 
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//


#include "pshader.h"

#include <PCore/pinputstream.h>

#include <PSystem/pglshader.h>
#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>


PShader::PShader(const pChar* name, const pChar* vertexSourcePath, 
    const pChar* fragmentSourcePath, PResourceManager* resourceManager)
    : PResourceObject(name, resourceManager, P_RESOURCE_DEFAULT, P_RESOURCE_SHADER)
    , m_vertexSourcePath(vertexSourcePath)
    , m_fragmentSourcePath(fragmentSourcePath)

{
    m_shaderObject = compileShader();
    if (m_shaderObject == P_NULL)
    {
        m_shaderObject = compileDefaultShader();
    }
}


PShader::~PShader()
{
    pDelete(m_shaderObject);
}

PGlShader* PShader::compileShader()
{
    // Compile the source code
    PInputStream vertexSourceStream; 
    PInputStream fragmentSourceStream;

    if (!vertexSourceStream.createFromFile(m_vertexSourcePath.c_str(), P_STREAM_ENDIANNESS_PLATFORM) ||
        !fragmentSourceStream.createFromFile(m_fragmentSourcePath.c_str(), P_STREAM_ENDIANNESS_PLATFORM))
    {
        pLogError("Failed to open %s or %s as the source of shader %s",
            m_vertexSourcePath.c_str(),
            m_fragmentSourcePath.c_str(),
            m_name.c_str());

        return P_NULL;
    }

    // TODO: load from project in addition to storage.
    // e.g., vertex source path = ":/vertexshader.glsl"

    pUint8 *vertexSource;
    pUint8 *fragmentSource;
    pUint32 nchars;
    nchars = vertexSourceStream.readAllBytes(vertexSource);
    nchars = fragmentSourceStream.readAllBytes(fragmentSource);

    const pChar *attributes[] =
    {
        "inVertex",
        "inNormal",
        "inTexCoord",
        P_NULL,
    };

    PGlShader* ret = compileShader((pChar*)vertexSource, 
        (pChar*)fragmentSource, attributes);
    pAssert(ret != P_NULL);
    if (ret == P_NULL)
    {
        pLogError("Failed to compile shader %s", m_name.c_str());
    }
    return ret;
}

PGlShader* PShader::compileShader(const pChar* vertexSource, const pChar *fragmentSource, 
    const pChar **attributes)
{
    PGlShader* ret = pNew(PGlShader);
    if (!ret->compile((pChar*)vertexSource, (pChar*)fragmentSource, attributes))
    {
        return P_NULL;
    }

    pDeleteArray(vertexSource);
    pDeleteArray(fragmentSource);

    ret->enable();

    // Fetch the uniforms of the compiled shader.
    pUint32 nuniforms = m_shaderObject->getNumberOfUniforms();
    for (pUint32 i = 0; i < nuniforms; ++i)
    {
        PGlShaderUniform uniform = m_shaderObject->getUniformInformation(i);

        PAbstractProperty *property = createUniformProperty(&uniform);
        pAssert(property != P_NULL);
        addProperty(uniform.m_name, property);
    }

    ret->disable();

    return ret;
}


PGlShader* PShader::compileDefaultShader()
{
    // The default shader is to paint the object solid red.
     const pChar* VSCODE = 
        "attribute vec4 inVertexPosition; \n"
        "uniform mat4 projectionModelviewMatrix; \n"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_Position = projectionModelviewMatrix * inVertexPosition; \n"
        "}\n";

    const pChar* FSCODE = 
        "void main() \n"
        "{\n"
        "    gl_FragColor = vec4(1, 0, 0, 1); \n"
        "}\n";
    
    const pChar *attributes[] =
    {
        "inVertex",
        P_NULL,
    };

    PGlShader* ret = compileShader(VSCODE, FSCODE, attributes);
    pAssert(ret != P_NULL);
    if (ret == P_NULL)
    {
        pLogError("Failed to compile default shader");
    }
    return ret;
}
    
PAbstractProperty* PShader::createUniformProperty(const PGlShaderUniform *uniform)
{
    // TODO: implement
    return P_NULL;
}

void PShader::discardResource()
{
    pDelete(m_shaderObject);
}

void PShader::restoreResource()
{
    pAssert(m_shaderObject == P_NULL);
    if (m_shaderObject == P_NULL)
    {
        m_shaderObject = compileShader();
    }
    else
    {
        pLogError("Shader %s resumed but old shader is not discarded");
    }
}
