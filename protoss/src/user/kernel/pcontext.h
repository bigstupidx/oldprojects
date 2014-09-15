// pcontext.h
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PCONTEXT_H
#define PCONTEXT_H

#include <PUser/pcontextproperties.h>

#include <PCore/pstring.h>

class PDevice;
class PResourceManager;
class PRenderState;
class PScene;

enum PContextState
{
    P_CONTEXT_STATE_UNINITIALIZED, ///< Context is not initialized.
    P_CONTEXT_STATE_RUNNING,        ///< Context is running.
    P_CONTEXT_STATE_PAUSED,        ///< Context is paused. Freezed in the main loop.
    P_CONTEXT_STATE_QUITING,       ///< Context is about to quit.
    P_CONTEXT_STATE_ERROR,         ///< Some fatal errors in the context.

    P_CONTEXT_STATE_FIRST = P_CONTEXT_STATE_UNINITIALIZED,
    P_CONTEXT_STATE_LAST = P_CONTEXT_STATE_ERROR,
    P_CONTEXT_STATE_NUMBER = P_CONTEXT_STATE_LAST - P_CONTEXT_STATE_FIRST + 1,
};

class PContext
{
public:
    PContext(const PContextProperties& properties); 
    virtual ~PContext();

    bool initialize();
    bool update(pUint32 currenTime);
    void destroy();
    void quit();
    void pause();
    bool resume();

    void setState(PContextState state);

    P_INLINE const PString&         getName() const { return m_properties.m_contextName; }
    P_INLINE const pUint32          getScreenWidth() const { return m_properties.m_screenWidth; }
    P_INLINE const pUint32          getScreenHeight() const { return m_properties.m_screenHeight; }
    P_INLINE PContextState          getState() const { return m_state; }
    P_INLINE PDevice*               getDevice() const { return m_device; }
    P_INLINE PScene*                getScene() const { return m_scene; }
    P_INLINE PRenderState*          getRenderState() const { return m_renderState; }
    P_INLINE PResourceManager*      getResourceManager() const { return m_resourceManager; }
    P_INLINE PContextProperties*    getProperties() { return &m_properties; }

public: 
    virtual bool onInitialized();
    virtual void onDestroy();
    virtual bool onClose();
    virtual void onScreenResized(pUint32 width, pUint32 height);
    virtual bool onUpdate(pUint32 currentTime);

private:
    PContextProperties      m_properties;
    PContextState           m_state;
    PDevice*                m_device;
    PResourceManager*       m_resourceManager;
    PScene*                 m_scene;
    PRenderState*           m_renderState;
};

#endif // !PCONTEXT_H
