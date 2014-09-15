#include "entity.h"

#include "world.h"

USING_NS_CC;

Entity::Entity(World *world, const char *name)
{
    static int uid = 0;
    m_id = uid++;
    
    if (name)
    {
        setName(name);
    }
    else
    {
        m_name.initWithFormat("Entity %d", m_id);
    }
    
    m_position.setPoint(0, 0);
    m_size.setSize(0, 0);

    m_world = world;
#if defined (USE_BOX2D)
    m_body = NULL;
#endif

    m_world->add(this);
}

Entity::~Entity()
{
}

void Entity::setName(const char *name)
{
    m_name.initWithFormat("%s %d", name, m_id);
}

void Entity::setPosition(const CCPoint &position)
{
    m_position = position;
}

void Entity::setSize(const CCSize &size)
{
    m_size = size;
}

