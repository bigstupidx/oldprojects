// presourceobject.cpp
// The base class of all resource objects.
// 
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "presourceobject.h"

#include <PUser/presourcemanager.h>

#include <PSystem/pdebug.h>
#include <PSystem/ptime.h>

    
PResourceObject::PResourceObject(const pChar* name, PResourceManager* resourceManager, 
    PResourceFlagEnum flag, PResourceTypeEnum type)
    : m_name(name)
{
    m_ref = 1;
    m_flag = flag;
    m_type = type;
    m_resourceManager = resourceManager;
    m_lastReferred = pTimeGetCurrentTimestamp();
}

PResourceObject::~PResourceObject()
{
    pAssert(m_ref == 0);
}

void PResourceObject::retain()
{
    // FIXME: make the following line thread-safe
    ++m_ref;

    m_lastReferred = pTimeGetCurrentTimestamp();
}

void PResourceObject::release()
{
    // FIXME: make the following line thread-safe
    --m_ref;
    if (m_ref == 0)
    {
        m_resourceManager->removeResourceObject(this);

        pDeleteThis(this);
    }
}
    
void PResourceObject::discard()
{
    if (m_state == P_RESOURCE_INSTORAGE)
    {
        return ;
    }
    discardResource();
    m_state = P_RESOURCE_INSTORAGE;
}

void PResourceObject::restore()
{
    if (m_state == P_RESOURCE_INMEMORY)
    {
        return ;
    }
    restoreResource();
    m_state = P_RESOURCE_INMEMORY;
}
