#include "girl.h"

#include <foundation/world.h>

#include <layer/tiledmap.h>

USING_NS_CC;

Girl::Girl(World *world, TiledMap *tiledMap)
    : Actor(world, tiledMap, "Actor", "Girl")
{
    m_sprite = CCSprite::create("girl.png");
    m_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
    this->addChild(m_sprite);

    setType(Entity::EntityGirl);
    
#if defined (USE_BOX2D)
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(m_position.x * PTM_RADIO, m_position.y * PTM_RADIO);

    b2PolygonShape shape;
    b2Vec2 shapeBox = b2Vec2(m_size.width / 2 * PTM_RADIO, m_size.height / 2 * PTM_RADIO);
    // adjust size for image align and collision.
    shapeBox -= b2Vec2(0.02f, 0.02f);
    shape.SetAsBox(shapeBox.x, shapeBox.y);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape; 
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;

    m_body = Entity::world()->createBody(&bodyDef);
    m_body->CreateFixture(&fixtureDef); 
    m_body->SetUserData(this);
#endif

    this->scheduleUpdate();
}

Girl::~Girl()
{
}

void Girl::update(float delta)
{
    m_sprite->setPosition(boxToCocosSpace(position()));
}

CCPoint Girl::position() const
{
    CCPoint position;
    position.x = m_body->GetPosition().x / PTM_RADIO;
    position.y = m_body->GetPosition().y / PTM_RADIO;
    return position;
}

void Girl::reset()
{
    Actor::reset();

    m_body->SetTransform(b2Vec2(m_position.x * PTM_RADIO, m_position.y * PTM_RADIO), 0);
    m_body->SetAwake(false);
    m_body->SetAwake(true);
}

