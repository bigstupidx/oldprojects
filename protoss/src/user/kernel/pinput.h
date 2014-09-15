// pinput.h
// The window events.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com


#ifndef PINPUT_H
#define PINPUT_H

#include <PGlobal/pglobal.h>
#include <PSystem/pdebug.h>

class PDevice;
class PGesturePinchSimulator;

enum PInputEventTypeEnum 
{
    P_INPUT_EVENT_KEY,
    P_INPUT_EVENT_TOUCH,
    P_INPUT_EVENT_UNKNOWN,
};

enum PInputPointingDeviceStateEnum
{
    P_POINTING_DEVICE_STATE_DOWN, ///< Pressed. 
    P_POINTING_DEVICE_STATE_MOVE, ///< Pointer moved. Not all platforms support this, for example many touch screens. 
    P_POINTING_DEVICE_STATE_DRAG, ///< Pointer dragged. 
    P_POINTING_DEVICE_STATE_UP    ///< Released. 
};

enum PInputCursorStateEnum
{
    P_CURSOR_STATE_DOWN,       //< finger down. 
    P_CURSOR_STATE_STATIONARY, //< finger still. 
    P_CURSOR_STATE_MOVE,       //< finger move. 
    P_CURSOR_STATE_UP          //< finger up. 
};

enum PInputTouchStateEnum
{
    P_TOUCH_STATE_BEGIN,    ///< First finger down. 
    P_TOUCH_STATE_CONTINUE, ///< Gesture or touch event in progress. 
    P_TOUCH_STATE_END       ///< Last finger up. 
};

enum PInputKeyDeviceStateEnum
{
    P_KEY_DEVICE_STATE_DOWN     = 0x01,   ///< Key down
    P_KEY_DEVICE_STATE_UP       = 0x02,   ///< Key up
    P_KEY_DEVICE_STATE_REPEAT   = 0x04,   ///< The key is pressed
    P_KEY_DEVICE_STATE_CTRL     = 0x08,   ///< The ctrl is pressed down
    P_KEY_DEVICE_STATE_ALT      = 0x10,   ///< Ditto
    P_KEY_DEVICE_STATE_SHIFT    = 0x20,   ///< Ditto
};

/// Platform independent key scancode 
enum PInputKey
{
    // Unknown keys are used for unmapped keys. 
    P_KEY_UNKNOWN = 0,

    // Keys used for numeric input 
    P_KEY_0,
    P_KEY_1,
    P_KEY_2,
    P_KEY_3,
    P_KEY_4,
    P_KEY_5,
    P_KEY_6,
    P_KEY_7,
    P_KEY_8,
    P_KEY_9,
    P_KEY_COMMA,
    P_KEY_PERIOD,
    P_KEY_SEMICOLON,
    P_KEY_DECIMAL_SEPARATOR,      ///< allows for locale specific separator key mapping */
    P_KEY_THOUSANDS_SEPARATOR,    ///< allows for locale specific separator key mapping */

    // Keys used for text input 
    P_KEY_A,
    P_KEY_B,
    P_KEY_C,
    P_KEY_D,
    P_KEY_E,
    P_KEY_F,
    P_KEY_G,
    P_KEY_H,
    P_KEY_I,
    P_KEY_J,
    P_KEY_K,
    P_KEY_L,
    P_KEY_M,
    P_KEY_N,
    P_KEY_O,
    P_KEY_P,
    P_KEY_Q,
    P_KEY_R,
    P_KEY_S,
    P_KEY_T,
    P_KEY_U,
    P_KEY_V,
    P_KEY_W,
    P_KEY_X,
    P_KEY_Y,
    P_KEY_Z,

    P_KEY_SPACE,
    P_KEY_BACKSPACE,
    P_KEY_ENTER,
    P_KEY_TAB,
    P_KEY_ESC,
    
    P_KEY_CAPS_LOCK,
    P_KEY_NUM_LOCK,
    P_KEY_PRINT_SCREEN,
    P_KEY_SCROLL_LOCK,
    P_KEY_BREAK,

    P_KEY_INSERT,
    P_KEY_DELETE,
    P_KEY_HOME,
    P_KEY_END,
    P_KEY_PAGE_UP,
    P_KEY_PAGE_DOWN,

    P_KEY_EQUAL,
    P_KEY_MINUS,
    P_KEY_MULTIPLY,
    P_KEY_DIVIDE,
    P_KEY_BACKSLASH,
    P_KEY_LEFT_BRACKET,
    P_KEY_RIGHT_BRACKET,
    P_KEY_QUOTELEFT,
    P_KEY_QUOTE,

    P_KEY_ARROW_UP,
    P_KEY_ARROW_DOWN,
    P_KEY_ARROW_LEFT,
    P_KEY_ARROW_RIGHT,
    
    P_KEY_NUM_0,
    P_KEY_NUM_1,
    P_KEY_NUM_2,
    P_KEY_NUM_3,
    P_KEY_NUM_4,
    P_KEY_NUM_5,
    P_KEY_NUM_6,
    P_KEY_NUM_7,
    P_KEY_NUM_8,
    P_KEY_NUM_9,
    P_KEY_NUM_DIVIDE,
    P_KEY_NUM_MULTIPLY,
    P_KEY_NUM_PLUS,
    P_KEY_NUM_MINUS,
    P_KEY_NUM_COMMA,
    P_KEY_NUM_ENTER,
    
    P_KEY_F1,
    P_KEY_F2,
    P_KEY_F3,
    P_KEY_F4,
    P_KEY_F5,
    P_KEY_F6,
    P_KEY_F7,
    P_KEY_F8,
    P_KEY_F9,
    P_KEY_F10,
    P_KEY_F11,
    P_KEY_F12,

    P_KEY_VOLUME_UP,
    P_KEY_VOLUME_DOWN,

    P_KEY_SOFTKEY1,  
    P_KEY_SOFTKEY2,
    P_KEY_SOFTKEY3,
    P_KEY_SOFTKEY4,
    
    // Generic names for modifier keys such as shift, ctrl, alt, Fn, command, super, etc. 
    P_KEY_MODIFIER1, 
    P_KEY_MODIFIER2,
    P_KEY_MODIFIER3,
    
    // Specific modifier key names on a common IBM keyboard 
    // Kiwi doesn't distinguish left and right alt, ctrl and shift.
    P_KEY_ALT,
    P_KEY_CONTROL,
    P_KEY_SHIFT,
    P_KEY_META, // On Mac OS X, this corresponds to the Commands keys. On Windows keyboards, this key is mapped to the Windows key.
    P_KEY_MENU, // The context key on Windows keyboards.

    P_KEY_PAUSE,
    P_KEY_PRINT,
    
    P_KEY_COUNT
};


// Structure for multi-touch events (touch screen) from system.
class PInputEventTouch
{
public:
    // One finger in multi-touch event.
    struct TouchCursor
    {
        /// The id of this cursor.
        pUint32 m_id;
        /// X coordinate for pointer. 
        pInt16 m_x;                    
        /// Y coordinate for pointer. It is in the viewport coordinate. The origin is at the 
        /// left bottom corner and the Y is up.
        pInt16 m_y;                    
        /// Pressure information for pointer, if supported by platform. Otherwise value unspecified.
        pFloat32 m_pressure;      
        ///< Size of the area touched if supported by platform. Otherwise value unspecified. 
        pFloat32 m_radius;             
        ///< State of this particular cursor. 
        PInputCursorStateEnum m_state; 
    };

    TouchCursor* getCursor(pUint32 index)
    {
        pAssert(index < m_cursorCount);
        return &m_cursorData[index];
    }
    
    const TouchCursor* getCursor(pUint32 index) const
    {
        pAssert(index < m_cursorCount);
        if (index < m_cursorCount)
        {
            return &m_cursorData[index];
        }
        return P_NULL;
    }

    void setCursorCount(pUint32 count)
    {
        m_cursorCount = count;
    }

    pUint32 getCursorCount() const
    {
        return m_cursorCount;
    }

    void setState(PInputTouchStateEnum state)
    {
        m_state = state;
    }

    PInputTouchStateEnum getState() const
    {
        return m_state;
    }
    
private:
    pUint32 m_cursorCount;  // Number of cursors for this touch event. 
    TouchCursor m_cursorData[P_INPUT_MAXIMUM_TOUCH]; // Data for all the cursors. 
    PInputTouchStateEnum m_state; // The state of this touch input event.
};

// An key event from keyboard, keypad, buttons, digital joysticks ...
class PInputEventKey
{
public:
    // Queries.
    PInputKey getKey() const
    {
        return m_key;
    }
    pUint32 getNativeScanCode() const
    {
        return m_nativeScanCode;
    }
    pUint32 getState() const
    {
        return m_state;
    }

    void setTranslatedScanCode(PInputKey key) 
    {
        m_key = key;
    }
    void setRawScanCode(pUint32 scancode)
    {
        m_nativeScanCode = scancode;
    }
    void setState(pUint32 state) 
    {
        m_state = state;
    }
    
private:
    PInputKey m_key;           ///< Platform independent button key value. 
    pUint32 m_nativeScanCode;  ///< Raw value from the OS.
    pUint32 m_state;           ///< Button state; a union of PInputKeyDeviceStateEnum.
};

class PInputEvent
{
public:
    PInputEvent()
    {
        m_type = P_INPUT_EVENT_UNKNOWN;
    }

    PInputEventTypeEnum getType() const
    {
        return m_type;
    }

    void setType(PInputEventTypeEnum type)
    {
        m_type = type;
    }

    PInputEventKey* getKeyEvent() 
    {
        return &m_event.m_key;
    }
    
    PInputEventTouch* getTouchEvent() 
    {
        return &m_event.m_touch;
    }
        
private:
    PInputEventTypeEnum m_type;

    union 
    {
        PInputEventKey m_key;
        PInputEventTouch m_touch;
    } m_event;
};


class P_DLLEXPORT PInputEventQueue
{
public:
    // Constructor.
    // \param window the parent window.
    PInputEventQueue(PDevice* window);

    // Destructor.
    ~PInputEventQueue();
        
    // Add touch event to the queue.
    // \param the number of touch points.
    // \param the state of this touch event
    // \return the touch event just added.
    PInputEventTouch* addTouchEvent(pUint32 touchPoints, PInputTouchStateEnum state);

    // Set the cursor data of one touch event.
    void setTouchCursor(PInputEventTouch* touchEvent, pInt32 index, pInt32 id,
            pFloat32 x, pFloat32 y, pFloat32 pressure, pFloat32 area, pInt32 state);
    
    // Add left button of the mouse event to the queue. The event will be translated into
    // a touch event before put it into the queue. This function is only useful for PC.
    // \param x the mouse pointer x coordinate.
    // \param y the mouse pointer y coordinate in the window coordinate (the origin is at top left).
    // \param state the state of the button
    // \param isCtrlDown if the ctrl key (left and right) is down during the mouse action.
    void addPointerEvent(pInt32 x, pInt32 y, PInputPointingDeviceStateEnum state, bool isCtrlHeld);

    // Add keyboard event to the queue.
    // \param keyCode the raw scan code of the keyboard input.
    // \param key the translated key code.
    // \param state the state of the key button. 
    void addKeyEvent(pUint32 nativeScanCode, PInputKey key, pUint32 state);

    // Clear the current events. 
    void clear();

    // Get the number of events in queue.
    // \return the event number.
    pUint32 getNumberOfEvents() const;

    // Get the event at the index.
    // \param index the index.
    // \return the event at the index of the queue.
    PInputEvent* getEventAtIndex(pUint32 index);

private:
    // Allocate a new event node.
    PInputEvent* reserveEvent();

private:
    PInputEvent* m_events; // The event queue.
    pUint32      m_numberOfEvents; // The number of events in the queue.
    pUint32      m_numberOfEventsCached; // The total events in the pool.
    PDevice*     m_device; // The parent device.
};

#endif // PINPUT_H
