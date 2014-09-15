#include "walls.h"

#include "wall.h"

#include <foundation/world.h>

#include <layer/tiledmap.h>

USING_NS_CC;

Walls::Walls(World *world, TiledMap *tiledMap)
    : m_world(world)
    , m_tiledMap(tiledMap)
{
    CCTMXObjectGroup *group = m_tiledMap->objectGroup("Walls");
    CCArray *array = group->getObjects();
    if (array && array->count() > 0)
    {
        CCObject *obj = NULL;
        CCARRAY_FOREACH(array, obj)
        {
            CCDictionary *dict = dynamic_cast<CCDictionary *>(obj);
            Wall *wall = new Wall(world, tiledMap, dict);
            this->addChild(wall);
        }
    }
}

Walls::~Walls()
{
}
