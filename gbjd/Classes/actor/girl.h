#ifndef GIRL_H
#define GIRL_H

#include "cocos2d.h"

#include "actor.h"

class Girl : public Actor
{
public:
    Girl(World *world, TiledMap *tiledMap);
    ~Girl();

    /* 
     * Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live"
     */
    virtual void update(float delta);

    virtual cocos2d::CCPoint position() const;

    void reset();
            
private:
};

#endif // !GIRL_H
