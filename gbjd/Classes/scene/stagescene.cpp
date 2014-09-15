#include "stagescene.h"

#include <layer/tiledmap.h>

USING_NS_CC;

StageScene::StageScene()
    : m_stage(0)
    , m_controlLayer(NULL)
    , m_tiledMap(NULL)
    , m_boy(NULL)
    , m_girl(NULL)
    , m_world(NULL)
    , m_texts(NULL)
{
}

StageScene::~StageScene()
{
}

void StageScene::onExit()
{
    // super
    CCLayer::onExit();
}

bool StageScene::initWithStage(int stage)
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    // Save m_stage.
    m_stage = stage;

    // Create and add control layer.
    m_controlLayer = ControlLayer::create(this);
    m_controlLayer->setPosition(CCPointZero);
    this->addChild(m_controlLayer, CONTROL_LAYER);

    // Create tiled map.
    m_tiledMap = TiledMap::create(m_stage);
    if (m_tiledMap)
    {
        this->addChild(m_tiledMap);
    }

    return true;
}
