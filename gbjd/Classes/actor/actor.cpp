#include "actor.h"

#include <layer/tiledmap.h>

USING_NS_CC;

Actor::Actor(World *world, TiledMap *tiledMap, const char *group, const char *name)
    : Entity(world, "actor")
    , m_tiledMap(tiledMap)
    , m_sprite(NULL)
{    
    CCDictionary *actor = m_tiledMap->objectGroup(group)->objectNamed(name);

    CCLOG("name = %s, position_in_map = %f, %f, size_in_map = %f, %f", 
        actor->valueForKey("name")->getCString(), 
        actor->valueForKey("x")->floatValue(), 
        actor->valueForKey("y")->floatValue(),
        actor->valueForKey("width")->floatValue(),
        actor->valueForKey("height")->floatValue()); 
    
    // Get size.
    m_size.width = actor->valueForKey("width")->floatValue() / tiledMap->tileSize().width;
    m_size.height = actor->valueForKey("height")->floatValue() / tiledMap->tileSize().height;

    // Get coord.
    CCPoint coord;
    coord.x = actor->valueForKey("x")->floatValue() + m_size.width * tiledMap->tileSize().width / 2;
    coord.y = actor->valueForKey("y")->floatValue() + m_size.height * tiledMap->tileSize().height / 2;
    CCLOG("coord = (%f, %f)", coord.x, coord.y);
    m_position = tiledMap->mapToBoxSpace(coord);
    CCLOG("m_position = (%f, %f)", m_position.x, m_position.y);

    m_originPosition = m_position;
    m_originSize = m_size;
}

void Actor::update(float delta)
{
}

CCPoint Actor::boxToCocosSpace(const cocos2d::CCPoint &in)
{
    CCPoint out;
    out.x = in.x * m_tiledMap->tileSize().width;
    out.y = in.y * m_tiledMap->tileSize().height;
    return out;
}

CCPoint Actor::cocosToBoxSpace(const cocos2d::CCPoint &in)
{
    CCPoint out;
    out.x = in.x * m_tiledMap->tileSize().width;
    out.y = in.y * m_tiledMap->tileSize().height;
    return out;
}

void Actor::reset()
{
    m_position = m_originPosition;
    m_size = m_originSize;
}
