#include "encoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "primarychunk.h"

// 20130620
#define HEADER_MASK             0x20061320

Encoder::Encoder()
{
}

Encoder::~Encoder()
{
    this->mData.dispose();
}

void Encoder::setData(ModelData &data)
{
    // FIXME: set data should clone, but here is not.
    this->mData = data;
}

void Encoder::saveFile(const char *filePath)
{
    Writer *writer = Writer::shardedWriter();
    if (!writer->openFile(filePath))
    {
        return;
    }
    
    // magic header
    writer->writeChars("PROT");
    writer->writeInt(HEADER_MASK);

    // primary chunk
    PrimaryChunk *pChunk = new PrimaryChunk();
    pChunk->setData(&mData);
    pChunk->write();

    // magic tailer
    writer->writeChars("TOSS");
    writer->writeInt(HEADER_MASK);
    
    writer->closeFile();
}

