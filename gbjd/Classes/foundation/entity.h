#ifndef ENTITY_H
#define ENTITY_H

#include "cocos2d.h"

#include <config/config.h>

#if defined (USE_BOX2D)
#include <Box2D/Box2D.h>
#endif

class World;

class Entity
{
protected:
    Entity(World *world, const char *name = NULL);
    ~Entity();

public:
    enum EntityType
    {
        EntityBoy,
        EntityGirl,
        EntityWall,
        EntityCount
    };
    
    void setName(const char *name);
    cocos2d::CCString name() const { return m_name; }

    virtual void setPosition(const cocos2d::CCPoint &position);
    virtual cocos2d::CCPoint position() const { return m_position; }

    virtual void setSize(const cocos2d::CCSize &size);
    cocos2d::CCSize size() const { return m_size; }

    void setType(EntityType type) { m_type = type; }
    EntityType getType() { return m_type; }

    World *world() const { return m_world; }

protected:
    // Notice: the position of entity is in box space.
#if defined (USE_BOX2D)
    b2Body             *m_body;
#endif
    cocos2d::CCPoint    m_position;
    cocos2d::CCSize     m_size;

private:
    int                 m_id;
    cocos2d::CCString   m_name;
    World              *m_world;
    EntityType          m_type;
};


#endif // !ENTITY_H
