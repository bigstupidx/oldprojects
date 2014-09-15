// pstreammemory.cpp
// Read/write to memory buffer as stream.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 

#include "pstreamobject_private.h"

#include <PSystem/pmemory.h>
#include <PSystem/pdebug.h>

PStreamMemory::PStreamMemory(pUint8* buffer, pUint32 bufferSize)
{
    m_position = 0;
    m_buffer = buffer;
    m_bufferSize = bufferSize;
}

PStreamMemory::~PStreamMemory()
{
}

bool PStreamMemory::read(pUint32 nbytes, pUint32& bytesRead, pUint8* buffer)
{
    bytesRead = pMin(nbytes, m_bufferSize - m_position);
    pmemcpy(buffer, m_buffer + m_position, bytesRead);
    m_position += bytesRead;
    return true;
}

bool PStreamMemory::readLine(pUint32 length, pUint8* buffer)
{
    pInt32 l = pMin((pInt32)length - 1, (pInt32)m_bufferSize - (pInt32)m_position);
    if (l <= 0)
    {
        return false;
    }

    pInt32 i;
    for (i = 0; i < l; i++)
    {
        buffer[i] = m_buffer[m_position + i];

        if (buffer[i] == '\n')
        {
            break;
        }
    }
    buffer[i + 1] = 0;
    m_position += i;
    // When we meet the '\n', we need to move the position one byte more.
    if (i != l)
    {
        m_position += 1;
    }
    return true;
}

bool PStreamMemory::write(pUint32 nbytes, pUint32& bytesWritten, const pUint8* buffer)
{
    bytesWritten = pMin(nbytes, m_bufferSize - m_position);
    pmemcpy(m_buffer + m_position, buffer, m_bufferSize);
    m_position += bytesWritten;
    return true;
}

void PStreamMemory::seek(pUint32 position)
{
    m_position = pMin(position, m_bufferSize);
}

void PStreamMemory::open()
{
}

void PStreamMemory::close()
{
}

void PStreamMemory::skip(pUint32 bytes)
{
    pUint32 bytesSkipped = pMin(bytes, m_bufferSize - m_position);
    m_position += bytesSkipped;
}

bool PStreamMemory::isEndOfStream()
{
    return m_bufferSize == m_position; 
}

pInt32 PStreamMemory::getPosition()
{
    return pInt32(m_position);
}

void PStreamMemory::flush()
{

}
