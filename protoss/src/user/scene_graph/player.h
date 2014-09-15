// player.h
// The layer contains a sequence of render passes. Each layer can 
// assume all preceding layers are finished with rendering 
// before itself.
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//
// 

#ifndef PLAYER_H
#define PLAYER_H

// DESIGN GUIDELINE:
// Usage 1:
// // create a new layer and insert into the end of the scene
// PLayer *layer;
// layer = pNew(PLayer("layer1", scene));
// // create a new layer and insert into the 2nd position at the
// // layer list of the scene.
// layer = pNew(PLayer("layer2", scene, 2));
//
// Usage 2:
// In PScene::render
// foreach layer
//   layer.render(renderState);
//
// Usage 3:
// // insert a new drawable into the layer.
// PDrawable *drawable = pNew(PDrawable("drawable", layer));

#include <PUser/pobject.h>
#include <PUser/prenderpass.h>

class PDrawable;


class P_DLLEXPORT PLayer : public PObject
{
public:
    PLayer(const pChar *name, PScene *parent, pInt32 position = -1);
    virtual ~PLayer();

    PDrawable* getdDrawable(const pChar* name);
    void deleteDrawables();

    PRenderPass *getRenderPass()
    { return &m_renderPass; }

    void update(pUint32 currentTime);

    void render(PRenderState *renderState);

private:
    PRenderPass m_renderPass;
};


#endif  //! PLAYER_H



