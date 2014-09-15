// pwin32surface.h
// Create OpenGL context using EGL under win32
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com

#ifndef PT_WIN32_SURFACE_EGL_H
#define PT_WIN32_SURFACE_EGL_H

#include <EGL/egl.h>

#include <PUser/pcontextproperties.h>

class PWin32Window;

class PWin32Surface 
{
public:
    PWin32Surface(HWND hWnd, HDC hDC);
    virtual ~PWin32Surface();

    bool create(PContextProperties* properties);
    void destroy();
    bool setActive(bool enabled);
    void update();

private:
    HDC        m_hDC;               // Device context.
    HWND       m_hWnd;              // The window handle.
    EGLDisplay m_eglDisplay;        // EGL display
    EGLSurface m_eglSurface;        // EGL surface.
    EGLContext m_eglContext;        // EGL context
    EGLConfig  m_eglConfiguration;  // EGL configuration.
};

#endif // !PT_WIN32_SURFACE_EGL_H


