// p_stream_file.cpp
// Read/write to file as a stream.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 

#include "pstreamobject_private.h"


#include <PSystem/pmemory.h>
#include <PSystem/pdebug.h>
#include <PSystem/pcrt.h>


PStreamFile::PStreamFile(const pChar* filePath, bool writable)
    : m_filePath(filePath)
{
    m_file = P_NULL;
    m_writable = writable;
}

PStreamFile::~PStreamFile()
{
    if (m_file != P_NULL)
    {
        close();
    }
}

bool PStreamFile::read(pUint32 nbytes, pUint32& bytesRead, pUint8* buffer)
{
    if (m_file == P_NULL)
    {
        pLogError("Unable to open file for reading");
        return false;
    }

    bytesRead = pfread(buffer, sizeof(pUint8), nbytes, m_file);
    return true;
}

bool PStreamFile::readLine(pUint32 length, pUint8* buffer)
{
    if (m_file == P_NULL)
    {
        pLogError("Unable to open file for reading");
        return false;
    }

    pChar* p = pfgets((pChar*)buffer, length, m_file);

    return true;
}

bool PStreamFile::write(pUint32 nbytes, pUint32& bytesWritten, const pUint8* buffer)
{
    if (m_file == P_NULL)
    {
        return false;
    }

    pUint32 tempBytesWritten = 0;
    pUint32 bytesRemaining = nbytes;
    const pUint8* p = buffer;

    do
    {
        tempBytesWritten = pfwrite(p, sizeof(pUint8), bytesRemaining, m_file);
        bytesRemaining -= tempBytesWritten;
        p += tempBytesWritten;
    } while (bytesRemaining && tempBytesWritten);

    bytesWritten = nbytes - bytesRemaining;

    return true;
}

void PStreamFile::seek(pUint32 position)
{
    // we don't have seek when writing.
    if (m_writable)
    {
        return ;
    }

    pAssert(m_file != P_NULL);
    if (m_file == P_NULL)
    {
        pLogError("Unable to open file for reading");
        return ;
    }

    pfseek(m_file, position, P_FILE_SEEK_FROM_BEGINNING);
}

void PStreamFile::open()
{
    pAssert(m_file == P_NULL);

    if (m_writable)
    {
        m_file = pfopen(m_filePath.c_str(), P_FILE_WRITEONLY_BINARY);
    }
    else
    {
        m_file = pfopen(m_filePath.c_str(), P_FILE_READONLY_BINARY);
    }
}

void PStreamFile::close()
{
    if (m_file != P_NULL)
    {
        pfclose(m_file);
        m_file = P_NULL;
    }
}

void PStreamFile::skip(pUint32 bytes)
{
    pAssert(m_file != P_NULL);
    if (m_file == P_NULL)
    {
        pLogError("Unable to open file for reading");
        return ;
    }

    pfseek(m_file, bytes, P_FILE_SEEK_FROM_HERE);
}
    
bool PStreamFile::isEndOfStream()
{
    return pfeof(m_file);
}

void PStreamFile::flush()
{
    pfflush(m_file);
}

pInt32 PStreamFile::getPosition()
{
    return pftell(m_file);
}
