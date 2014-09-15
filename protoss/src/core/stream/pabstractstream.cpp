// pabstractstream.cpp
// The interface of stream.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 

#include "pabstractstream.h"

#include "pstreamobject_private.h"
    
PAbstractStream::PAbstractStream()
{
    m_object = P_NULL;
}

PAbstractStream::~PAbstractStream()
{
    if (m_object != P_NULL)
    {
        pDelete(m_object);
    }
}

void PAbstractStream::setEndianness(PStreamEndianessEnum endianness)
{
    if (endianness != P_STREAM_ENDIANNESS_UNKNOWN)
    {
        m_endianness = endianness;
    }
    else
    {
        pLogDebug("the current endianness is specified");
    }
}
