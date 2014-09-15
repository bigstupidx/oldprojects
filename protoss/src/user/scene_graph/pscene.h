// pscene.h 
// The scene
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//
// 

#ifndef PSCENE_H
#define PSCENE_H

#include <PUser/pobject.h>

#include <PCore/parray.h>

// DESIGN GUIDELINE:
//
// usage 1: 
// PLayer* layer;
// // Create a new layer and insert the layer into the position 0 of
// // layer list in the scene.
// layer = pNew(PLayer("layer1", scene, 0));
// // Create a new layer and insert the layer into the back of layer
// // list in the scene.
// layer = pNew(PLayer("layer2", scene));
//    
// usage 2:
// PLayer *layer = scene->getLayer("layer1");
// // Remove the layer from the layer list of the scene and delete
// // the layer's memory
// pDelete(layer);
//

class PContext;
class PLayer;
class PRenderState;

class P_DLLEXPORT PScene : public PObject
{
    friend class PContext;

public:
    PScene(const pChar *name, PContext* context);
    virtual ~PScene();

    // Get the layer at certain position.
    PLayer *getLayer(pUint32 position);
    // Get the render by its name
    PLayer *getLayer(const pChar *name);
    // Remove all layers from this scene and
    // release memory of all layers.
    void deleteLayers();
    
    P_INLINE PContext* getContext() const
    { return m_context; }

protected:
    // Update the scene; called only in PContext.
    void update(pUint32 currentTime);
    // Render the scene layer by layer.
    void render(PRenderState *renderState);

private:
    PContext* m_context;
};

#endif // !PSCENE_H
