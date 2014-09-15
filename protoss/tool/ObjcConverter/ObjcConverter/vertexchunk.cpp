#include "vertexchunk.h"
#include <assert.h>

VertexChunk::VertexChunk()
{
}

VertexChunk::~VertexChunk()
{
}

int VertexChunk::write()
{
    assert(m_data);
    
    Writer *writer = Writer::shardedWriter();
    writer->writeInt(MESH_VERTEX_CHUNK_ID);

    m_size = 8 + m_data->vertexCount * 3 * sizeof(float);
    writer->writeInt(m_size);
    
    if (m_data)
    {
        // vertex
        for (int i = 0; i < m_data->vertexCount * 3; i++)
        {
            writer->writeFloat(m_data->vertexs[i]);
        }
    }
    
    return m_size; 
}

void VertexChunk::setData(ModelData *data)
{
    this->m_data = data;
}

