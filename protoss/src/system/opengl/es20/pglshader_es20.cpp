// pglshader_es20.cpp
// OpenGL shader wrapper.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 

#include "../pglshader.h"

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>
#include <PSystem/pglerror.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h> 


PGlShader::PGlShader()
{
    m_program   = 0;
    m_enabled   = false;
}

PGlShader::~PGlShader()
{
    // detach  the shader from pipeline first. 
    if (m_enabled && m_program != 0)
    {
        glUseProgram(0);
    }
    
    // Delete the program. 
    if (m_program != 0)
    {
        glDeleteProgram(m_program);
    }
    
    pGlErrorCheckWarning();
}

bool PGlShader::compile(const pChar* vertexProgramSource, 
    const pChar* fragmentProgramSource,
    const pChar** attributeNames)
{
    GLint compiled;

    // If it is already loaded.
    if (m_program != 0)
    {
        pLogWarning("Can't modify an existing shader program");
        return false;
    }

    // Compile the vertex shader. 
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const char **)&vertexProgramSource, 0);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint logLength, charsWritten;

        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

        pChar* log = pNewArray(pChar[logLength + 1]);

        glGetShaderInfoLog(vertexShader, logLength, &charsWritten, log);

        pLogError("Vertex shader compile failed");
        pLogInfo(log);

        pDeleteArray(log);
            
        // Release the resource and return. 
        glDeleteShader(vertexShader);

        return false;
    }
    
    // Compile fragment source. 
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const char **)&fragmentProgramSource, 0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint logLength, charsWritten;

        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

        pChar* log = pNewArray(pChar[logLength + 1]);
        glGetShaderInfoLog(fragmentShader, logLength, &charsWritten, log);

        pLogError("Fragment shader compile failed");
        pLogInfo(log);

        pDeleteArray(log);
            
        // Release the reSource and return. 
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

        return false;
    }
    
    // Create the OpenGL program object. 
    m_program = glCreateProgram();

    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);

    // Bind the attribute locations. 
    pInt32 i = 0; 
    while (attributeNames[i] != P_NULL)
    {
        glBindAttribLocation(m_program, i, attributeNames[i]);
        i++;
    }

    // Link the shaders. 
    glLinkProgram(m_program);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    GLint linked;
    glGetProgramiv(m_program, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        GLint logLength, charsWritten;

        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);

        pChar * log = pNewArray(pChar[logLength + 1]);
        glGetProgramInfoLog(m_program, logLength, &charsWritten, log);

        pLogError("shader linking failed");
        pLogInfo(log);

        pDeleteArray(log);

        // Restore the state and return false.
        glDeleteProgram(m_program);
        m_program = 0;
        
        return false;
    }
    
    // Validate the current program. 
    glValidateProgram(m_program);

    GLint status;
    glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status);
    if (!status)
    {
        pLogError("validation of the shader failed");
        glDeleteProgram(m_program);
        m_program = 0;
        return false;
    }

    // The link will implicitly bind the program to the pipeline so
    // we need to remove it from pipeline explicitly.
    glUseProgram(0);

    pGlErrorCheckAbort();

    return true;
}

#if defined P_OPENGL_BINARY_PROGRAM_ENABLED

bool PGlShader::programBinary(pEnum binaryFormat, const void* binary, pInt32 length)
{
    // If this shader program has been already compiled and linked. 
    if (m_program != 0)
    {
        pLogWarning("Can't modify an existing shader program");
        return false;
    }

    // Create the OpenGL program object. 
    program = glCreateProgram();

    // Load the binary program. 
    glProgramBinaryOES(m_program, binaryFormat, binary, length);

    // Validate the current program. 
    glValidateProgram(m_program);

    glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status);
    if (!status)
    {
        pLogError("validation of the shader failed");
        glDeleteProgram(m_program);
        m_program = 0;
        return false;
    }

    // The glProgramBinaryOES will implicitly bind the program to the pipeline.
    m_enabled = true;

    pGlErrorCheckErrorAbort();

    return true;
}

bool PGlShader::getProgramBinary(pEnum* binaryFormat, const void** binary, pInt32* length)
{
    GLint bufSize;
    pUint8* binaryData;
    GLint status;

    if (m_program != 0)
    {
        pLogError("Not a valid shader");
        return false;
    }

    // Get the length of the binary program.
    glGetProgramiv(m_program, PROGRAM_BINARY_LENGTH_OES, &bufSize);

    *length = bufSize;

    // Dump the binary program into the buffer when needed.
    if (binary == P_NULL)
    {
        pUint8* binaryData = pNew(pUint8[bufSize]);

        glGetProgramBinaryOES(m_program, bufSize, binaryFormat, binaryData, length);
        
        *binary = binaryData;
    }
    
    pGlErrorCheckErrorAbort();

    return true;
}

#endif // P_OPENGL_BINARY_PROGRAM_ENABLED

void PGlShader::enable()
{
    // As PRenderEngine will ensure the same shader won't be 
    // enabled twice consecutively.
    //pAssert(!m_enabled);
    if (m_enabled)
    {
        return ;
    }

    // Switch the current shader when necessary. 
    glUseProgram(m_program);

    m_enabled = true;

    pGlErrorCheckError();
}

void PGlShader::disable()
{
    // As PRenderEngine will ensure the same shader won't be 
    // disabled twice consecutively.
    pAssert(m_enabled);

    m_enabled = false;
}

void PGlShader::useDefault()
{
    pAssert(!m_enabled);
    glUseProgram(0);
    pGlErrorCheckError();
}

pInt32 PGlShader::getUniformLocation(const pChar* name)
{
    if (!m_enabled)
    {
        return -1;
    }

    return glGetUniformLocation(m_program, name);
}

void PGlShader::uniform(pInt32 location, pFloat32 x)
{
    if (m_enabled)
    {
        glUniform1f(location, x);
    }
}

void PGlShader::uniform(pInt32 location, pFloat32 x, pFloat32 y)
{
    if (m_enabled)
    {
        glUniform2f(location, x, y);
    }
}

void PGlShader::uniform(pInt32 location, pFloat32 x, pFloat32 y, pFloat32 z)
{
    if (m_enabled)
    {
        glUniform3f(location, x, y, z);
    }
}

void PGlShader::uniform(pInt32 location, pFloat32 x, pFloat32 y, pFloat32 z, pFloat32 w)
{
    if (m_enabled)
    {
        glUniform4f(location, x, y, z, w);
    }
}

void PGlShader::uniform(pInt32 location, pInt32 x)
{
    if (m_enabled)
    {
        glUniform1i(location, x);
    }
}

void PGlShader::uniform(pInt32 location, pInt32 x, pInt32 y)
{
    if (m_enabled)
    {
        glUniform2i(location, x, y);
    }
}

void PGlShader::uniform(pInt32 location, pInt32 x, pInt32 y, pInt32 z)
{
    if (m_enabled)
    {
        glUniform3i(location, x, y, z);
    }
}

void PGlShader::uniform(pInt32 location, pInt32 x, pInt32 y, pInt32 z, pInt32 w)
{
    if (m_enabled)
    {
        glUniform4i(location, x, y, z, w);
    }
}

void PGlShader::uniform(pInt32 location, const pFloat32* value)
{
    if (m_enabled)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, value);
    }
}

bool PGlShader::isPhony() const
{
    return m_program == 0;
}
    
pUint32 PGlShader::getNumberOfUniforms()
{
    pAssert(m_enabled);
    if (!m_enabled)
    {
        pLogError("The shader is not bound to the pipeline yet");
        return 0xffffffff;
    }

    GLint nuniforms;
    glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &nuniforms);

    pGlErrorCheckError();

    return pUint32(nuniforms);
}

PGlShaderUniform PGlShader::getUniformInformation(pUint32 index)
{
    PGlShaderUniform ret;
    ret.m_index = index;

    pAssert(m_enabled);
    if (!m_enabled)
    {
        pLogError("The shader is not bound to the pipeline yet");
        return ret;
    }

    GLenum type = 0;
    GLint size = -1;
    GLsizei length = 0;
    glGetActiveUniform(m_program, index, 1024, &length, &size, &type, ret.m_name);

    pGlErrorCheckError();

    switch (type)
    {
        case GL_FLOAT: ret.m_type = P_GLSHADERUNIFORM_FLOAT; break;
        case GL_FLOAT_VEC2: ret.m_type = P_GLSHADERUNIFORM_FLOAT2; break;
        case GL_FLOAT_VEC3: ret.m_type = P_GLSHADERUNIFORM_FLOAT3; break;
        case GL_FLOAT_VEC4: ret.m_type = P_GLSHADERUNIFORM_FLOAT4; break;
        case GL_INT: ret.m_type = P_GLSHADERUNIFORM_INT; break;
        case GL_INT_VEC2: ret.m_type = P_GLSHADERUNIFORM_INT2; break;
        case GL_INT_VEC3: ret.m_type = P_GLSHADERUNIFORM_INT3; break;
        case GL_INT_VEC4: ret.m_type = P_GLSHADERUNIFORM_INT4; break;
        case GL_BOOL: ret.m_type = P_GLSHADERUNIFORM_BOOL; break;
        case GL_BOOL_VEC2: ret.m_type = P_GLSHADERUNIFORM_BOOL2; break;
        case GL_BOOL_VEC3: ret.m_type = P_GLSHADERUNIFORM_BOOL3; break;
        case GL_BOOL_VEC4: ret.m_type = P_GLSHADERUNIFORM_BOOL4; break;
        case GL_FLOAT_MAT2: ret.m_type = P_GLSHADERUNIFORM_FLOATMATRIX2X2; break;
        case GL_FLOAT_MAT3: ret.m_type = P_GLSHADERUNIFORM_FLOATMATRIX3X3; break;
        case GL_FLOAT_MAT4: ret.m_type = P_GLSHADERUNIFORM_FLOATMATRIX4X4; break;
        case GL_SAMPLER_2D: ret.m_type = P_GLSHADERUNIFORM_SAMPLER2D; break;
        case GL_SAMPLER_CUBE: ret.m_type = P_GLSHADERUNIFORM_SAMPLERCUBE; break;
        default:
            pAssert(!"Unrecognized OpenGL uniform variable type");
            pLogError("Unrecognized OpenGL uniform variable type");
            break;
    }

    // Get the location of this uniform
    ret.m_location = glGetUniformLocation(m_program, ret.m_name);
    pAssert(ret.m_location >= 0);
    if (ret.m_location < 0)
    {
        pLogError("Unable to find the location of %s", ret.m_name);
    }

    return ret;
}
