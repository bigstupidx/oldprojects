#include "objectchunk.h"
#include "meshchunk.h"

ObjectChunk::ObjectChunk()
: m_data(NULL)
{
	m_id = PRIMARY_CHUNK_ID;
}

ObjectChunk::~ObjectChunk()
{
}

int ObjectChunk::write()
{
    Writer *writer = Writer::shardedWriter();
    writer->writeInt(OBJECT_CHUNK_ID);
    int sizePos = writer->getPosition();
    writer->writeInt(0); // dummy size
    m_size = 8;
    int curPos = writer->getPosition();
    
    if (m_data)
    {
        MeshChunk *meshChunk = new MeshChunk();
        meshChunk->setData(m_data);
        m_size += meshChunk->write();
        delete meshChunk;
        
        curPos = writer->getPosition();
    }

    writer->seek(sizePos);
    writer->writeInt(m_size);

    writer->seek(curPos);
    
    return m_size; 
}

void ObjectChunk::setData(ModelData *data)
{
    this->m_data = data;
}
