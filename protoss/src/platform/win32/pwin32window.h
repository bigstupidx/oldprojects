// p_win32_window.h
// The native window under win32
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com

#ifndef PWIN32WINDOW_H
#define PWIN32WINDOW_H

#include <PUser/PInput>

#include <windows.h>


class PWin32Surface;
class PContext;


class P_DLLEXPORT PWin32Window 
{
public:
    PWin32Window(PContext* context);
    virtual ~PWin32Window();

    P_INLINE HWND getHWND() const
    { pAssert(m_hWnd != P_NULL); return m_hWnd; }
    P_INLINE HDC getHDC() const
    { pAssert(m_hDC != P_NULL); return m_hDC; }

    virtual bool create();
    virtual void run();
    virtual void destroy();
    
    P_INLINE PContext* getContext() const
    { return m_context; }

    void mousePressEvent(pInt32 x, pInt32 y, bool isCtrlHeld);
    void mouseMoveEvent(pInt32 x, pInt32 y, bool isCtrlHeld);
    void mouseReleaseEvent(pInt32, pInt32 y, bool isCtrlHeld);
    void keyPressEvent(pUint32 nativeScanCode, PInputKey key, pUint32 state);
    void keyReleaseEvent(pUint32 nativeScanCode, PInputKey key, pUint32 state);
    void resizeEvent(pInt32 width, pInt32 height);
    bool closeEvent();
    void focusLostEvent();
    void focusGainedEvent();

public:
    bool createWindow(pUint32 windowWidth, pUint32 windowHeight);
    void destroyWindow();

private:
    HDC                m_hDC;
    HWND               m_hWnd;   
    DWORD              m_style; 
    PWin32Surface*     m_surface;
    PContext*          m_context;
};

#endif // PWIN32WINDOW_H
