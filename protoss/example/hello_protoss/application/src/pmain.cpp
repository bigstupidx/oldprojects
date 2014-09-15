// p_main.cpp
// Create the context and add it to activity.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

//#include <PUser>
//#include <PSystem>

#include <PActivity>
#include <PContext>

/*
void setupScene(PContext* context)
{
    PScene* scene = context->getScene();
    PLayer* layer = pNew(PLayer(scene));

    // sprint 1 mesh (stream) -> suyu, resource -> lihw
    PMesh* mesh = context->getResourceManager()->retainMesh("object.mes");
    PTexture* texture = context->getResourceManager()->retainTexture("texture.png");
    PShader* shader = context->getResourceManager()->retainShader("vert.glsl", "frag.glsl");

    // sprint 2
    PDrawable* drawable = pNew(PDrawable(layer));
    drawable->getMaterial()->setShader(shader);
    drawable->getMaterial()->addTexture(texture);
    drawable->getGeometry()->setMesh(mesh);
    
    // sprint 1 -> jihao
    layer->getCamera()->setPosition(10, 0, 0);
    layer->getCamera()->setOrientation(0, 0, 0, 0, 1, 0);
    layer->getCamera()->setProjection(P_CAMERA_PROJECTION_PERSPECTIVE);

    // sprint 3
    layer->getCulling()->setCulling(P_CULLING_DEFAULT);
    layer->getSorting()->setSorting(P_SORTING_DEFAULT); 
    
    // sprint 1 -> jihao
    layer->getRenderTarget()->setViewport(-1, -1, -1, -1);
    layer->getRenderTarget()->setStencilWritable(false);
    layer->getRenderTarget()->setFrameBuffer(P_NULL);

    // sprint 1, object hierachy -> PData/PObject -> suyu
}
*/
void pMain(int argc, char* argv[])
{
    pAssert(PActivity::s_activity != P_NULL);

    if (PActivity::s_activity != P_NULL)
    {
        PContextProperties contextProperties;
        contextProperties.m_contextName = PString("default");
        contextProperties.m_multisamples = 2;

        PContext* context = pNew(PContext(contextProperties));
        PActivity::s_activity->addContext(context);

        //setupScene(context);
    }
    else
    {
        pLogError("No running activity");
    }
}


