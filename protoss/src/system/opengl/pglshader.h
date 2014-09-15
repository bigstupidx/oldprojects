// pglshader.h
// OpenGL Shader wrapper.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 

#ifndef PGLSHADER_H
#define PGLSHADER_H

#include <PGlobal/pglobal.h>

enum PGlShaderUniformTypeEnum
{
    P_GLSHADERUNIFORM_FLOAT,
    P_GLSHADERUNIFORM_FLOAT2,
    P_GLSHADERUNIFORM_FLOAT3,
    P_GLSHADERUNIFORM_FLOAT4,
    P_GLSHADERUNIFORM_INT,
    P_GLSHADERUNIFORM_INT2,
    P_GLSHADERUNIFORM_INT3,
    P_GLSHADERUNIFORM_INT4,
    P_GLSHADERUNIFORM_BOOL,
    P_GLSHADERUNIFORM_BOOL2,
    P_GLSHADERUNIFORM_BOOL3,
    P_GLSHADERUNIFORM_BOOL4,
    P_GLSHADERUNIFORM_FLOATMATRIX2X2,
    P_GLSHADERUNIFORM_FLOATMATRIX3X3,
    P_GLSHADERUNIFORM_FLOATMATRIX4X4,
    P_GLSHADERUNIFORM_SAMPLER2D,
    P_GLSHADERUNIFORM_SAMPLERCUBE,
};

struct P_DLLEXPORT PGlShaderUniform
{
    pUint32 m_index;
    pUint32 m_location;
    pChar m_name[1024];
    PGlShaderUniformTypeEnum m_type;
};


class P_DLLEXPORT PGlShader
{
public:
    // Constructor
    PGlShader();

    // Destructor
    ~PGlShader();

    // Compile and link shader code. The programming of shader source should
    // conform to Kiwi OpenGL Shader Guideline. It doesn't affect the current
    // shader in the pipeline.
    bool compile(const pChar* vertexProgramSource, 
        const pChar* fragmentProgramSource,
        const pChar** attributeNames);

#if defined P_OPENGL_BINARY_PROGRAM_ENABLED
    // Load program binary into a program object. It doesn't affect the current
    // shader in the pipeline.
    bool programBinary(pUint32 binaryFormat, const void* binary, pInt32 length);

    // Dump program binary to a string. 
    bool getProgramBinary(pUint32* binaryFormat, void** binary, pInt32* length);
#endif

    // Bind this shader object to the pipeline. 
    // \return true when succeed
    void enable();

    // Disable this shader.
    void disable();

    // Use default shader 0 on the pipeline.
    void useDefault();

    // Check if this shader is phony
    bool isPhony() const;

    // Get the location of certain uniforms.
    pInt32 getUniformLocation(const pChar* name);

    /// Update the value of the uniform when it is different from the current
    /// one in this shader object. If the shader is not current one in the pipeline,
    /// the value is uploaded to GPU when the shader is bound to pipeline. 
    void uniform(pInt32 location, pFloat32 x);
    void uniform(pInt32 location, pFloat32 x, pFloat32 y);
    void uniform(pInt32 location, pFloat32 x, pFloat32 y, pFloat32 z);
    void uniform(pInt32 location, pFloat32 x, pFloat32 y, pFloat32 z, pFloat32 w);
    void uniform(pInt32 location, pInt32 x);
    void uniform(pInt32 location, pInt32 x, pInt32 y);
    void uniform(pInt32 location, pInt32 x, pInt32 y, pInt32 z);
    void uniform(pInt32 location, pInt32 x, pInt32 y, pInt32 z, pInt32 w);
    void uniform(pInt32 location, const pFloat32* value);

    // Get the number of active uniforms in this shader object.
    pUint32 getNumberOfUniforms();

    // Get the information of the uniform at certain index.
    PGlShaderUniform getUniformInformation(pUint32 index);

private:
    pUint32 m_program;   // OpenGL program object. When this value is 0, it is a null shader. 
    bool m_enabled; // If it is currently bound to the pipeline.
};

#endif // !PGLSHADER_H
