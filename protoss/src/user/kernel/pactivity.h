// pactivity.h 
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PACTIVITY_H
#define PACTIVITY_H

#include <PGlobal/pglobal.h>

class PContext;

class P_DLLEXPORT PActivity
{
public:
    PActivity(pInt32 argc, pChar** argv);
    virtual ~PActivity();

    P_INLINE pUint32 getNumberOfContexts() const { return m_contextCount; }


    bool addContext(PContext* context);
    PContext* findContext(pUint32 contextId);
    PContext* findContext(const pChar* contextName);
    void removeContext(PContext* context);
    void removeContext(pUint32 contextId);
    void removeContext(const pChar* contextName);

    // TODO:
    // events
    // resume
    // pause

    // All global variables need to be visited through PActivity for 
    // records.
public:
    // The globally unique instance of PActivity.
    P_GLOBAL static PActivity* s_activity;

private:
    // Context array 
    PContext*      m_contexts[P_CONTEXT_MAX_COUNT];
    pUint32        m_contextCount;
};

// Get the global application instance.
P_EXTERN PActivity* P_APIENTRY pGetActivity();

#endif // !PACTIVITY_H


