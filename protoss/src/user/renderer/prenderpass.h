// prenderpass.h
// The rendering pass
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PRENDERPASS_H
#define PRENDERPASS_H

#include <PUser/pcamera.h>
#include <PUser/prendertarget.h>

#include <PCore/plist.h>


//class PAbstractCulling;
//class PAbstractSorting;
class PDrawable;

class P_DLLEXPORT PRenderPass 
{
public:
    PRenderPass();
    virtual ~PRenderPass();

    void setCamera(PCamera &camera);
    P_INLINE PCamera* getCamera() { return &m_camera; }

    // should we clone a rendertarget, or just keep the pointer?
    // what do PRenderPass do when PRenderTarget is released?
    // should PRenderPass manage renderTarget?
    void setRenderTarget(PRenderTarget &renderTarget);
    P_INLINE PRenderTarget* getRenderTarget() { return &m_renderTarget; }

    // TODO: complete culling and sorting.
    //PAbstractCulling* getCulling();
    //PAbstractSorting* getSorting();
    //void setCulling(const pChar *culling);
    //void setSorting(const pChar *sorting);

    // Add a drawable to the render pass.
    void addDrawable(PDrawable *drawable);
    // Add many drawables to the render pass at the same time.
    void addDrawables(const PList<PDrawable*> &drawables);
    // Remove the drawable from the render pass.
    void removeDrawable(PDrawable *drawable);
    // Remove drawable from the render pass.
    void removeDrawable(const pChar *name);
    // Clean the drawables in the render pass.
    void removeAllDrawables();

    // Execute the render pass.
    void execute();

private:
    PCamera             m_camera;
    PRenderTarget       m_renderTarget;

    PList<PDrawable *>  m_drawables;
    
    // TODO: design and implement culling and sorting modules.
    //PCullingFactory     m_cullingFactory;
    //PSortingFactory     m_sortingFactory;
    //PAbstractCulling    *m_culling;
    //PAbstractSorting    *m_sorting;
};


#endif // !PRENDERPASS_H
