// poutputstream.cpp
// Write to file/memory/other.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 
// 

#include "poutputstream.h"

#include <PSystem/pmemory.h>
#include <PSystem/pdebug.h>

#include "pstreamobject_private.h"

POutputStream::POutputStream()
    : PAbstractStream()
{
    m_writtenBytes = 0;
}

POutputStream::~POutputStream()
{
}

bool POutputStream::createFromFile(const pChar *filePath, PStreamEndianessEnum endianness)
{
    pAssert(m_object == P_NULL);
    if (m_object != P_NULL)
    {
        pLogError("Unable to reopen the stream for writing");
        return false;
    }

    m_object = pNew(PStreamFile(filePath, true));

    m_object->open();

    m_endianness = endianness;

    return true;
}

bool POutputStream::createFromMemory(pUint8 *buffer, pUint32 size, PStreamEndianessEnum endianness)
{
    pAssert(m_object == P_NULL);
    if (m_object != P_NULL)
    {
        pLogError("Unable to reopen the stream for writing");
        return false;
    }

    m_object = pNew(PStreamMemory(buffer, size));

    m_object->open();

    m_endianness = endianness;

    return true;
}

bool POutputStream::writeBytes(pUint32 nbytes, const pUint8* buffer)
{
    pAssert(m_object != P_NULL);
    if (m_object == P_NULL)
    {
        pLogError("Output stream is unavailable");
        return false;
    }
    pUint32 bytesWritten;
    if (!m_object->write(nbytes, bytesWritten, buffer))
    {
        return false;
    }
    if (bytesWritten != nbytes)
    {
        pLogWarning("The written data is less than expected");
        m_writtenBytes = bytesWritten;
        return false;
    }

    m_writtenBytes += bytesWritten;
    return true;
}

bool POutputStream::write(pUint32 nbytes, pUint32& bytesWritten, const pUint8* buffer)
{
    return m_object->write(nbytes, bytesWritten, buffer);
}

bool POutputStream::writeUint8(pUint8 value)
{
    return writeBytes(1, &value);
}

bool POutputStream::writeInt8(pInt8 value)
{
    pUint8 buffer[1] = {value};
    return writeBytes(1, buffer);
}

bool POutputStream::writeUint16(pUint16 value)
{
    pUint8 buffer[2];
    switch (m_endianness)
    {
        case P_STREAM_ENDIANNESS_BIG:
            buffer[0] = (pUint8)(value);
            buffer[1] = (pUint8)(value >> 8);
            break;
        case P_STREAM_ENDIANNESS_LITTLE:
            buffer[0] = (pUint8)(value >> 8);
            buffer[1] = (pUint8)(value);
            break;
        case P_STREAM_ENDIANNESS_PLATFORM:
            {
                pUint8* valueBuffer = (pUint8*)&value;
                buffer[0] = valueBuffer[0];
                buffer[1] = valueBuffer[1];
            }
            break;
        default:
            pLogError("Invalid endianness");
            return false;
    }
    
    if (!writeBytes(2, buffer))
    {
        return false;
    }

    return true;
}

bool POutputStream::writeInt16(pInt16 value)
{
    pUint16 v = (pUint16)value;
    if (!writeUint16(v))
    {
        return false;
    }

    return true;
}

bool POutputStream::writeUint32(pUint32 value)
{
    pUint8 buffer[4];
    
    switch (m_endianness)
    {
        case P_STREAM_ENDIANNESS_BIG:
            buffer[0] = (pUint8)(value >> 24);
            buffer[1] = (pUint8)(value >> 16);
            buffer[2] = (pUint8)(value >> 8);
            buffer[3] = (pUint8)value;
            break;
        case P_STREAM_ENDIANNESS_LITTLE:
            buffer[0] = (pUint8)value;
            buffer[1] = (pUint8)(value >> 8);
            buffer[2] = (pUint8)(value >> 16);
            buffer[3] = (pUint8)(value >> 24);
            break;
        case P_STREAM_ENDIANNESS_PLATFORM:
            {
                pUint8* valueBuffer = (pUint8*)&value;
                buffer[0] = valueBuffer[0];
                buffer[1] = valueBuffer[1];
                buffer[2] = valueBuffer[2];
                buffer[3] = valueBuffer[3];
            }
            break;
        default:
            pLogError("Invalid endianness");
            return false;
    }
    
    if (!writeBytes(4, buffer))
    {
        return false;
    }

    return true;
}

bool POutputStream::writeInt32(pInt32 value)
{
    pUint32 v;
    v = (pUint32)value;
    if (!writeUint32(v))
    {
        return false;
    }

    return true;
}

bool POutputStream::writeFloat32(pFloat32 value)
{
    pUint32 v = *(pUint32*)&value;
    return writeUint32(v);
}

bool POutputStream::writeBoolean(bool value)
{
    pUint8 buffer[1];

    if (value)
    {
        buffer[0] = 1;
    }
    else
    {
        buffer[0] = 0;
    }
    return writeBytes(1, buffer);
}

bool POutputStream::writeString(const PString& value)
{
    return writeBytes(value.length(), (const pUint8*)value.c_str()) &&
           writeUint8(0);
}

bool POutputStream::writeString(const pChar* value)
{
    const pChar* p = value;
    do
    {
        if (!writeInt8(*p))
        {
            return false;
        }

        p++;
    } while (*p != 0);

    return true;
}

void POutputStream::flush()
{
    pAssert(m_object != P_NULL);
    if (m_object == P_NULL)
    {
        pLogError("Output stream is unavailable");
        return ;
    }

    m_object->flush();
}

void POutputStream::skipBytes(pUint32 nbytes)
{
    pAssert(m_object != P_NULL);
    if (m_object == P_NULL)
    {
        pLogError("Output stream is unavailable");
        return ;
    }

    m_object->skip(nbytes);

    m_writtenBytes += nbytes;
}

