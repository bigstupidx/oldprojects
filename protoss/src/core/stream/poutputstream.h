// poutputstream.h
// Write to file/memory/other.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// 
// Hongwei Li lihw81@gmail.com
// 

#ifndef POUTPUTSTREAM_H
#define POUTPUTSTREAM_H

#include <PCore/pabstractstream.h>

#include <PCore/pstring.h>

class PStreamObject;

class P_DLLEXPORT POutputStream : public PAbstractStream
{
public:
    POutputStream();
    virtual ~POutputStream();

    bool createFromFile(const pChar* filePath, PStreamEndianessEnum endianness);
    bool createFromMemory(pUint8* buffer, pUint32 size, PStreamEndianessEnum endianness);

    // How many bytes have been written to the stream so far.
    // \return the number of bytes that have been written.
    pUint32 getWrittenBytes() const;

    bool writeBytes(pUint32 nbytes, const pUint8* buffer);
    bool write(pUint32 nbytes, pUint32& bytesWritten, const pUint8* buffer);
    void flush();

    bool writeUint8(pUint8 value);
    bool writeInt8(pInt8 value);
    bool writeUint16(pUint16 value);
    bool writeInt16(pInt16 value);
    bool writeUint32(pUint32 value);
    bool writeInt32(pInt32 value);
    bool writeFloat32(pFloat32 value);
    bool writeBoolean(bool value);
    bool writeString(const PString& value);
    bool writeString(const pChar* value);

    void skipBytes(pUint32 nbytes);

private:
    // The number of bytes written so far
    pUint32 m_writtenBytes;
};


#endif // !POUTPUTSTREAM_H
