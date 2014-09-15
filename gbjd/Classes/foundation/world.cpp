#include "world.h"

#if defined (DEBUG_DRAW)
#include "GLES-render.h"
#endif

USING_NS_CC;

World::World(const CCPoint &gravity)
{
#if defined (USE_BOX2D)
    b2Vec2 newGravity(gravity.x, gravity.y);
    newGravity.y = -20.0f;
    m_world = new b2World(newGravity);
    m_world->SetAllowSleeping(false);
#endif

    m_root.value = NULL;
    m_root.next = NULL;
    m_tail = &m_root;

#if defined (DEBUG_DRAW)
    m_debugDraw = new GLESDebugDraw(32);  
    m_world->SetDebugDraw(m_debugDraw);
    uint32 flags = 0;  
    flags += b2Draw::e_shapeBit;
    m_debugDraw->SetFlags(flags);  
#endif
}

World::~World()
{
#if defined (USE_BOX2D)
    CC_SAFE_DELETE(m_world);

    EntityNode *node = m_root.next;
    while (node)
    {
        EntityNode *old = node;
        node = node->next;
        free(old);
    }
#endif
}

void World::tick(float deltaTime)
{
#if defined (USE_BOX2D)
    m_world->Step(deltaTime, 8, 8);
#endif
}

void World::add(Entity *entity)
{
    EntityNode *node = (EntityNode *)malloc(sizeof(EntityNode));
    node->value = entity;
    node->next = NULL;
    
    m_tail->next = node;
    m_tail = node;
}

void World::draw()
{
#if defined (DEBUG_DRAW)
    glDisable(GL_TEXTURE_2D);  
    glDisableClientState(GL_COLOR_ARRAY);  
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);  
      
    m_world->DrawDebugData();  
      
    glEnable(GL_TEXTURE_2D);  
    glEnableClientState(GL_COLOR_ARRAY);  
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);  
#endif
}

void World::reset()
{
    m_world->ClearForces();
}
