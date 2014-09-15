#include "meshmtlchunk.h"
#include <assert.h>

MeshMtlChunk::MeshMtlChunk()
{
}

MeshMtlChunk::~MeshMtlChunk()
{
}

int MeshMtlChunk::write()
{
    assert(m_data);
    
    Writer *writer = Writer::shardedWriter();
    writer->writeInt(MESH_MTL_CHUNK_ID);

    m_size = 8 + m_data->vertexCount * 3 * sizeof(float);
    writer->writeInt(m_size);
    
    if (m_data)
    {
        // mesh mtl name
        for (int i = 0; i < m_data->vertexCount * 3; i++)
        {
            writer->writeFloat(m_data->vertexs[i]);
        }
    }
    
    return m_size; 
}

void MeshMtlChunk::setData(ModelData *data)
{
    this->m_data = data;
}

