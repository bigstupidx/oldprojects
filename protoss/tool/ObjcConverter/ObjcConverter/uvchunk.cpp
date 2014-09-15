#include "uvchunk.h"
#include <assert.h>

UvChunk::UvChunk()
{
}

UvChunk::~UvChunk()
{
}

int UvChunk::write()
{
    assert(m_data);
    
    Writer *writer = Writer::shardedWriter();
    writer->writeInt(MESH_UV_CHUNK_ID);

    m_size = 8 + m_data->textureCoordinateCount * 2 * sizeof(float);
    writer->writeInt(m_size);
    
    if (m_data)
    {
        // uv
        for (int i = 0; i < m_data->textureCoordinateCount * 2; i++)
        {
            writer->writeFloat(m_data->textureCoordinates[i]);
        }
    }
    
    return m_size; 
}

void UvChunk::setData(ModelData *data)
{
    this->m_data = data;
}

