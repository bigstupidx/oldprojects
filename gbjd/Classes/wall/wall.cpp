#include "wall.h"

#include <layer/tiledmap.h>

#include <foundation/world.h>

USING_NS_CC;

Wall::Wall(World *world, TiledMap *tiledMap, CCDictionary *dict)
    : Entity(world, "wall")
{
    setType(Entity::EntityWall);
    
    CCLOG("name = %s, position_in_map = %f, %f, size_in_map = %f, %f", 
        dict->valueForKey("name")->getCString(), 
        dict->valueForKey("x")->floatValue(), 
        dict->valueForKey("y")->floatValue(),
        dict->valueForKey("width")->floatValue(),
        dict->valueForKey("height")->floatValue()); 

    // Get size.
    m_size.width = dict->valueForKey("width")->floatValue() / tiledMap->tileSize().width;
    m_size.height = dict->valueForKey("height")->floatValue() / tiledMap->tileSize().height;
    
    // Get coord.
    CCPoint coord;
    coord.x = dict->valueForKey("x")->floatValue() + m_size.width * tiledMap->tileSize().width / 2;
    coord.y = dict->valueForKey("y")->floatValue() + m_size.height * tiledMap->tileSize().height / 2;
    CCLOG("coord = (%f, %f)", coord.x, coord.y);
    m_position = tiledMap->mapToBoxSpace(coord);
    CCLOG("m_position = (%f, %f)", m_position.x, m_position.y);

    // The position value is always valid.
#if defined (USE_BOX2D)
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = b2Vec2(m_position.x * PTM_RADIO, m_position.y * PTM_RADIO);

    b2PolygonShape shape;
#endif

    // If the shape is polygon, the size will be CCPointZero.
    // Polygon?
    if (dict->objectForKey("points"))
    {
        CCArray *points = (CCArray *)dict->objectForKey("points");
        if (points->count() > 0)
        {
        #if defined (USE_BOX2D)
            shape.m_vertexCount = points->count();
            int n = 0;
        #endif
        
            CCObject *obj = NULL;
            CCARRAY_FOREACH(points, obj)
            {
                // TODO: need adjust position with size.
                CCDictionary *point = (CCDictionary *)obj;
                // Get coord.
                CCPoint coord;
                coord.x = dict->valueForKey("x")->floatValue();
                coord.y = dict->valueForKey("y")->floatValue();
                CCPoint position = tiledMap->mapToBoxSpace(coord);
            #if defined (USE_BOX2D)
                shape.m_vertices[n++].Set(position.x * PTM_RADIO, position.y * PTM_RADIO);
            #endif
            }
        }
        else
        {
            CCLOG("points count == 0!");
        }
    }
    else
    {
        // Rectangle?
    #if defined (USE_BOX2D)
        shape.SetAsBox(m_size.width / 2 * PTM_RADIO, m_size.height / 2 * PTM_RADIO);
    #endif
    }

    // Create body.
#if defined (USE_BOX2D)
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape; 
    fixtureDef.density = 1.0f; 
    fixtureDef.friction = 0.0f;

    m_body = Entity::world()->createBody(&bodyDef);
    m_body->CreateFixture(&fixtureDef); 
    m_body->SetUserData(this);
    // FIXME: visible key is not valid.
    if (dict->valueForKey("visible")->length() > 0)
    {
        m_body->SetActive(dict->valueForKey("visible")->boolValue());
    }
#endif

    CCLOG("name = %s, position = (%f, %f), size = (%f, %f)", dict->valueForKey("name")->getCString(), m_position.x, m_position.y, m_size.width, m_size.height);
}

void Wall::update(float deltaTime)
{
}
