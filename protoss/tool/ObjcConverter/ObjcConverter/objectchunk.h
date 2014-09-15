#ifndef __OBJECT_CHUNK_H__
#define __OBJECT_CHUNK_H__

#include "modeldata.h"
#include "chunk.h"

class ObjectChunk : public Chunk
{
public:
    ObjectChunk();
    ~ObjectChunk();

    virtual int write();

    void setData(ModelData *data);
    
private:
    ModelData *m_data;
};

#endif // __MESH_CHUNK_H__