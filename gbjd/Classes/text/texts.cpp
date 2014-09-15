#include "texts.h"

#include <layer/tiledmap.h>

USING_NS_CC;

Texts::Texts(World *world, TiledMap *tiledMap)
    : m_world(world)
    , m_tiledMap(tiledMap)
{
    CCTMXObjectGroup *group = m_tiledMap->objectGroup("Texts");
    CCArray *array = group->getObjects();
    if (array && array->count() > 0)
    {
        CCObject *obj = NULL;
        CCARRAY_FOREACH(array, obj)
        {
            CCDictionary *dict = dynamic_cast<CCDictionary *>(obj);
            
            // get position.

            // get size.

            // get text.
            CCObject *textObj = dict->objectForKey("text");
            CCDictionary *text = dynamic_cast<CCDictionary *>(dict->objectForKey("text"));
            CCLOG("%s", text->valueForKey("value")->getCString());

            // create sprite and add it.
            
        }
    }
}

Texts::~Texts()
{
}

