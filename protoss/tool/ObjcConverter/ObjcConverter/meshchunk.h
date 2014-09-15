#ifndef __MESH_CHUNK_H__
#define __MESH_CHUNK_H__

#include "modeldata.h"
#include "chunk.h"

class MeshChunk : public Chunk
{
public:
    MeshChunk();
    ~MeshChunk();
	
	virtual int write();

	void setData(ModelData *data);
	
private:
	ModelData *m_data;
};

#endif // __MESH_CHUNK_H__
