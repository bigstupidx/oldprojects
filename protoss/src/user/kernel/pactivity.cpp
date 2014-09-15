// pactivity.cpp
//
// Copyright 2012 by Hongwei Li. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pactivity.h"

#include <PUser/pcontext.h>

#include <PSystem/pmemory.h>

PActivity* PActivity::s_activity = P_NULL;

PActivity::PActivity(pInt32 argc, pChar** argv)
{
    pAssert(s_activity == P_NULL);
    if (s_activity == P_NULL)
    {
        for (pUint32 i = 0; i < P_CONTEXT_MAX_COUNT; ++i)
        {
            m_contexts[i] = P_NULL;
        }

        m_contextCount = 0;

        s_activity = this;
    }
}

PActivity::~PActivity()
{
    for (pUint32 i = 0; i < m_contextCount; ++i)
    {
        pDelete(m_contexts[i]);
    }
    m_contextCount = 0;
}

bool PActivity::addContext(PContext* context)
{
    // Check if the context with the same name existing.
    for (pUint32 i = 0; i < m_contextCount; ++i)
    {
        if (m_contexts[i]->getName() == context->getName())
        {
            return false;
        }
    }

    // Check if there is still some space to have a new context.
    if (m_contextCount < P_CONTEXT_MAX_COUNT)
    {
       m_contexts[m_contextCount] = context;
       m_contextCount++;
       return true;
    }

    return false;
}

PContext* PActivity::findContext(const pChar *contextName)
{
    for (pUint32 i = 0; i < m_contextCount; ++i)
    {
        // Find the context by name 
        if (m_contexts[i]->getName() == contextName)
        {
            return m_contexts[i];
        }
    }
    return P_NULL;
}

PContext* PActivity::findContext(pUint32 contextId)
{
    if (contextId >= P_CONTEXT_MAX_COUNT)
    {
       return P_NULL;
    }

    return m_contexts[contextId];
}
    
void PActivity::removeContext(PContext* context)
{
    for (pUint32 i = 0; i < m_contextCount; ++i)
    {
        if (m_contexts[i] == context)
        {
            for (pUint32 j = i; j < m_contextCount - 1; ++j)
            {
                m_contexts[j] = m_contexts[j + 1];
            }
            m_contexts[m_contextCount - 1] = P_NULL;

            m_contextCount -= 1;

            break;
        }
    }        
}

void PActivity::removeContext(pUint32 contextId)
{
    pAssert(contextId < m_contextCount);
    if (contextId >= m_contextCount)
    {
        return ;
    }

    for (pUint32 j = contextId; j < m_contextCount - 1; ++j)
    {
        m_contexts[j] = m_contexts[j + 1];
    }
    m_contexts[m_contextCount - 1] = P_NULL;

    m_contextCount -= 1;
}

void PActivity::removeContext(const pChar* contextName)
{
    pUint32 i = 0;
    for (i = 0; i < m_contextCount; ++i)
    {
        if (m_contexts[i]->getName() == contextName)
        {
            for (pUint32 j = i; j < m_contextCount - 1; ++j)
            {
                m_contexts[j] = m_contexts[j + 1];
            }
        }
    }

    if (i != m_contextCount)
    {
        m_contexts[m_contextCount - 1] = P_NULL;

        m_contextCount -= 1;
    }
}

PActivity* P_APIENTRY pGetActivity()
{
    return PActivity::s_activity;
}

