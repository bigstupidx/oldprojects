// pstreamobject_private.h
// stream object 
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 

#ifndef PSTREAMOBJECT_PRIVATE_H
#define PSTREAMOBJECT_PRIVATE_H


#include <PCore/pstring.h>

#include <PSystem/pcrt.h>


class PStreamObject
{
public:
    PStreamObject() {};
    virtual ~PStreamObject() {};

    // read to the stream.
    virtual bool read(pUint32 nbytes, pUint32& bytesRead, pUint8* buffer) = 0;

    // read till the new line.
    virtual bool readLine(pUint32 size, pUint8* buffer) = 0;
    
    // write to the stream.
    virtual bool write(pUint32 nbytes, pUint32& bytesWritten, const pUint8* buffer) = 0;

    // reposition the read/write in the stream.
    virtual void seek(pUint32 position) = 0;

    // open the stream.
    virtual void open() = 0;
    
    // close the stream.
    virtual void close() = 0;

    // skip the a stream a few bytes.
    virtual void skip(pUint32 position) = 0;

    // reaches the end of the stream.
    virtual bool isEndOfStream() = 0;

    // Flush cached buffer to output.
    virtual void flush() = 0;
    
    // Return how many bytes that have been read from the beginning.
    virtual pInt32 getPosition() = 0;
};

class PStreamFile : public PStreamObject
{
public:
    PStreamFile(const pChar* filePath, bool writable);
    virtual ~PStreamFile();

    virtual bool read(pUint32 nbytes, pUint32& bytesRead, pUint8* buffer);
    virtual bool readLine(pUint32 size, pUint8* buffer);
    virtual bool write(pUint32 nbytes, pUint32& bytesWritten, const pUint8* buffer);
    virtual void seek(pUint32 position);
    virtual void open();
    virtual void close();
    virtual void skip(pUint32 bytes);
    virtual bool isEndOfStream();
    virtual void flush();
    virtual pInt32 getPosition();

private:
    PString m_filePath;
    PFile* m_file;
    bool m_writable;
};

class PStreamMemory : public PStreamObject
{
public:
    PStreamMemory(pUint8* buffer, pUint32 bufferSize);
    virtual ~PStreamMemory();

    virtual bool read(pUint32 nbytes, pUint32& bytesRead, pUint8* buffer);
    virtual bool readLine(pUint32 length, pUint8* buffer);
    virtual bool write(pUint32 nbytes, pUint32& bytesWritten, const pUint8* buffer);
    virtual void seek(pUint32 position);
    virtual void open();
    virtual void close();
    virtual void skip(pUint32 bytes);
    virtual bool isEndOfStream();
    virtual void flush();
    virtual pInt32 getPosition();

private:
    pUint8* m_buffer;
    pUint32 m_bufferSize;
    pUint32 m_position;
};


#endif // !PSTREAMOBJECT_PRIVATE_H
