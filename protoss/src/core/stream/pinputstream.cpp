// pinputstream.cpp
// Read file/memory/other streams.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 

#include "pinputstream.h"

#include <PSystem/pmemory.h>
#include <PSystem/pdebug.h>

#include "pstreamobject_private.h"


PInputStream::PInputStream()
    : PAbstractStream()
{
}

PInputStream::~PInputStream()
{
}

bool PInputStream::createFromFile(const pChar* filePath, 
    PStreamEndianessEnum endianness)
{
    pAssert(m_object == P_NULL);
    if (m_object != P_NULL)
    {
        pLogError("Unable to reopen the stream for reading");
        return false;
    }

    m_object = pNew(PStreamFile(filePath, false));

    m_object->open();

    m_endianness = endianness;

    return true;
}

bool PInputStream::createFromMemory(pUint8* buffer, pUint32 size, 
    PStreamEndianessEnum endianness)
{
    pAssert(m_object == P_NULL);
    if (m_object != P_NULL)
    {
        pLogError("Unable to reopen the stream for reading");
        return false;
    }

    m_object = pNew(PStreamMemory(buffer, size));

    m_object->open();

    m_endianness = endianness;

    return true;
}

bool PInputStream::isEndOfStream() const
{
    return m_object->isEndOfStream();
}

bool PInputStream::readBytes(pUint32 nbytes, pUint8* buffer)
{
    if (m_object == P_NULL)
    {
        pLogError("Intput stream is unavailable");
        return false;
    }

    pUint32 bytesRead;
    if (!m_object->read(nbytes, bytesRead, buffer))
    {
        return false;
    }

    if (nbytes != bytesRead)
    {
        pLogError("The number of bytes read is not as expected.");
        return false;
    }

    return true;
}

bool PInputStream::read(pUint32 nbytes, pUint32& bytesRead, pUint8* buffer)
{
    if (m_object == P_NULL)
    {
        pLogError("Intput stream is unavailable");
        return false;
    }

    return m_object->read(nbytes, bytesRead, buffer);
}

bool PInputStream::readUint8(pUint8* value)
{
    pUint8 buffer[1];
    if (!readBytes(1, buffer))
    {
        return false;
    }
    
    *value = buffer[0];

    return true;
}

bool PInputStream::readInt8(pInt8* value)
{
    pUint8 buffer[1];
    if (!readBytes(1, buffer))
    {
        return false;
    }
    
    *value = (pInt8)buffer[0];

    return true;
}

bool PInputStream::readUint16(pUint16* value)
{
    pUint8 buffer[2];
    if (!readBytes(2, buffer))
    {
        return false;
    }
    
    switch (m_endianness)
    {
        case P_STREAM_ENDIANNESS_BIG:
            *value = ((pUint16)(buffer[1]) | ((pUint16)(buffer[0]) << 8));
            break;
        case P_STREAM_ENDIANNESS_LITTLE:
            *value = ((pUint16)(buffer[0]) | ((pUint16)(buffer[1]) << 8));
            break;
        case P_STREAM_ENDIANNESS_PLATFORM:
            *value = *(pUint16*)buffer;
            break;
        default:
            pLogError("Invalid endianness");
            return false;
    }

    return true;
}

bool PInputStream::readInt16(pInt16* value)
{
    pUint16 v;
    if (!readUint16(&v))
    {
        return false;
    }

    *value = (pInt16)v;
    return true;
}

bool PInputStream::readUint32(pUint32* value)
{
    pUint8 buffer[4];
    if (!readBytes(4, buffer))
    {
        return false;
    }
    
    switch (m_endianness)
    {
        case P_STREAM_ENDIANNESS_BIG:
            *value = ((pUint32)(buffer[3]) | 
                     ((pUint32)(buffer[2]) << 8) |
                     ((pUint32)(buffer[1]) << 16) |
                     ((pUint32)(buffer[0]) << 24));
            break;
        case P_STREAM_ENDIANNESS_LITTLE:
            *value = ((pUint32)(buffer[0]) | 
                     ((pUint32)(buffer[1]) << 8) |
                     ((pUint32)(buffer[2]) << 16) |
                     ((pUint32)(buffer[3]) << 24));
            break;
        case P_STREAM_ENDIANNESS_PLATFORM:
            *value = *(pUint32*)buffer;
            break;
        default:
            pLogError("Invalid endianness");
            return false;
    }

    return true;
}

bool PInputStream::readInt32(pInt32* value)
{
    pUint32 v;
    if (!readUint32(&v))
    {
        return false;
    }

    *value = (pInt32)v;
    return true;
}

bool PInputStream::readFloat32(pFloat32* value)
{
    pUint8 buffer[4];
    if (!readBytes(4, buffer))
    {
        return false;
    }
    
    pUint32 v;
    switch (m_endianness)
    {
        case P_STREAM_ENDIANNESS_BIG:
            v= ((pUint32)(buffer[3]) | 
               ((pUint32)(buffer[2]) << 8) |
               ((pUint32)(buffer[1]) << 16) |
               ((pUint32)(buffer[0]) << 24));
            break;
        case P_STREAM_ENDIANNESS_LITTLE:
            v= ((pUint32)(buffer[0]) | 
               ((pUint32)(buffer[1]) << 8) |
               ((pUint32)(buffer[2]) << 16) |
               ((pUint32)(buffer[3]) << 24));
            break;
        case P_STREAM_ENDIANNESS_PLATFORM:
            v= *(pUint32*)buffer;
            break;
        default:
            pLogError("Invalid endianness");
            return false;
    }

    *value = *(pFloat32*)&v;
    return true;
}

bool PInputStream::readBoolean(bool* value)
{
    pUint8 buffer[1];
    if (!readBytes(1, buffer))
    {
        return false;
    }
    
    *value = (buffer[0] != 0);
    return true;
}

bool PInputStream::readString(pUint32 length, pChar* buffer)
{
    if (readBytes(length, (pUint8*)buffer))
    {
        buffer[length + 1] = 0;
        return true;
    }

    return false;
}

bool PInputStream::readString(PString& string)
{
    pChar buffer[1024];
    pUint32 index = 0;

    string = PString();

    pChar c;
    while (readInt8(&c))
    {
        if (c != 0)
        {
            buffer[index++] = c;
        }
        else
        {
            break;
        }

        if (index >= 1023)
        {
            index = 0;
            buffer[1023] = 0;
            string += PString(buffer);
        }
    }
            
    buffer[index] = 0;
    string += PString(buffer);

    return true;
}

pInt32 PInputStream::readAllBytes(pUint8*& buffer)
{
    pUint32 bufferSize = 512;
    pUint32 usedBufferSize = 0;
    pInt32 bytesRead = 0;

    buffer = pNewArray(pUint8[bufferSize]);

    while (!isEndOfStream())
    {
        if (usedBufferSize == bufferSize)
        {
            pUint32 oldBufferSize = bufferSize;
            // Increase the buffer size 100%
            if (bufferSize < 4096)
            {
                bufferSize *= 2;
            }
            else
            {
                bufferSize += 4096;
            }

            pUint8* tempBuffer = pNewArray(pUint8[bufferSize]);
            
            pmemcpy(tempBuffer, buffer, oldBufferSize);
            pDeleteArray(buffer);
            buffer = tempBuffer;
        }

        pUint32 bytesReadThisTime;
        if (!read(bufferSize - usedBufferSize, bytesReadThisTime, buffer + usedBufferSize))
        {
            pDeleteArray(buffer);
            return -1;
        }

        usedBufferSize += bytesReadThisTime;
        bytesRead += bytesReadThisTime;
    }

    return bytesRead;
}

bool PInputStream::readLine(pUint32 length, pChar* buffer)
{
    if (m_object == P_NULL)
    {
        pLogError("Intput stream is unavailable");
        return false;
    }

    if (!m_object->readLine(length, (pUint8*)buffer))
    {
        return false;
    }

    return true;
}

void PInputStream::skipBytes(pUint32 nbytes)
{
    if (m_object == P_NULL)
    {
        pLogError("Intput stream is unavailable");
    }
    else
    {
        m_object->skip(nbytes);
    }
}

pInt32 PInputStream::getReadBytes()
{
    if (m_object == P_NULL)
    {
        pLogError("Intput stream is unavailable");
        return -1;
    }

    pInt32 nbytes = m_object->getPosition();
    if (nbytes < 0)
    {
        pLogError("Can't obtain the number of read bytes");
    }
    return nbytes;
}

void PInputStream::seek(pUint32 position)
{
    if (m_object == P_NULL)
    {
        pLogError("Intput stream is unavailable");
    }
    else
    {
        m_object->seek(position);
    }
}

