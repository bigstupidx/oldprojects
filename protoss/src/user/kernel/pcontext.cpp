// pcontext.h
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pcontext.h"

#include <PUser/pdevice.h>
#include <PUser/prenderstate.h>
#include <PUser/presourcemanager.h>
#include <PUser/pscene.h>

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>

PContext::PContext(const PContextProperties& properties)
    : m_properties(properties)
{
    m_state                = P_CONTEXT_STATE_UNINITIALIZED;
    m_device               = P_NULL;
    m_resourceManager      = P_NULL;
    m_renderState          = P_NULL;
    m_scene                = P_NULL;
}

PContext::~PContext()
{
    pAssert(m_device == P_NULL);
    pAssert(m_resourceManager == P_NULL);
    pAssert(m_renderState == P_NULL);
    pAssert(m_scene == P_NULL);
    pAssert(m_state == P_CONTEXT_STATE_UNINITIALIZED ||
             m_state == P_CONTEXT_STATE_ERROR ||
             m_state == P_CONTEXT_STATE_QUITING);
}

void PContext::quit()
{
    if (m_state != P_CONTEXT_STATE_UNINITIALIZED &&
        m_state != P_CONTEXT_STATE_QUITING)
    {
        pAssert(m_device != P_NULL);
        m_device->setState(P_DEVICE_STATE_CLOSED);
        pLogInfo("context is quitting");
        m_state = P_CONTEXT_STATE_QUITING;
    }
}

bool PContext::initialize()
{
    // It can't be called more than once.
    pAssert(m_state == P_CONTEXT_STATE_UNINITIALIZED);
    if (m_state != P_CONTEXT_STATE_UNINITIALIZED)
    {
        return true;
    }
    
    m_device          = pNew(PDevice(this));
    m_resourceManager = pNew(PResourceManager(this));
    m_renderState     = pNew(PRenderState(getScreenWidth(), getScreenHeight()));
    m_scene           = pNew(PScene("scene", this));

    return true;
}

void PContext::destroy()
{
    if (m_state != P_CONTEXT_STATE_UNINITIALIZED)
    {
        pDelete(m_resourceManager);
        pDelete(m_renderState);
        pDelete(m_device);
        pDelete(m_scene);

        m_state = P_CONTEXT_STATE_UNINITIALIZED;
    }
}

bool PContext::update(pUint32 currentTime)
{
    // Callback before update this frame.
    onUpdate(currentTime);
    
    // One iteration of window main loop.
    m_device->update();

    // When the window is closed, we quit the context.
    if (m_device->getState() == P_DEVICE_STATE_CLOSED)
    {
        pLogInfo("device is closed");
        m_state = P_CONTEXT_STATE_QUITING;
    }

    // Rendering.
    // TODO: rework the scene rendering. Use
    // render engine and render queue instead of calling 
    if (m_state == P_CONTEXT_STATE_RUNNING)
    {
        // FIXME: put the clear command here.
        //m_scene->update(currentTime);
        //m_renderEngine->beginFrame();
        //m_scene->render();
        //m_renderEngine->endFrame();
    }

    return true;
}

void PContext::pause()
{
}

bool PContext::resume()
{
    return true;
}

void PContext::setState(PContextState state)
{
    m_state = state;
}

bool PContext::onInitialized()
{
    return true;
}

bool PContext::onClose()
{
    return true;
}

void PContext::onDestroy()
{
}
    
void PContext::onScreenResized(pUint32 width, pUint32 height)
{
    // Update all layers' viewports
}

bool PContext::onUpdate(pUint32 currentTime)
{
    return true;
}

