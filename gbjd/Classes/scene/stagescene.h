#ifndef STAGESCENE_H
#define STAGESCENE_H

#include "cocos2d.h"

#include <layer/controllayer.h>

class TiledMap;
class Boy;
class Girl;
class World;
class Texts;

class StageScene : public cocos2d::CCLayer
{
public:
    enum
    {
        BACKGROUND_LAYER,
        STAGE_LAYER,
        ACTOR_LAYER,
        CONTROL_LAYER,
        POPUP_LAYER,
    };
    
public:
    StageScene();
    virtual ~StageScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool initWithStage(int stage);
    
    virtual void onExit();

    virtual void reset() = 0;
    virtual void pass() = 0;
    virtual void fail() = 0;
    
protected:    
    int                 m_stage;
    // Control layer.
    ControlLayer       *m_controlLayer;
    // Tiled map.
    TiledMap           *m_tiledMap;
    // Actors.
    Boy                *m_boy;
    Girl               *m_girl;
    World              *m_world;
    Texts              *m_texts;
};

#endif // !STAGESCENE_H
