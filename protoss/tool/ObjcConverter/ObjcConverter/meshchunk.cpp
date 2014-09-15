#include "meshchunk.h"
#include "vertexchunk.h"
#include "facechunk.h"
#include "uvchunk.h"
#include "normalchunk.h"

MeshChunk::MeshChunk()
{
}

MeshChunk::~MeshChunk()
{
}

int MeshChunk::write()
{
    Writer *writer = Writer::shardedWriter();
    writer->writeInt(MESH_CHUNK_ID);
    int sizePos = writer->getPosition();
    writer->writeInt(0); // dummy size
    m_size = 8;
    int curPos = writer->getPosition();
    
    if (m_data)
    {
        // vertex
        VertexChunk *vertexChunk = new VertexChunk();
        vertexChunk->setData(m_data);
        m_size += vertexChunk->write();
        delete vertexChunk;

        // face
        FaceChunk *faceChunk = new FaceChunk();
        faceChunk->setData(m_data);
        m_size += faceChunk->write();
        delete faceChunk;

        // uv
        UvChunk *uvChunk = new UvChunk();
        uvChunk->setData(m_data);
        m_size += uvChunk->write();
        delete uvChunk;

        // normal
        NormalChunk *normalChunk = new NormalChunk();
        normalChunk->setData(m_data);
        m_size += normalChunk->write();
        delete normalChunk;

        curPos = writer->getPosition();
    }

    writer->seek(sizePos);
    writer->writeInt(m_size);

    writer->seek(curPos);
    
    return m_size; 
}

void MeshChunk::setData(ModelData *data)
{
    this->m_data = data;
}

