#include "boy.h"

#include <foundation/world.h>

#include <layer/tiledmap.h>

USING_NS_CC;

Boy::Boy(World *world, TiledMap *tiledMap)
    : Actor(world, tiledMap, "Actor", "Boy")
{
    m_sprite = CCSprite::create("boy.png");
    m_sprite->setAnchorPoint(ccp(0.5f, 0.5f));
    this->addChild(m_sprite);

    setType(Entity::EntityBoy);

#if defined (USE_BOX2D)
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(m_position.x * PTM_RADIO, m_position.y * PTM_RADIO);

    b2PolygonShape shape;
    // adjust size for image align and collision.
    shape.SetAsBox(m_size.width * PTM_RADIO / 2 - 0.02f, m_size.height * PTM_RADIO / 2 - 0.02f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape; 
    fixtureDef.density = 0.0f; 
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;

    m_body = Entity::world()->createBody(&bodyDef);
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
#endif

    m_speed = 4.0f;
    m_jumpForce = 700.0f;
    m_canJump = false;

    this->scheduleUpdate();
}

Boy::~Boy()
{
}

void Boy::update(float delta)
{
    // set velocity.
    if (getKeyPressed(DPadDelegate::KeyLeft))
    {
        m_body->SetLinearVelocity(b2Vec2(-m_speed, m_body->GetLinearVelocity().y));
    }
    
    if (getKeyPressed(DPadDelegate::KeyRight))
    {
        m_body->SetLinearVelocity(b2Vec2(m_speed, m_body->GetLinearVelocity().y));
    }
    
    if (getKeyPressed(DPadDelegate::KeyFire))
    {
        if (m_canJump)
        {
            if (m_body->GetLinearVelocity().y == 0)
            {
                m_body->ApplyForceToCenter(b2Vec2(0, m_jumpForce));
            }
        }
    }

    // contact.
    m_canJump = false;
    b2ContactEdge *edge = m_body->GetContactList();
    while (edge)
    {
        b2WorldManifold *manifold = new b2WorldManifold();
        edge->contact->GetWorldManifold(manifold);
        b2Vec2 normal = manifold->normal;
        if (edge->contact->IsTouching())
        {
            Entity *entity = (Entity *)edge->contact->GetFixtureB()->GetBody()->GetUserData();
            if (entity)
            {
                if (entity->getType() == Entity::EntityWall)
                {
                    if (normal.y < 0)
                    {
                        m_canJump = true;
                    }
                }
            }
        }
        edge = edge->next;
    }
    
    //CCLOG("boy m_position(%f, %f)", position().x, position().y);
    m_sprite->setPosition(boxToCocosSpace(position()));
}

CCPoint Boy::position() const
{
    CCPoint position;
    position.x = m_body->GetPosition().x / PTM_RADIO;
    position.y = m_body->GetPosition().y / PTM_RADIO;
    return position;
}

void Boy::keyDown(DPadDelegate::KeyCode key)
{
}

void Boy::keyUp(DPadDelegate::KeyCode key)
{
    // reset x velocity.
    if (key == DPadDelegate::KeyLeft ||
        key == DPadDelegate::KeyRight)
    {
        m_body->SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y));
    }
}

void Boy::reset()
{
    Actor::reset();

    m_body->SetTransform(b2Vec2(m_position.x * PTM_RADIO, m_position.y * PTM_RADIO), 0);
    m_body->SetAwake(false);
    m_body->SetAwake(true);
}
