#ifndef WALL_H
#define WALL_H

#include "cocos2d.h"

#include <foundation/entity.h>

class World;
class TiledMap;

class Wall : public Entity, public cocos2d::CCNode
{
public:
    Wall(World *world, TiledMap *tiledMap, cocos2d::CCDictionary *dict);

    /* 
     * Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live"
     */
    virtual void update(float delta);

protected:
    cocos2d::CCSprite   *m_sprite;
    TiledMap            *m_tiledMap;
};

#endif // !WALL_H
