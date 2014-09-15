#ifndef ACTOR_H
#define ACTOR_H

#include "cocos2d.h"

#include <foundation/entity.h>

class TiledMap;

class Actor : public Entity, public cocos2d::CCNode
{
protected:
    Actor(World *world, TiledMap *tiledMap, const char *group, const char *name);

public:
    /* 
     * Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live"
     */
    virtual void update(float delta);

    virtual void reset();

    cocos2d::CCPoint boxToCocosSpace(const cocos2d::CCPoint &in);
    cocos2d::CCPoint cocosToBoxSpace(const cocos2d::CCPoint &in);

protected:
    cocos2d::CCSprite  *m_sprite;
    TiledMap           *m_tiledMap;

    cocos2d::CCPoint    m_originPosition;
    cocos2d::CCSize     m_originSize;
};

#endif // !ACTOR_H
