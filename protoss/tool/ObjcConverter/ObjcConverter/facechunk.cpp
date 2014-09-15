#include "facechunk.h"
#include <assert.h>

FaceChunk::FaceChunk()
{
}

FaceChunk::~FaceChunk()
{
}

int FaceChunk::write()
{
    assert(m_data);
    
    Writer *writer = Writer::shardedWriter();
    writer->writeInt(MESH_FACE_CHUNK_ID);

    m_size = 8 + m_data->faceCount * 9 * sizeof(int);
    writer->writeInt(m_size);
    
    if (m_data)
    {
        // face
        for (int i = 0; i < m_data->faceCount * 9; i++)
        {
            writer->writeInt(m_data->faces[i]);
        }
    }
    
    return m_size; 
}

void FaceChunk::setData(ModelData *data)
{
    this->m_data = data;
}

