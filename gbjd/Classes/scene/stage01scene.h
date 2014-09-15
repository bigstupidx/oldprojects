#ifndef STAGE01SCENE_H
#define STAGE01SCENE_H

#include "cocos2d.h"

#include "stagescene.h"

USING_NS_CC;

class Stage01Scene : public StageScene
{
public:
    Stage01Scene();
    ~Stage01Scene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    virtual void update(float deltaTime);

    virtual void draw();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(Stage01Scene);

    virtual void reset();
    virtual void pass();
    virtual void fail();
    
private:
    
};

#endif // !STAGE01SCENE_H
