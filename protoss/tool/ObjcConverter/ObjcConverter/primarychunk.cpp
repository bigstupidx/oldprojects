#include "primarychunk.h"
#include "objectchunk.h"

PrimaryChunk::PrimaryChunk()
{
	m_id = PRIMARY_CHUNK_ID;
}

PrimaryChunk::~PrimaryChunk()
{
}

int PrimaryChunk::write()
{
    Writer *writer = Writer::shardedWriter();
    writer->writeInt(PRIMARY_CHUNK_ID);
    int sizePos = writer->getPosition();
    writer->writeInt(0); // dummy size
    m_size = 8;
    int curPos = writer->getPosition();
    
    if (m_data)
    {
        ObjectChunk *objChunk = new ObjectChunk();
        objChunk->setData(m_data);
        m_size += objChunk->write();
        delete objChunk;
        
        curPos = writer->getPosition();
    }

    writer->seek(sizePos);
    writer->writeInt(m_size);

    writer->seek(curPos);
    
    return m_size;
}

void PrimaryChunk::setData(ModelData *data)
{
    this->m_data = data;
}
