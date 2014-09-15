#include "dpad.h"

USING_NS_CC;

DPad::DPad()
    : m_delegate(NULL)
{
}

bool DPad::init()
{
    // add menu to layer
    CCMenu* menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    this->addChild(menu);

    // left 
    m_leftButton = CCMenuItemImage::create(
                                    "Thumb_dpad_left.png",
                                    "Thumb_dpad_left_pressed.png",
                                    this,
                                    menu_selector(DPad::menuCallback));
    m_leftButton->setPosition(CCPoint(50, 48));
    menu->addChild(m_leftButton);

    // right
    m_rightButton = CCMenuItemImage::create(
                                    "Thumb_dpad_right.png",
                                    "Thumb_dpad_right_pressed.png",
                                    this,
                                    menu_selector(DPad::menuCallback));
    m_rightButton->setPosition(CCPoint(150, 48));
    menu->addChild(m_rightButton);

    // add menu to layer
    CCMenu* menuFire = CCMenu::create();
    menuFire->setPosition(CCPointZero);
    this->addChild(menuFire);
    
    // jump
    m_fireButton = CCMenuItemImage::create(
                                    "Thumb_dpad_jump.png",
                                    "Thumb_dpad_jump_pressed.png",
                                    this,
                                    menu_selector(DPad::menuCallback));
    m_fireButton->setPosition(CCPoint(800-80, 48));
    menuFire->addChild(m_fireButton);

    this->scheduleUpdate();

    return true;
}

void DPad::update(float dt)
{
    if (m_delegate == NULL)
        return;
        
    if (0 ||
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        ((GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000) ||
#endif
        m_leftButton->isSelected())
    {
        if (!m_delegate->getKeyPressed(DPadDelegate::KeyLeft) && 
            !m_delegate->getKeyPressed(DPadDelegate::KeyRight))
        {
            m_delegate->setKeyPressed(DPadDelegate::KeyLeft);
            m_delegate->keyDown(DPadDelegate::KeyLeft);
        }
    }
    else
    {
        if (m_delegate->getKeyPressed(DPadDelegate::KeyLeft))
        {
            m_delegate->setKeyPressed(DPadDelegate::KeyLeft, false);
            m_delegate->keyUp(DPadDelegate::KeyLeft);
        }
    }

    if (0 ||
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        ((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000) ||
#endif
        m_rightButton->isSelected())
    {
        if (!m_delegate->getKeyPressed(DPadDelegate::KeyLeft) && 
            !m_delegate->getKeyPressed(DPadDelegate::KeyRight))
        {
            m_delegate->setKeyPressed(DPadDelegate::KeyRight);
            m_delegate->keyDown(DPadDelegate::KeyRight);
        }
    }
    else
    {
        if (m_delegate->getKeyPressed(DPadDelegate::KeyRight))
        {
            m_delegate->setKeyPressed(DPadDelegate::KeyRight, false);
            m_delegate->keyUp(DPadDelegate::KeyRight);
        }
    }

    if (0 ||
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        ((GetAsyncKeyState(VK_SPACE) & 0x8000) == 0x8000) ||
        ((GetAsyncKeyState(VK_UP) & 0x8000) == 0x8000) ||
#endif
        m_fireButton->isSelected())
    {
        if (!m_delegate->getKeyPressed(DPadDelegate::KeyFire))
        {
            m_delegate->setKeyPressed(DPadDelegate::KeyFire);
            m_delegate->keyDown(DPadDelegate::KeyFire);
        }
    }
    else
    {
        if (m_delegate->getKeyPressed(DPadDelegate::KeyFire))
        {
            m_delegate->setKeyPressed(DPadDelegate::KeyFire, false);
            m_delegate->keyUp(DPadDelegate::KeyFire);
        }
    }
}

void DPad::menuCallback(CCObject *pSender)
{
}

