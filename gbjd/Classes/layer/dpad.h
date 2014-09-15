#ifndef DPAD_H
#define DPAD_H

#include "cocos2d.h"

class DPadDelegate
{
public:
    enum KeyCode
    {
        KeyLeft,
        KeyRight,
        KeyFire,
        KeyCount
    };

    virtual void keyDown(KeyCode key) = 0;
    virtual void keyUp(KeyCode key) = 0;
    
    bool getKeyPressed(KeyCode key) { return m_keyPressed[key]; }
    void setKeyPressed(KeyCode key, bool pressed = true) { m_keyPressed[key] = pressed; }

private:
    bool m_keyPressed[KeyCount];
};

class DPad : public cocos2d::CCNode
{
private:
    DPad();

public:
    virtual bool init();

    virtual void update(float delta);

    CREATE_FUNC(DPad);
    
    void setDelegate(DPadDelegate *delegate) { m_delegate = delegate; }

private:
    DPadDelegate *m_delegate;
    
    cocos2d::CCMenuItemImage*   m_leftButton;
    cocos2d::CCMenuItemImage*   m_rightButton;
    cocos2d::CCMenuItemImage*   m_fireButton;

    void menuCallback(cocos2d::CCObject *pSender);
};

#endif // !DPAD_H
