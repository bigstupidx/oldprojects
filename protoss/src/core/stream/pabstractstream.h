// pabstractstream.h
// The interface of stream.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 

#ifndef PABSTRACTSTREAM_H
#define PABSTRACTSTREAM_H

#include <PGlobal/pglobal.h>


enum PStreamEndianessEnum 
{
    P_STREAM_ENDIANNESS_UNKNOWN,
    P_STREAM_ENDIANNESS_BIG,
    P_STREAM_ENDIANNESS_LITTLE,
    P_STREAM_ENDIANNESS_PLATFORM,
};


class PStreamObject;


class P_DLLEXPORT PAbstractStream
{
public:
    PAbstractStream();
    virtual ~PAbstractStream();

    void setEndianness(PStreamEndianessEnum endianness);
    P_INLINE PStreamEndianessEnum getEndianness() const
    { return m_endianness; }

protected:
    PStreamEndianessEnum m_endianness;
    PStreamObject* m_object;
};


#endif // !PABSTRACTSTREAM_H
