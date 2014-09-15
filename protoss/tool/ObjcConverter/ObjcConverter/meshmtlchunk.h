#ifndef __MESH_MTL_CHUNK_H__
#define __MESH_MTL_CHUNK_H__

#include "modeldata.h"
#include "chunk.h"

class MeshMtlChunk : public Chunk
{
public:
    MeshMtlChunk();
    ~MeshMtlChunk();
	
	virtual int write();

	void setData(ModelData *data);
	
private:
	ModelData *m_data;
};

#endif // __MESH_MTL_CHUNK_H__
