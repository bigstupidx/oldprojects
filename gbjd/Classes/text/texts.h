#ifndef TEXTS_H
#define TEXTS_H

#include "cocos2d.h"

class World;
class TiledMap;

class Texts : public cocos2d::CCNode
{
public:
    Texts(World *world, TiledMap *tiledMap);
    ~Texts();
    
private:
    World       *m_world;
    TiledMap    *m_tiledMap;
};

#endif // !TEXTS_H
