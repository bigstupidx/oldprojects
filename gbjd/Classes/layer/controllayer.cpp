#include "controllayer.h"

#include "dpad.h"

#include <scene/stagescene.h>

USING_NS_CC;

ControlLayer *ControlLayer::create(StageScene *scene)
{
    ControlLayer *pRet = new ControlLayer();
    if (pRet->initWithScene(scene))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool ControlLayer::initWithScene(StageScene *scene)
{
    if (!CCLayer::init())
    {
        return false;
    }

    // save scene
	m_scene = scene;
	
    // add menu to layer
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);

    const int buttonEdge = 31;
    const int buttonGap = 5;
    const int buttonSize = 62;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint point(visibleSize.width - (buttonEdge + buttonGap), visibleSize.height - (buttonEdge + buttonGap));

    // create speaker menu item
    m_soundBtn = CCMenuItemImage::create("Thumb_speaker.png",
                    "Thumb_speaker_pressed.png",
                    this,
                    menu_selector(ControlLayer::menuCallback));
    
	m_soundBtn->setPosition(point);
	pMenu->addChild(m_soundBtn);
	point.x -= buttonSize + buttonGap;

    // create reset menu item
    m_resetBtn = CCMenuItemImage::create("Thumb_back.png",
                    "Thumb_back_pressed.png",
                    this,
                    menu_selector(ControlLayer::menuCallback));
    
	m_resetBtn->setPosition(point);
	pMenu->addChild(m_resetBtn);
	point.x -= buttonSize + buttonGap;
    
    // create back menu item
    m_backBtn = CCMenuItemImage::create("Thumb_back.png",
                    "Thumb_back_pressed.png",
                    this,
                    menu_selector(ControlLayer::menuCallback));
    
	m_backBtn->setPosition(point);
	pMenu->addChild(m_backBtn);
	point.x -= buttonSize + buttonGap;

	// add dpad
	m_dpad = DPad::create();
	this->addChild(m_dpad);

	return true;
}

void ControlLayer::menuCallback(CCObject *pSender)
{
    if (pSender == m_backBtn)
    {
        CCDirector::sharedDirector()->popScene();
    }
    else if (pSender == m_resetBtn)
    {
        if (m_scene)
        {
            m_scene->reset();
        }
    }
}
