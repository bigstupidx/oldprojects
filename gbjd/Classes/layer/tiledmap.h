#ifndef TILEDMAP_H
#define TILEDMAP_H

#include "cocos2d.h"

class TiledMap : public cocos2d::CCNode
{
public:
    // We don't use CREATE_FUNC() macro here, because we should init with parameter stage.
    static TiledMap *create(int stage);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool initWithStage(int stage);

    ///////////////////////////////////////////////////////////////////////////
    //
    // CCTMXTiledMap functions.
    //
    ///////////////////////////////////////////////////////////////////////////
    cocos2d::CCTMXObjectGroup* objectGroup(const char *groupName);
    cocos2d::CCTMXLayer* layer(const char *layerName);
    cocos2d::CCString *property(const char *propertyName);
    cocos2d::CCSize tileSize();
    cocos2d::CCSize mapSize();
    cocos2d::CCPoint mapToBoxSpace(const cocos2d::CCPoint &in);
    cocos2d::CCPoint boxToMapSpace(const cocos2d::CCPoint &in);
    
private:
    cocos2d::CCTMXTiledMap* m_TMXTiledMap;
};

#endif // !TILEDMAP_H
