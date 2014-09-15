// pwin32surface.cpp
// The OpenGL surface using EGL
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com

#include "pwin32surface.h"

#include <PUser/pcontextproperties.h>

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>

#include <EGL/egl.h>

// Initialize the EGL display
// \param display specifies the display to connect to. EGL_DEFAULT_DISPLAY
// indicates the default display.
static EGLDisplay pEglDisplayInitialize_internal(EGLNativeDisplayType displayType);
// Initialize the EGL surface.
// \param eglDisplay the EGL display
// \param eglWindow the native window type.
// \param eglConfiguration the configuration for this surface.
// \param out_eglSurface the returned EGL surface.
// \param out_eglContext the returned EGL context.
// \return true if successful and false otherwise.
static bool pEglSurfaceInitialize_internal(EGLDisplay eglDisplay, HWND eglWindow, 
        EGLConfig eglConfiguration, EGLSurface& out_eglSurface, EGLContext& out_eglContext);

//  Make the the EGL surface configuration with given one.
//  \param eglDisplay the EGL display.
//  \param eglConfigurationAttributeArray the input EGL surface configuration.
//  \param out_eglConfiguration the returned surface configuration.
static EGLConfig pEglConfigure_internal(EGLDisplay eglDisplay, EGLint* eglConfigurationAttributeArray);

// Check the EGL error
// \param file the file name where this function is used.
// \param line the line number where this function is at 
static bool pEglErrorCheck_internal(const pChar* file, pUint32 line);
#define pEglErrorCheckError() pEglErrorCheck_internal(__FILE__, __LINE__) 


PWin32Surface::PWin32Surface(HWND hWnd, HDC hDC)
{
    pAssert(hWnd != NULL);
    m_hWnd = hWnd;
    pAssert(hDC != NULL);
    m_hDC = hDC;

    m_eglDisplay       = P_NULL;
    m_eglSurface       = P_NULL;
    m_eglContext       = P_NULL;
    m_eglConfiguration = P_NULL;
}

PWin32Surface::~PWin32Surface()
{
    pAssert(m_eglDisplay == P_NULL);
    pAssert(m_eglSurface == P_NULL);
    pAssert(m_eglContext == P_NULL);
}

bool PWin32Surface::create(PContextProperties* properties)
{
    // Create private data object.
    m_eglDisplay = pEglDisplayInitialize_internal((EGLNativeDisplayType)m_hDC);
    if (m_eglDisplay == EGL_NO_DISPLAY)
    {
        return false;
    }

    // Set EGL attributes.
    EGLint eglConfigurationAttributeArray[128];
    pInt32 i = 0;
    eglConfigurationAttributeArray[i++] = EGL_RED_SIZE;
    eglConfigurationAttributeArray[i++] = properties->m_rgba[0];
    eglConfigurationAttributeArray[i++] = EGL_GREEN_SIZE;
    eglConfigurationAttributeArray[i++] = properties->m_rgba[1];
    eglConfigurationAttributeArray[i++] = EGL_BLUE_SIZE;
    eglConfigurationAttributeArray[i++] = properties->m_rgba[2];
    eglConfigurationAttributeArray[i++] = EGL_ALPHA_SIZE;
    eglConfigurationAttributeArray[i++] = properties->m_rgba[3];
    eglConfigurationAttributeArray[i++] = EGL_SURFACE_TYPE;
    eglConfigurationAttributeArray[i++] = EGL_WINDOW_BIT;
    eglConfigurationAttributeArray[i++] = EGL_DEPTH_SIZE;
    eglConfigurationAttributeArray[i++] = properties->m_depth;
    eglConfigurationAttributeArray[i++] = EGL_STENCIL_SIZE;
    eglConfigurationAttributeArray[i++] = properties->m_stencil;
    
    if (properties->m_multisamples > 0)
    {
        eglConfigurationAttributeArray[i++] = EGL_SAMPLES;
        eglConfigurationAttributeArray[i++] = properties->m_multisamples;
    }

#if defined PT_OPENGL_ES20 
    eglConfigurationAttributeArray[i++] = EGL_RENDERABLE_TYPE;
    eglConfigurationAttributeArray[i++] = EGL_OPENGL_ES2_BIT;
#endif
    eglConfigurationAttributeArray[i++] = EGL_NONE;

    m_eglConfiguration = pEglConfigure_internal(m_eglDisplay, eglConfigurationAttributeArray);
    if (m_eglConfiguration == P_NULL)
    {
        eglTerminate(m_eglDisplay);
        m_eglDisplay = P_NULL;
        return false;
    }

    // Find the actual properties 
    EGLBoolean result;
    EGLint redBits, greenBits, blueBits, alphaBits, depthBits, stencilBits, samples;

    result = eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_RED_SIZE, &redBits);
    result &= eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_GREEN_SIZE, &greenBits);
    result &= eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_BLUE_SIZE, &blueBits);
    result &= eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_ALPHA_SIZE, &alphaBits);
    result &= eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_DEPTH_SIZE, &depthBits);
    result &= eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_STENCIL_SIZE, &stencilBits);
    result &= eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_SAMPLES, &samples);

    if (result == EGL_TRUE)
    {
        pLogDebug("EGL surface created, RGBA=(%d,%d,%d,%d), depth=%d, stencil=%d, multisamples=%d",
                redBits, greenBits, blueBits, alphaBits, depthBits, stencilBits, samples);

        // Save these actual surface parameters.
        properties->m_rgba[0] = redBits;
        properties->m_rgba[1] = greenBits;
        properties->m_rgba[2] = blueBits;
        properties->m_rgba[3] = alphaBits;
        properties->m_depth   = depthBits;
        properties->m_stencil = stencilBits;
        properties->m_multisamples = samples;
    }
    else
    {
        pLogError("fail to get EGL surface parameters");
        eglTerminate(m_eglDisplay);
        m_eglDisplay = P_NULL;
        return false;
    }

    if (!pEglSurfaceInitialize_internal(m_eglDisplay, m_hWnd, 
            m_eglConfiguration, m_eglSurface, m_eglContext))
    {
        eglTerminate(m_eglDisplay);
        m_eglDisplay = P_NULL;
        return false;
    }

    // Set this surface active.
    if (!setActive(true))
    {
        destroy();
        return false;
    }
    
    return true;
}

void PWin32Surface::destroy()
{
    pAssert(m_eglContext != P_NULL);
    pAssert(m_eglDisplay != P_NULL);
    pAssert(m_eglSurface != P_NULL);

    EGLBoolean result;

    result = eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (result != EGL_TRUE || !pEglErrorCheckError()) 
    {
        pLogWarning("failed to remove current EGL surface and context");
    }

    result = eglDestroySurface(m_eglDisplay, m_eglSurface);
    if (result != EGL_TRUE || !pEglErrorCheckError()) 
    {
        pLogWarning("failed to destroy EGL surface");
    }
    m_eglSurface = P_NULL;

    result = eglDestroyContext(m_eglDisplay, m_eglContext);
    if (result != EGL_TRUE || !pEglErrorCheckError()) 
    {
        pLogWarning("failed to destroy EGL context");
    }
    m_eglContext = P_NULL;

    result = eglTerminate(m_eglDisplay);
    if (result != EGL_TRUE || !pEglErrorCheckError()) 
    {
        pLogWarning("failed to terminate EGL display");
    }
    m_eglDisplay = P_NULL;
}

bool PWin32Surface::setActive(bool active)
{
    pAssert(m_eglSurface != P_NULL);
    pAssert(m_eglContext != P_NULL);
    pAssert(m_eglDisplay != P_NULL);

    EGLBoolean result;

    if (active)
    {
        result = eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
        if (result != EGL_TRUE || !pEglErrorCheckError()) 
        {
            pLogWarning("failed to switch to new EGL context and surface");
            return false;
        }
    }
    else
    {
        result = eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (result != EGL_TRUE || !pEglErrorCheckError()) 
        {
            pLogWarning("failed to switch to NULL EGL context and surface");
            return false;
        }
    }

    return true;
}

void PWin32Surface::update()
{
    pAssert(m_eglSurface != P_NULL);
    pAssert(m_eglContext != P_NULL);
    pAssert(m_eglDisplay != P_NULL);

    EGLBoolean result;
    result = eglSwapBuffers(m_eglDisplay, m_eglSurface);
    if (result != EGL_TRUE) 
    {
        pEglErrorCheckError(); 
        pLogWarning("failed to flush EGL buffer to screen");
    }
}

/*
void PWin32Surface::readPixels(void* pixels)
{
    pAssert(m_eglSurface != P_NULL);
    pAssert(m_eglContext != P_NULL);
    pAssert(m_eglDisplay != P_NULL);

    EGLint width, height;
    EGLint redBits, greenBits, blueBits, alphaBits;
    EGLBoolean result;

    // Query surface and configuration attributes.
    result = eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_WIDTH, &width);
    result &= eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_HEIGHT, &height);
    result &= eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_RED_SIZE, &redBits);
    result &= eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_GREEN_SIZE, &greenBits);
    result &= eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_BLUE_SIZE, &blueBits);
    result &= eglGetConfigAttrib(m_eglDisplay, m_eglConfiguration,  EGL_ALPHA_SIZE, &alphaBits);

    if (result != EGL_TRUE || !pEglErrorCheckError())
    {
        pLogWarning("Unable to query the surface");
        return ;
    }

    // Dump the data from surface to bitmap.
    EGLint nbits = redBits + greenBits + blueBits + alphaBits;
    pUint8* bits = new pUint8 [nbits >> 3];
    pAssert(bits);
    if (bits == P_NULL)
    {
        pLogWarning("new pUint8 failed");
        return;
    }
    HBITMAP hbitmap = CreateBitmap(width, height, 1, nbits, bits);
    if (hbitmap == P_NULL)
    {
        pLogWarning("error in CreateBitmap");
        pDelete(bits);
        return;
    }

    result = eglCopyBuffers(m_eglDisplay, m_eglSurface, hbitmap);
    if (result != EGL_TRUE) 
    {
        pEglErrorCheckError(); 

        DeleteObject(hbitmap);
        pDeleteArray(bits);
        
        pLogWarning("failed to copy EGL surface content to memory");

        return ;
    }

    // Copy the pixels from hbitmap to pixels.
    BITMAP bmp;
    ::GetObject(hbitmap, sizeof(BITMAP), &bmp);
    pSystem_memcpy(pixels, bmp.bmBits, width * height * (nbits >> 3));    

    pDeleteArray(bits);
    DeleteObject(hbitmap);
}
*/

EGLDisplay pEglDisplayInitialize_internal(EGLNativeDisplayType displayType)
{
    EGLDisplay eglDisplay;

    eglDisplay = eglGetDisplay(displayType);
    if (!pEglErrorCheckError() || eglDisplay == EGL_NO_DISPLAY)
    {
        pLogError("Unable to init EGL display");
        return P_NULL;
    }

    // Got a valid display, now init EGL. 
    EGLint eglVersionMajor, eglVersionMinor;
    EGLBoolean initializeResult = eglInitialize(eglDisplay, &eglVersionMajor, &eglVersionMinor);
    if (!pEglErrorCheckError() || initializeResult != EGL_TRUE)
    {
        pLogError("EGL initialization failed.");
        return P_NULL;
    }
    else
    {
        pLogDebug("EGL version: %d.%d", eglVersionMajor, eglVersionMinor);
    }

    return eglDisplay;
}

bool pEglErrorCheck_internal(const pChar* file, pUint32 line)
{
    EGLint error;
    do 
    {
        error = eglGetError();
        if (error != EGL_SUCCESS)
        {
            pChar* errorString;
            switch (error)
            {
                case EGL_NOT_INITIALIZED: errorString = "EGL_NOT_INITIALIZED"; break;
                case EGL_BAD_ACCESS: errorString = "EGL_BAD_ACCESS"; break;
                case EGL_BAD_ALLOC: errorString = "EGL_BAD_ALLOC"; break;
                case EGL_BAD_ATTRIBUTE: errorString = "EGL_BAD_ATTRIBUTE"; break;
                case EGL_BAD_CONFIG: errorString = "EGL_BAD_CONFIG"; break;
                case EGL_BAD_CONTEXT: errorString = "EGL_BAD_CONTEXT"; break;
                case EGL_BAD_CURRENT_SURFACE: errorString = "EGL_BAD_CURRENT_SURFACE"; break;
                case EGL_BAD_DISPLAY: errorString = "EGL_BAD_DISPLAY"; break;
                case EGL_BAD_MATCH: errorString = "EGL_BAD_MATCH"; break;
                case EGL_BAD_NATIVE_PIXMAP: errorString = "EGL_BAD_NATIVE_PIXMAP"; break;
                case EGL_BAD_NATIVE_WINDOW: errorString = "EGL_BAD_NATIVE_WINDOW"; break;
                case EGL_BAD_PARAMETER: errorString = "EGL_BAD_PARAMETER"; break;
                case EGL_BAD_SURFACE: errorString = "EGL_BAD_SURFACE"; break;
                default: errorString = "Unknown EGL error"; break;
            }

            pLog(P_LOG_ERROR, file, line, "%s", errorString); 
            return false;
        }
    } 
    while (error != EGL_SUCCESS);

    return true;
}

EGLConfig pEglConfigure_internal(EGLDisplay eglDisplay, EGLint* eglConfigurationAttributeArray)
{
    EGLBoolean result = EGL_TRUE;

    EGLConfig eglConfig = P_NULL;

    pInt32 eglConfigurationTotalCount;
    result = eglGetConfigs(eglDisplay, NULL, 0, &eglConfigurationTotalCount);
    if (!pEglErrorCheckError() || result != EGL_TRUE || eglConfigurationTotalCount < 1)
    {
        pLogError("Unable to get an EGL configuraiton");
        return P_NULL;
    }

    EGLConfig* configurationArray = pNewArray(EGLConfig[eglConfigurationTotalCount]);
    pAssert(configurationArray != P_NULL);
    if (configurationArray == P_NULL)
    {
        pLogError("new EGLConfig failed");
        return P_NULL;
    }

    // Find the closest matching configuration.
    pInt32 eglConfigurationCount;            
    result = eglChooseConfig(eglDisplay, eglConfigurationAttributeArray, 
            configurationArray, eglConfigurationTotalCount, &eglConfigurationCount);
    if (result != EGL_TRUE || !pEglErrorCheckError())
    {
        pLogError("Error in finding the closest matching EGL configuration");
        pDeleteArray(configurationArray);
        return P_NULL;
    }

    // If no configs found, check if AA was requested and try again without it. 
    if (eglConfigurationCount == 0)
    {
        pLogWarning("Could not find an EGL configuration with given settings. Trying again without anti-aliasing.");

        for (pUint32 i = 0; eglConfigurationAttributeArray[i] != EGL_NONE; i++)
        {
            if (eglConfigurationAttributeArray[i] == EGL_SAMPLE_BUFFERS)
            {
                ++i;
                eglConfigurationAttributeArray[i] = EGL_DONT_CARE;
            }
            if(eglConfigurationAttributeArray[i] == EGL_SAMPLES)
            {
                ++i;
                eglConfigurationAttributeArray[i] = EGL_DONT_CARE;
            }
        }

        // Try again without AA.
        result = eglChooseConfig(eglDisplay, eglConfigurationAttributeArray, 
            configurationArray, eglConfigurationTotalCount, &eglConfigurationCount);
        if (result != EGL_TRUE || !pEglErrorCheckError())
        {
            pLogError("Error in finding the closest matching EGL configuration without AA");
            pDelete(configurationArray);
            return P_NULL;
        }
    }

    // Still none found: just take the ones that are available and see if one
    // with correct color depth can be found 
    if (eglConfigurationCount == 0)
    {
        pLogWarning("Could not find an EGL configuration that matches the requirements. Performance may be reduced.");
        pInt32 eglConfigurationTotalCountConfirmed;
        result = eglGetConfigs(eglDisplay, configurationArray,
                eglConfigurationTotalCount,
                &eglConfigurationTotalCountConfirmed);
        if (result != EGL_TRUE || !pEglErrorCheckError())
        {
            pLogError("Error in get all EGL configurations");
            pDelete(configurationArray);
            return P_NULL;
        }
        if (eglConfigurationTotalCountConfirmed != eglConfigurationTotalCount)
        {
            pLogError("Wrong EGL total configuration number");
            pDelete(configurationArray);
            return P_NULL;
        }

        eglConfigurationCount = eglConfigurationTotalCount;
    }

    // Find out which color depths were requested 
    EGLint redAsked = 5;          // bit depths that were requested in eglConfigurationAttributeArray 
    EGLint greenAsked = 6;
    EGLint blueAsked = 5;
    for (pInt32 i = 0; eglConfigurationAttributeArray[i] != EGL_NONE; i++)
    {
        switch (eglConfigurationAttributeArray[i]) 
        {
            case EGL_RED_SIZE:
            {
                i++;
                redAsked = eglConfigurationAttributeArray[i];
                break;
            }
            case EGL_GREEN_SIZE:
            {
                i++;
                greenAsked = eglConfigurationAttributeArray[i];
                break;
            }
            case EGL_BLUE_SIZE:
            {
                i++;
                blueAsked = eglConfigurationAttributeArray[i];
                break;
            }
            default:
            {
                break;
            }
        }
    }

    // Search for a configuration that has the correct color format 
    for (pInt32 i = 0; i < eglConfigurationCount; i++)
    {
        EGLint redBits = 0;      
        EGLint greenBits = 0;
        EGLint blueBits = 0;            

        result = eglGetConfigAttrib(eglDisplay, configurationArray[i], EGL_RED_SIZE, &redBits);
        result &= eglGetConfigAttrib(eglDisplay, configurationArray[i], EGL_GREEN_SIZE, &greenBits);
        result &= eglGetConfigAttrib(eglDisplay, configurationArray[i], EGL_BLUE_SIZE, &blueBits);

        if (!pEglErrorCheckError())
        {
            pLogError("Error in getting EGL config attribute");
            pDelete(configurationArray);
            return P_NULL;
        }

        if (result == EGL_TRUE && redBits == redAsked && blueBits == blueAsked && greenBits == greenAsked) 
        {
            eglConfig = configurationArray[i];
            break;
        }
    }
    
    // None found, pick the first one 
    if (eglConfig == 0) 
    {
        eglConfig = configurationArray[0];
    }

    pDelete(configurationArray);

    return eglConfig;
}

bool pEglSurfaceInitialize_internal(EGLDisplay eglDisplay, HWND eglWindow, 
        EGLConfig eglConfiguration, EGLSurface& out_eglSurface, EGLContext& out_eglContext)
{
    EGLSurface eglSurface = EGL_NO_SURFACE;
    EGLContext eglContext = EGL_NO_CONTEXT;

    // Create EGL surface with the configuration.
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfiguration, eglWindow, P_NULL);
    if (!pEglErrorCheckError())
    {
        pLogError("Unable to initialize EGL surface");
        return false;
    }

    // Create EGL context.
#if defined P_OPENGL_ES20
    EGLint contextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    eglContext = eglCreateContext(eglDisplay, eglConfiguration, eglGetCurrentContext(), contextAttributes);
#else 
    eglContext = eglCreateContext(eglDisplay, eglConfiguration, eglGetCurrentContext(), P_NULL);
#endif
    if (!pEglErrorCheckError())
    {
        eglDestroySurface(eglDisplay, eglSurface);
        eglSurface = P_NULL;
        pLogError("Unable to initialize EGL context");
        return false;
    }

    // Activate EGL surface. 
    EGLBoolean result = eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
    if (result != EGL_TRUE || !pEglErrorCheckError())
    {
        pLogError("Unable to activate EGL context");
        
        eglDestroySurface(eglDisplay, eglSurface);
        eglSurface = P_NULL;
        eglDestroyContext(eglDisplay, eglContext);
        eglContext = P_NULL;

        return false;
    }

    out_eglSurface = eglSurface;
    out_eglContext = eglContext;
    
    return true;
}

