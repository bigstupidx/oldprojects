#include "stage01scene.h"

#include <actor/boy.h>
#include <actor/girl.h>
#include <wall/walls.h>
#include <text/texts.h>

#include <foundation/world.h>

#include <layer/tiledmap.h>

USING_NS_CC;

Stage01Scene::Stage01Scene()
{
    m_stage = 1;
}

Stage01Scene::~Stage01Scene()
{
    CC_SAFE_DELETE(m_world);
}

CCScene* Stage01Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Stage01Scene *layer = Stage01Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Stage01Scene::init()
{
    if (!StageScene::initWithStage(m_stage))
    {
        return false;
    }

    // World.
    m_world = new World();

    // Boy.
    m_boy = new Boy(m_world, m_tiledMap);
    this->addChild(m_boy);

    // Girl.
    m_girl = new Girl(m_world, m_tiledMap);
    this->addChild(m_girl);

    // Walls
    Walls *walls = new Walls(m_world, m_tiledMap);

    // Texts
    Texts *texts = new Texts(m_world, m_tiledMap);

    // controller
    m_controlLayer->setDPadDelegate(m_boy);

    this->scheduleUpdate();

#if defined (DEBUG_DRAW)
    // disable all objects.
    m_tiledMap->setVisible(0);
    m_boy->setVisible(0);
    m_girl->setVisible(0);
#endif

    return true;
}

void Stage01Scene::update(float deltaTime)
{
    m_world->tick(deltaTime);
}

void Stage01Scene::draw()
{
#if defined (DEBUG_DRAW)
    m_world->draw();
#else
    StageScene::draw();
#endif
}

void Stage01Scene::reset()
{
    m_world->reset();
    m_boy->reset();
    m_girl->reset();
}

void Stage01Scene::pass()
{
}

void Stage01Scene::fail()
{
}
