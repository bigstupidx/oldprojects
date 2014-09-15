// pwin32window.cpp
// The native window for win32.
//
// Copyright 2012 by Hongwei Li. All rights reserved.
//
// Hongwei Li lihw81@gmail.com

#include "pwin32window.h"

#include <PPlatform/pwin32surface.h>

#include <PUser/pinput.h>
#include <PUser/pcontext.h>
#include <PUser/pdevice.h>

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>
#include <PSystem/ptime.h>

#include <windows.h>
//#include <system/kzs_winapi.h>
#include <WindowsX.h>


P_EXTERN PInputKey P_APIENTRY pInputNativeGetTranslatedKey(pUint32 keyCode);

// Win32 message dispatcher.
static LRESULT CALLBACK pWin32WindowMainWndProc_internal(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

PWin32Window::PWin32Window(PContext* context)
{
    m_hDC     = P_NULL;
    m_hWnd    = P_NULL;
    m_surface = P_NULL;
    m_context = context;
}

PWin32Window::~PWin32Window()
{
    pAssert(m_hDC == P_NULL);
    pAssert(m_hWnd == P_NULL);
    pAssert(m_surface == P_NULL);
}

bool PWin32Window::create()
{
    // Create the window.
    pUint32 width = m_context->getProperties()->m_screenWidth;
    pUint32 height = m_context->getProperties()->m_screenHeight;
    if (!createWindow(width, height))
    {
        return false;
    }

    // Create the GL surface.
    m_surface = pNew(PWin32Surface(m_hWnd, m_hDC));
    if (!m_surface->create(m_context->getProperties()))
    {
        pDelete(m_surface);
        destroyWindow();
        return false;
    }

    // Store window pointer to window handler. 
    SetWindowLongPtr(m_hWnd, GWL_USERDATA, (LONG)this);

    // Show window and put it on foreground. 
    ShowWindow(m_hWnd, SW_SHOWNORMAL);
    UpdateWindow(m_hWnd);
    SetForegroundWindow(m_hWnd);

    return true;
}

void PWin32Window::destroy()
{
    // Destroy surface
    if (m_surface != P_NULL)
    {
        m_surface->destroy();
        pDelete(m_surface);
    }

    // Destroy window.
    destroyWindow();
}

bool PWin32Window::createWindow(pUint32 windowWidth, pUint32 windowHeight)
{
    // Get the window and height of current display.
    pUint32 displayWidth = GetSystemMetrics(SM_CXSCREEN); 
    pUint32 displayHeight = GetSystemMetrics(SM_CYSCREEN);
    // pLogDebug("Display resolution: %d x %d", displayWidth, displayHeight);

    // If resolution set to automatic, get maximum window size available.
    if (windowWidth == 0)
    {
        windowWidth = displayWidth;
    }

    if (windowHeight == 0)
    {
        windowHeight = displayHeight;
    }
    
    // Register win32 window class. 
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = pWin32WindowMainWndProc_internal;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = NULL;
    wcex.hIcon          = NULL;
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = TEXT("PWin32Window");
    wcex.hIconSm        = NULL;

    RegisterClassEx(&wcex);
    
    // Create a win32 window and set it up. 
    RECT rect;

    pUint32 windowWidthActual;
    pUint32 windowHeightActual;
    pInt32 windowPositionX;
    pInt32 windowPositionY;

    DWORD windowStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_THICKFRAME;
    DWORD extendedWindowStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

    // Set desired window position to the center of the screen. 
    pUint32 desiredWindowWidth = windowWidth;
    pUint32 desiredWindowHeight = windowHeight;
    int desiredWindowPositionX = (GetSystemMetrics(SM_CXSCREEN) - (int)desiredWindowWidth) / 2;
    int desiredWindowPositionY = (GetSystemMetrics(SM_CYSCREEN) - (int)desiredWindowHeight) / 2;
    SetRect(&rect, desiredWindowPositionX, desiredWindowPositionY, 
        desiredWindowPositionX + (int)desiredWindowWidth, desiredWindowPositionY + (int)desiredWindowHeight);

    // Set window style and position. 
    AdjustWindowRectEx(&rect, windowStyle, FALSE, extendedWindowStyle);

    // Calculate width and height. 
    windowPositionX = rect.left;
    windowPositionY = rect.top;
    windowWidthActual = rect.right - rect.left;
    windowHeightActual = rect.bottom - rect.top;

    // Create the window with given parameters.
    const pChar* title = m_context->getName().c_str();
    wchar_t windowTitle[1024];
#if defined P_DEBUG
    size_t convertedChars;
    mbstowcs_s(&convertedChars, windowTitle, 1024, title, strlen(title) + 1);
#else
    size_t windowTitleChars;
    mbstowcs_s(&windowTitleChars, windowTitle, 1024, title, strlen(title) + 1);
#endif

    m_hWnd = CreateWindowEx(extendedWindowStyle, TEXT("PWin32Window"), windowTitle, windowStyle,
                                        windowPositionX, windowPositionY, windowWidthActual, windowHeightActual,
                                        NULL, NULL, NULL, NULL);
    if (m_hWnd == NULL)
    {
        pLogError("fail to create a window with error code 0x%x", GetLastError());
        return false;
    }

    m_style = windowStyle;

    RECT clientRect;
    GetClientRect(m_hWnd, &clientRect);

    windowWidth = clientRect.right - clientRect.left;
    windowHeight = clientRect.bottom - clientRect.top;
    
    SetWindowTextA(m_hWnd, title);

    // We want touch messages. 
    //if(/*PWindowsHaveTouch_internal() &&*/ PWindowsLoadFunctions(&user32Module))
    //{
    //    ATOM atom;
    //    DWORD flags = TABLET_DISABLE_PRESSANDHOLD | TABLET_DISABLE_PENTAPFEEDBACK | TABLET_DISABLE_PENBARRELFEEDBACK | TABLET_DISABLE_FLICKS;
    //    PWinapiRegisterTouchWindow(hWnd, 0);

    //    atom = GlobalAddAtom(MICROSOFT_TABLETPENSERVICE_PROPERTY);
    //    SetProp(hWnd, MICROSOFT_TABLETPENSERVICE_PROPERTY, (HANDLE)flags);
    //    GlobalDeleteAtom(atom);
    //}

    // Store the display device context handle for the window. 
    m_hDC = GetDC(m_hWnd);
    if (m_hDC == P_NULL)
    {
        pLogError("can't get device context of the current window!");
        destroyWindow();
        return false;
    }
    
    m_context->getProperties()->m_screenWidth = windowWidth;
    m_context->getProperties()->m_screenHeight = windowHeight;
    pLogDebug("Drawable resolution: %d x %d", windowWidth, windowHeight);

    return true;
}

void PWin32Window::destroyWindow()
{
    if (m_hDC != P_NULL)
    {
        ReleaseDC(m_hWnd, m_hDC);
        m_hDC = P_NULL;
    }

    DestroyWindow(m_hWnd);
    
    m_hWnd = P_NULL;
}
    
void PWin32Window::run()
{
    while((m_context->getState() == P_CONTEXT_STATE_RUNNING) ||
          (m_context->getState() == P_CONTEXT_STATE_PAUSED))
    {
        MSG message;
        while (PeekMessage(&message, m_hWnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        // Update context state. 
        if (!m_context->update(pTimeGetCurrentTimestamp()))
        {
            m_context->setState(P_CONTEXT_STATE_ERROR);
        }
        else
        {
            m_surface->update();
        }
    }
}

LRESULT CALLBACK pWin32WindowMainWndProc_internal(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT lresult;
    bool handled = false;

    // Retrieve the PWin32Window object from the user data of the win32 window handle.

    switch (message)
    {
        case WM_CLOSE:
        case WM_QUERYENDSESSION:
        {
            PWin32Window* window = reinterpret_cast<PWin32Window*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
            lresult = window->closeEvent()? 0 : 1;
            handled = true;
            break;
        }
        case WM_DESTROY:
        {
            // window has been destroyed
            ::PostQuitMessage(0);
            break;
        }
        case WM_KILLFOCUS:
        {
            PWin32Window* window = reinterpret_cast<PWin32Window*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
            window->focusLostEvent();
            break;
        }
        case WM_SETFOCUS:
        {
            PWin32Window* window = reinterpret_cast<PWin32Window*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
            window->focusGainedEvent();
            break;
        }
        case WM_SIZE:
        {
            PWin32Window* window = reinterpret_cast<PWin32Window*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
                    
            RECT windowSize;
            if (GetClientRect(hWnd, &windowSize))
            {
                window->resizeEvent(windowSize.right, windowSize.bottom);
            }

            break;
        }
        case WM_LBUTTONDOWN:
        {
            PWin32Window* window = reinterpret_cast<PWin32Window*>(GetWindowLongPtr(hWnd, GWL_USERDATA));

            window->mousePressEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),  (wParam & MK_CONTROL) > 0);
            SetCapture(window->getHWND());   // Set capture on, to get drag movement outside the window. 
            break;
        }
        case WM_LBUTTONUP: 
        {
            PWin32Window* window = reinterpret_cast<PWin32Window*>(GetWindowLongPtr(hWnd, GWL_USERDATA));

            window->mouseReleaseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),  (wParam & MK_CONTROL) > 0);
            ReleaseCapture();   // Release mouse capture after click/drag has ended. 
            break;
        }
        case WM_MOUSEMOVE:
        {
            PWin32Window* window = reinterpret_cast<PWin32Window*>(GetWindowLongPtr(hWnd, GWL_USERDATA));

            // If lbutton of mouse is pressed down.
            if ((wParam & 0x0013) > 0 && (wParam & MK_LBUTTON) != 0)
            {
                window->mouseMoveEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (wParam & MK_CONTROL) > 0);
            }

            // for tracking the mouse leaving a window 
            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_LEAVE;
            tme.hwndTrack = window->getHWND();
            tme.dwHoverTime = 0;
            TrackMouseEvent(&tme);
            break;
        }
        case WM_MOUSELEAVE:
        {
            // The mouse has left the window.. don't care because the mouse is still tracked by capturing it earlier. 
            break;
        }
        // Keyboard input. 
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
        {
            pUint32 keyCode = (pUint32)wParam;

            pUint32 state = P_KEY_DEVICE_STATE_DOWN;
            if (GetKeyState(VK_SHIFT) & 0x8000)
            {
                state |= P_KEY_DEVICE_STATE_SHIFT;
            }
            if (GetKeyState(VK_MENU) & 0x8000)
            {
                state |= P_KEY_DEVICE_STATE_ALT;
            }
            if (GetKeyState(VK_CONTROL) & 0x8000)
            {
                state |= P_KEY_DEVICE_STATE_CTRL;
            }

            PInputKey key = pInputNativeGetTranslatedKey(keyCode);
            PWin32Window* window = reinterpret_cast<PWin32Window*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
            window->keyPressEvent(keyCode, key, state);
            break;
        }
        case WM_SYSKEYUP:
        case WM_KEYUP:
        {
            pUint32 keyCode = (pUint32)wParam;
            
            pUint32 state = P_KEY_DEVICE_STATE_UP;
            if (GetKeyState(VK_SHIFT) & 0x8000)
            {
                state |= P_KEY_DEVICE_STATE_SHIFT;
            }
            if (GetKeyState(VK_MENU) & 0x8000)
            {
                state |= P_KEY_DEVICE_STATE_ALT;
            }
            if (GetKeyState(VK_CONTROL) & 0x8000)
            {
                state |= P_KEY_DEVICE_STATE_CTRL;
            }

            PInputKey key = pInputNativeGetTranslatedKey(keyCode);
            PWin32Window* window = reinterpret_cast<PWin32Window*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
            window->keyReleaseEvent(keyCode, key, state);
            
            break;
        }
        default:
            handled = false;
            break;
    }
    
    if (!handled)
    {
        lresult = DefWindowProc(hWnd, message, wParam, lParam);
    }

    return lresult;
}

void PWin32Window::mousePressEvent(pInt32 x, pInt32 y, bool isCtrlHeld)
{
    if (m_context->getState() == P_CONTEXT_STATE_RUNNING ||
        m_context->getState() == P_CONTEXT_STATE_PAUSED)
    {
        PInputEventQueue* inputQueue = m_context->getDevice()->getInputEventQueue();

        inputQueue->addPointerEvent(x,
                                    y,
                                    P_POINTING_DEVICE_STATE_DOWN, 
                                    isCtrlHeld);
    }
}

void PWin32Window::mouseMoveEvent(pInt32 x, pInt32 y, bool isCtrlHeld)
{
    if (m_context->getState() == P_CONTEXT_STATE_RUNNING ||
        m_context->getState() == P_CONTEXT_STATE_PAUSED)
    {
        PInputEventQueue* inputQueue = m_context->getDevice()->getInputEventQueue();

        inputQueue->addPointerEvent(x,
                                    y,
                                    P_POINTING_DEVICE_STATE_DRAG, 
                                    isCtrlHeld);
    }
}

void PWin32Window::mouseReleaseEvent(pInt32 x, pInt32 y, bool isCtrlHeld)
{
    if (m_context->getState() == P_CONTEXT_STATE_RUNNING ||
        m_context->getState() == P_CONTEXT_STATE_PAUSED)
    {
        PInputEventQueue* inputQueue = m_context->getDevice()->getInputEventQueue();

        inputQueue->addPointerEvent(x,
                                    y,
                                    P_POINTING_DEVICE_STATE_UP, 
                                    isCtrlHeld);
    }
}

void PWin32Window::keyPressEvent(pUint32 nativeScanCode, PInputKey key, pUint32 state)
{
    if (m_context->getState() == P_CONTEXT_STATE_RUNNING ||
        m_context->getState() == P_CONTEXT_STATE_PAUSED)
    {
        PInputEventQueue* inputQueue = m_context->getDevice()->getInputEventQueue();
        inputQueue->addKeyEvent(nativeScanCode, key, state);
    }
}

void PWin32Window::keyReleaseEvent(pUint32 nativeScanCode, PInputKey key, pUint32 state)
{
    if (m_context->getState() == P_CONTEXT_STATE_RUNNING ||
        m_context->getState() == P_CONTEXT_STATE_PAUSED)
    {
        PInputEventQueue* inputQueue = m_context->getDevice()->getInputEventQueue();
        inputQueue->addKeyEvent(nativeScanCode, key, state);
    }
}

void PWin32Window::resizeEvent(pInt32 width, pInt32 height)
{
    PDevice* device = m_context->getDevice();
    if (device != P_NULL && 
            (m_context->getState() == P_CONTEXT_STATE_RUNNING ||
             m_context->getState() == P_CONTEXT_STATE_PAUSED))
    {
       device->onResized(width, height);
    }
}

bool PWin32Window::closeEvent()
{
    if (m_context->getState() == P_CONTEXT_STATE_RUNNING ||
        m_context->getState() == P_CONTEXT_STATE_PAUSED)
    {
        if (m_context->onClose())
        {
            m_context->getDevice()->setState(P_DEVICE_STATE_CLOSED);
            return true;
        }
    }

    return false;
}

void PWin32Window::focusLostEvent()
{
    PDevice* device = m_context->getDevice();
    if (device != P_NULL)
    {
        // Release all held keys.
        // For the integer 225, please see P_INPUT_NATIVE_KEY_TRANSLATION_TABLE_SIZE
        // in p_input_win32.cpp
        for (pUint32 i = 0; i < 225; ++i)
        {
            PInputKey key = pInputNativeGetTranslatedKey(i);
            if (key != P_KEY_UNKNOWN && device->getKeyState(key) == P_KEY_DEVICE_STATE_DOWN)
            {
                device->setKeyState((PInputKey)i, P_KEY_DEVICE_STATE_UP);
                device->getInputEventQueue()->addKeyEvent(i, key, P_KEY_DEVICE_STATE_UP);
            }
        }

        device->setState(P_DEVICE_STATE_INACTIVE);
        device->onFocusLost();
    }
}

void PWin32Window::focusGainedEvent()
{
    PDevice* device = m_context->getDevice();
    if (device != P_NULL)
    {
        // FIXME: device == P_NULL when the context has not been initialized.
        device->setState(P_DEVICE_STATE_ACTIVE);
        device->onFocusGained();
    }
}

