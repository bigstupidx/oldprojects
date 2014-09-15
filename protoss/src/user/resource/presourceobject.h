// presourceobject.h
// The base class of all resource objects.
// 
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PRESOURCEOBJECT_H
#define PRESOURCEOBJECT_H

#include <PCore/pstring.h>


enum PResourceTypeEnum
{
    P_RESOURCE_TEXTURE,
    P_RESOURCE_SHADER,
    P_RESOURCE_MESH,
    P_RESOURCE_FRAMEBUFFER,
    P_RESOURCE_USER,

    P_RESOURCE_TYPE_FIRST = P_RESOURCE_TEXTURE,
    P_RESOURCE_TYPE_LAST = P_RESOURCE_USER,
    P_RESOURCE_TYPE_NUMBER = P_RESOURCE_TYPE_LAST - P_RESOURCE_TYPE_FIRST + 1,
};

enum PResourceFlagEnum
{
    P_RESOURCE_DEFAULT,
    P_RESOURCE_MANAGED,
    P_RESOURCE_SEMIMANAGED,
    P_RESOURCE_SYSTEM,

    P_RESOURCE_FLAG_FIRST = P_RESOURCE_DEFAULT,
    P_RESOURCE_FLAG_LAST = P_RESOURCE_SYSTEM,
    P_RESOURCE_FLAG_NUMBER = P_RESOURCE_FLAG_LAST - P_RESOURCE_FLAG_FIRST + 1,
};

enum PResourceStateEnum
{
    P_RESOURCE_INMEMORY,
    P_RESOURCE_INSTORAGE,
};


class PResourceManager;


class P_DLLEXPORT PResourceObject
{
    friend class PResourceManager;


private:
    PResourceObject(const PResourceObject& other) {};
    void operator=(const PResourceObject& other) {};

public:
    PResourceObject(const pChar* name, PResourceManager* resourceManager, 
        PResourceFlagEnum flag = P_RESOURCE_DEFAULT,
        PResourceTypeEnum type = P_RESOURCE_USER);
    virtual ~PResourceObject();

    P_INLINE pUint32 getRefereceCount() const    { return m_ref;   }
    P_INLINE PResourceTypeEnum getType() const   { return m_type;  }
    P_INLINE const PString& getName() const      { return m_name;  }
    P_INLINE PResourceFlagEnum getFlag() const   { return m_flag;  }
    P_INLINE PResourceStateEnum getState() const { return m_state; }
    P_INLINE bool isAvailable() const { return m_state == P_RESOURCE_INMEMORY; }

    void retain();
    void release();
    
    void discard();
    void restore();
    
protected:
    virtual void discardResource() = 0;
    virtual void restoreResource() = 0;

protected:
    pUint32            m_ref;
    PString            m_name;
    PResourceTypeEnum  m_type;
    PResourceFlagEnum  m_flag;
    PResourceManager*  m_resourceManager;
    pUint32            m_lastReferred;   // The timestamp of last reference.
    PResourceStateEnum m_state;
};


#endif // !PRESOURCEOBJECT_H
