#ifndef WALLS_H
#define WALLS_H

#include "cocos2d.h"

class World;
class TiledMap;

class Walls : public cocos2d::CCNode
{
public:
    Walls(World *world, TiledMap *tiledMap);
    ~Walls();
    
private:
    World       *m_world;
    TiledMap    *m_tiledMap;
};

#endif // !WALL_H
