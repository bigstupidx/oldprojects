// pdevice.cpp
// Each PContext has one window instance which collect the current display
// screen's status and manges the input events.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com

#include "pdevice.h"

#include <PUser/pcontext.h>
#include <PUser/pcontextproperties.h>

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>


PDevice::PDevice(PContext* context)
    : m_context(context)
{
    m_state = P_DEVICE_STATE_UNINITIALIZED;
    m_inputEventQueue = P_NULL;

    for (pUint32 i = 0; i < P_KEY_COUNT; ++i)
    {
        m_keyStates[i] = P_KEY_DEVICE_STATE_UP;
    }
    
    m_state = P_DEVICE_STATE_ACTIVE;

    m_orientation = P_DEVICE_ORIENTATION_LANDSCAPE;
    m_orientationAngle = P_DEVICE_ORIENTATION_ANGLE_0;

    m_inputEventQueue = pNew(PInputEventQueue(this));
}

PDevice::~PDevice()
{
    pDelete(m_inputEventQueue);
}

void PDevice::update()
{
    // Handle the queued events.
    if (m_context->getState() == P_CONTEXT_STATE_RUNNING)
    {
        pUint32 events = m_inputEventQueue->getNumberOfEvents();
        for (pUint32 i = 0; i < events; ++i)
        {
            PInputEvent* event = m_inputEventQueue->getEventAtIndex(i);
            switch (event->getType())
            {
            case P_INPUT_EVENT_KEY:
                {
                    // Get the native event 
                    //PInputEventKey* keyEvent = event->getKeyEvent();
                    //// Translate it into PEvent and queue the PEvent.
                    //PInputKeyDeviceStateEnum updown = (PInputKeyDeviceStateEnum)(keyEvent->getState() & 
                    //    (P_KEY_DEVICE_STATE_UP | P_KEY_DEVICE_STATE_DOWN));
                    //PEvent* event = pNew(PKeyEvent(
                    //    updown == P_KEY_DEVICE_STATE_DOWN? PEvent::KEY_DOWN : PEvent::KEY_UP,
                    //    keyEvent->getKey(), 
                    //    keyEvent->getNativeScanCode(),
                    //    (keyEvent->getState() & P_KEY_DEVICE_STATE_ALT) > 0,
                    //    (keyEvent->getState() & P_KEY_DEVICE_STATE_CTRL) > 0,
                    //    (keyEvent->getState() & P_KEY_DEVICE_STATE_SHIFT) > 0));
                    //m_context->getEventManager()->appendEvent(event);
                }
                break;
            case P_INPUT_EVENT_TOUCH:
                {
                    //PInputEventTouch* touchEvent = event->getTouchEvent();
                    //// Translate the input type to touch event type.
                    //PEvent::TypeEnum type = (PEvent::TypeEnum)(PEvent::TOUCH_DOWN + 
                    //    (touchEvent->getState() - P_TOUCH_STATE_BEGIN));

                    //PEvent* event = pNew(PTouchEvent(type, *touchEvent));
                    //m_context->getEventManager()->appendEvent(event);

                    //// Do the gesture recognition and insert gesture events into 
                    //// the event queue if any gesture is seen.
                    //m_context->getGestureManager()->recognizeGestures(*touchEvent);
                }
                break;
            }
        }
    }

    m_inputEventQueue->clear();
}

void PDevice::setState(PDeviceStateEnum state)
{
    m_state = state;
}

bool PDevice::onClose()
{
    if (m_context != P_NULL)
    {
        return m_context->onClose();
    }

    return true;
}

void PDevice::onFocusGained()
{
}

void PDevice::onFocusLost()
{
}

void PDevice::onResized(pUint32 width, pUint32 height)
{
    PContextProperties* properties = m_context->getProperties();
    properties->m_screenWidth = width;
    properties->m_screenHeight = height;

    pLogInfo("screen size is changed to %d x %d", width, height);

    m_context->onScreenResized(width, height);
}

void PDevice::onOrientationChanged(PDeviceOrientationEnum orientation)
{
    pLogInfo("orientation is changed to %s", orientation == P_DEVICE_ORIENTATION_LANDSCAPE? 
        "landscape" : "portrait");

    m_orientation = orientation;
}

void PDevice::onOrientationAngleChanged(PDeviceOrientationAngleEnum angle)
{
    pLogInfo("orientation angle is changed to %s", angle == P_DEVICE_ORIENTATION_ANGLE_0? 
        "0" : "180");
}

void PDevice::setKeyState(PInputKey key, PInputKeyDeviceStateEnum state)
{
    pAssertInfo(key < P_KEY_COUNT, "out of key range");
    if (key < P_KEY_COUNT)
    {
        m_keyStates[key] = state;
    }
}

