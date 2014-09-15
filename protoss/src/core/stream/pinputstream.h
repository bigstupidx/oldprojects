// pinputstream.h
// Read file/memory/other streams.
// 
// Copyright 2013 Cooee. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 

#ifndef PINPUTSTREAM_H
#define PINPUTSTREAM_H

#include <PCore/pabstractstream.h>
#include <PCore/pstring.h>
 
class P_DLLEXPORT PInputStream : public PAbstractStream
{
public:
    PInputStream();
    virtual ~PInputStream();

    bool createFromFile(const pChar* filePath, PStreamEndianessEnum endianness);
    bool createFromMemory(pUint8* buffer, pUint32 size, PStreamEndianessEnum endianness);

    bool isEndOfStream() const;

    bool readBytes(pUint32 nbytes, pUint8* buffer);
    bool read(pUint32 nbytes, pUint32& bytesRead, pUint8* buffer);

    bool readUint8(pUint8* value);
    bool readInt8(pInt8* value);
    bool readUint16(pUint16* value);
    bool readInt16(pInt16* value);
    bool readUint32(pUint32* value);
    bool readInt32(pInt32* value);
    bool readFloat32(pFloat32* value);
    bool readBoolean(bool* value);
    bool readString(PString& value);
    bool readString(pUint32 length, pChar* value);

    // return the number of bytes read or -1 when fails.
    pInt32 readAllBytes(pUint8*& buffer);
    bool readLine(pUint32 length, pChar* buffer);

    void skipBytes(pUint32 nbytes);

    pInt32 getReadBytes();
    void seek(pUint32 position);
};


#endif // !PINPUTSTREAM_H
