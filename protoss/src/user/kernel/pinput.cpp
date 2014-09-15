// pinput.cpp
// The window events.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com


#include "pinput.h"

#include <PUser/pdevice.h>
#include <PUser/pcontext.h>

//#include <PCore/p_math_functions.h>

#include <PSystem/pmemory.h>
#include <PSystem/pdebug.h>

PInputEventQueue::PInputEventQueue(PDevice* device)
{
    m_device = device;

    m_numberOfEventsCached = P_INPUT_EVENT_QUEUE_INITIAL_SIZE;
    m_events = pNewArray(PInputEvent[m_numberOfEventsCached]);
    pAssert(m_events != P_NULL);

    m_numberOfEvents = 0;
}

PInputEventQueue::~PInputEventQueue()
{
    pDeleteArray(m_events);

#if P_GESTURE_PINCH_SIMULATION_ENABLED == 1
    pDelete(m_pinchSimulator);
#endif

}

pUint32 PInputEventQueue::getNumberOfEvents() const
{
    return m_numberOfEvents;
}

void PInputEventQueue::clear()
{
    m_numberOfEvents = 0;
}

PInputEvent* PInputEventQueue::getEventAtIndex(pUint32 index)
{
    pAssert(index < m_numberOfEvents);
    return &m_events[index];
}

void PInputEventQueue::addKeyEvent(pUint32 nativeScanCode, PInputKey key, pUint32 state)
{
    PInputEvent* event = reserveEvent();
    pAssert(event != P_NULL);

    event->setType(P_INPUT_EVENT_KEY);

    PInputEventKey* keyEvent = event->getKeyEvent();

    keyEvent->setRawScanCode(nativeScanCode);
    keyEvent->setTranslatedScanCode(key);
    keyEvent->setState(state);

    PInputKeyDeviceStateEnum keyState;
    keyState = (PInputKeyDeviceStateEnum)(state & (P_KEY_DEVICE_STATE_DOWN | P_KEY_DEVICE_STATE_UP));
    m_device->setKeyState(keyEvent->getKey(), keyState);

#if P_GESTURE_PINCH_SIMULATION_ENABLED == 1
    if (state & P_KEY_DEVICE_STATE_CTRL)
    {
        if (m_pinchSimulator->getState() == P_POINTING_DEVICE_STATE_DRAG)
        {
            PInputEventTouch* event = addTouchEvent(2, P_TOUCH_STATE_END);
            pAssert(event != P_NULL);

            m_pinchSimulator->createEvent(event);
        }
    }
#endif

}

void PInputEventQueue::addPointerEvent(pInt32 x, pInt32 y, PInputPointingDeviceStateEnum state, bool isCtrlHeld)
{
    pAssert(!isCtrlHeld);

    pUint32 screenWidth = m_device->getContext()->getScreenWidth();
    pUint32 screenHeight = m_device->getContext()->getScreenHeight();

    // Convert Y from window coordinate to viewport coordinate.
    // y = (pInt16)(screenHeight - 1 - y);

    // Change orientation before creating event. 
    if (m_device->getOrientationAngle() == P_DEVICE_ORIENTATION_ANGLE_180)
    {
        x = (pInt16)(screenWidth - 1 - x);
        y = (pInt16)(screenHeight - 1 - y);
    }

    // Translate pointer events to touch events
    PInputCursorStateEnum cursorState = P_CURSOR_STATE_STATIONARY;
    PInputTouchStateEnum touchState = P_TOUCH_STATE_END;

    switch(state)
    {
        case P_POINTING_DEVICE_STATE_DOWN:
            cursorState = P_CURSOR_STATE_DOWN;
            touchState = P_TOUCH_STATE_BEGIN;
            break;
        case P_POINTING_DEVICE_STATE_DRAG:
            cursorState = P_CURSOR_STATE_MOVE;
            touchState = P_TOUCH_STATE_CONTINUE;
            break;
        case P_POINTING_DEVICE_STATE_UP:
            cursorState = P_CURSOR_STATE_UP;
            break;
        case P_POINTING_DEVICE_STATE_MOVE:
        default:
            break;
    }

    if (cursorState != P_CURSOR_STATE_STATIONARY)
    {
#if P_GESTURE_PINCH_SIMULATION_ENABLED == 1

        if (isCtrlHeld)
        {
            PInputEventTouch* event = addTouchEvent(2, touchState);
            pAssert(event != P_NULL);
            m_pinchSimulator->createEvent(x, y, state, event);
        }
        else
        {
#endif
        PInputEventTouch* event = addTouchEvent(1, touchState);
        pAssert(event != P_NULL);

        if (event != P_NULL)
        {
            PInputEventTouch::TouchCursor* c = event->getCursor(0);

            c->m_id = 0;
            c->m_x = x;
            c->m_y = y;
            c->m_state = cursorState;
            c->m_pressure = 1.0f;
            c->m_radius = 1.0f;
        }


#if P_GESTURE_PINCH_SIMULATION_ENABLED == 1
        }
#endif
    }
}

PInputEventTouch* PInputEventQueue::addTouchEvent(pUint32 numCursors, PInputTouchStateEnum state)
{
    PInputEvent* event = (PInputEvent*)reserveEvent();
    pAssert(event != P_NULL);

    event->setType(P_INPUT_EVENT_TOUCH);
    
    PInputEventTouch* touchEvent = event->getTouchEvent();

    touchEvent->setCursorCount(numCursors);
    touchEvent->setState(state);

    return touchEvent;
}
    
void PInputEventQueue::setTouchCursor(PInputEventTouch* touchEvent, pInt32 index, pInt32 id,
            pFloat32 x, pFloat32 y, pFloat32 pressure, pFloat32 area, pInt32 state)
{
    pAssert(touchEvent != P_NULL);

    PInputEventTouch::TouchCursor* cursor = touchEvent->getCursor(index);
    if (cursor == P_NULL)
    {
        pLogError("too many cursor data for this touch event");
        return ;
    }

    cursor->m_id = id;
    if (m_device->getOrientationAngle() == P_DEVICE_ORIENTATION_ANGLE_180)
    {
        cursor->m_x = pInt16(180.0f - x);
        cursor->m_y = pInt16(180.0f - y);
    }
    else
    {
        cursor->m_x = pInt16(x);
        cursor->m_y = pInt16(y);
    }
    cursor->m_pressure = pressure;
    cursor->m_radius = area;
    cursor->m_state = (PInputCursorStateEnum)(state);
}

PInputEvent* PInputEventQueue::reserveEvent()
{
    PInputEvent* ret;

    if (m_numberOfEvents >= m_numberOfEventsCached)
    {
        m_numberOfEventsCached += P_INPUT_EVENT_QUEUE_INITIAL_SIZE / 2;

        pLogDebug("event queue resized to %d", m_numberOfEventsCached);
      
        PInputEvent* newEvents = pNewArray(PInputEvent[m_numberOfEventsCached]);
        for (pUint32 i = 0; i < m_numberOfEvents; ++i)
        {
            newEvents[i] = m_events[i];
        }

        pDeleteArray(m_events);
        m_events = newEvents;
    }

    ret = &m_events[m_numberOfEvents];
    m_numberOfEvents++;

    return ret;
}
