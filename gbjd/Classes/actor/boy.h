#ifndef BOY_H
#define BOY_H

#include "cocos2d.h"

#include "actor.h"

#include <layer/dpad.h>

class Boy : public Actor, public DPadDelegate
{
public:
    Boy(World *world, TiledMap *tiledMap);
    ~Boy();

    /* 
     * Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live"
     */
    virtual void update(float delta);

    void reset();

    virtual cocos2d::CCPoint position() const;

    void keyDown(DPadDelegate::KeyCode key);

    void keyUp(DPadDelegate::KeyCode key);
    
private:
    float m_speed;
    float m_jumpForce;
    bool  m_canJump;
};

#endif // !BOY_H
