#include "TiledMap.h"

USING_NS_CC;

TiledMap *TiledMap::create(int stage)
{
    TiledMap *pRet = new TiledMap();
    if (pRet->initWithStage(stage))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool TiledMap::initWithStage(int stage)
{
    if (m_TMXTiledMap)
    {
        this->removeChild(m_TMXTiledMap);
    }
    
    // load new tilemap
    char filename[128];
    
    sprintf(filename, "stage%d%d.tmx", stage / 10, stage % 10);
    
    m_TMXTiledMap = CCTMXTiledMap::create(filename);

    if (m_TMXTiledMap)
    {
        this->addChild(m_TMXTiledMap);
    }

    return (m_TMXTiledMap != NULL);
}

CCTMXObjectGroup* TiledMap::objectGroup(const char *groupName)
{
    if (m_TMXTiledMap)
    {
        return m_TMXTiledMap->objectGroupNamed(groupName);
    }
    else
    {
        return NULL;
    }
}

CCTMXLayer* TiledMap::layer(const char *layerName)
{
    if (m_TMXTiledMap)
    {
        return m_TMXTiledMap->layerNamed(layerName);
    }
    else
    {
        return NULL;
    }
}

CCString *TiledMap::property(const char *propertyName)
{
    if (m_TMXTiledMap)
    {
        return m_TMXTiledMap->propertyNamed(propertyName);
    }
    else
    {
        return NULL;
    }
}

CCSize TiledMap::tileSize()
{
    if (m_TMXTiledMap)
    {
        return m_TMXTiledMap->getTileSize();
    }
    else
    {
        return CCSizeMake(0, 0);
    }
}

CCSize TiledMap::mapSize()
{
    if (m_TMXTiledMap)
    {
        return m_TMXTiledMap->getMapSize();
    }
    else
    {
        return CCSizeMake(0, 0);
    }
}

CCPoint TiledMap::boxToMapSpace(const cocos2d::CCPoint &in)
{
    CCPoint out;
    out.x = in.x * tileSize().width;
    out.y = in.y * tileSize().height;
    return out;
}

CCPoint TiledMap::mapToBoxSpace(const cocos2d::CCPoint &in)
{
    CCPoint out;
    out.x = in.x / tileSize().width;
    out.y = in.y / tileSize().height;
    return out;
}

