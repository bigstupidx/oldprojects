// pobject.c
// The base class of all protoss objects which needs auto release.
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Su Yu
// suyu@cooee.cn
//

#include "pobject.h"

#include <PSystem/pmemory.h>
#include <PSystem/pdebug.h>

PObject::PObject(void)
: m_reference(1) // when the object is created, the reference count of it is 1
{
}

PObject::~PObject(void)
{
}

void PObject::release(void)
{
    pAssertInfo(m_reference > 0, "reference count should greater than 0");
    // FIXME: make the following line thread-safe
    --m_reference;

    if (m_reference == 0)
    {
        pDeleteThis(this);
    }
}

void PObject::retain(void)
{
    pAssertInfo(m_reference > 0, "reference count should greater than 0");

    // FIXME: make the following line thread-safe
    ++m_reference;
}