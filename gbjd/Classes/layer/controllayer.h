#ifndef CONTROLLAYER_H
#define CONTROLLAYER_H

#include "cocos2d.h"

#include "dpad.h"

class StageScene;

class ControlLayer : public cocos2d::CCLayer
{
public:
    // implement the "static node()" method manually
    static ControlLayer *create(StageScene *scene);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithScene(StageScene *scene);

    void setDPadDelegate(DPadDelegate *delegate) { m_dpad->setDelegate(delegate); }

private:
    void menuCallback(cocos2d::CCObject *pSender);
    
private:
    // Buttons.
    cocos2d::CCMenuItemImage    *m_backBtn;
    cocos2d::CCMenuItemImage    *m_resetBtn;
    cocos2d::CCMenuItemImage    *m_soundBtn;

    // Arrows.
    DPad       *m_dpad;

    // Stage scene.
    StageScene  *m_scene;
};

#endif // !CONTROLLAYER_H
