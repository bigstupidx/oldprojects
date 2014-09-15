#ifndef WORLD_H
#define WORLD_H

#include "cocos2d.h"

#include <config/config.h>

#if defined (USE_BOX2D)
#include <Box2D/Box2D.h>
#endif

#include "entity.h"

#if defined (DEBUG_DRAW)
class GLESDebugDraw;
#endif

class World
{
    struct EntityNode
    {
        Entity      *value;
        EntityNode  *next;
    };
    
public:
    World(const cocos2d::CCPoint &gravity = cocos2d::CCPoint(0, -10.0f));
    ~World();

    void draw();

    void reset();

    void tick(float deltaTime);

    void add(Entity *entity);

#if defined (USE_BOX2D)
    b2Body *createBody(b2BodyDef *bodyDef) 
    { return m_world->CreateBody(bodyDef); }
#endif

private:
#if defined (USE_BOX2D)
    b2World        *m_world;
#endif
#if defined (DEBUG_DRAW)
    GLESDebugDraw  *m_debugDraw;
#endif

    EntityNode     *m_entitys;
    EntityNode      m_root;
    EntityNode     *m_tail;
};

#endif // !WORLD_H
