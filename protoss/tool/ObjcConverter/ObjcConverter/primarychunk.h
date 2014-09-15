#ifndef __PRIMARY_CHUNK_H__
#define __PRIMARY_CHUNK_H__

#include "modeldata.h"
#include "chunk.h"

class PrimaryChunk : public Chunk
{
public:
    PrimaryChunk();
    ~PrimaryChunk();

    virtual int write();

    void setData(ModelData *data);
    
private:
    ModelData *m_data;
};

#endif // __MESH_CHUNK_H__