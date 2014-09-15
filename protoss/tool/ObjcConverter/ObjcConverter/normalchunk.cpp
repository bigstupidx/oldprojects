#include "normalchunk.h"
#include <assert.h>

NormalChunk::NormalChunk()
{
}

NormalChunk::~NormalChunk()
{
}

int NormalChunk::write()
{
    assert(m_data);
    
    Writer *writer = Writer::shardedWriter();
    writer->writeInt(MESH_NORMAL_CHUNK_ID);

    m_size = 8 + m_data->normalCount * 3 * sizeof(float);
    writer->writeInt(m_size);
    
    if (m_data)
    {
        // normal
        for (int i = 0; i < m_data->normalCount * 3; i++)
        {
            writer->writeFloat(m_data->normals[i]);
        }
    }
    
    return m_size; 
}

void NormalChunk::setData(ModelData *data)
{
    this->m_data = data;
}

