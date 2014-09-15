#ifndef __VERTEX_CHUNK_H__
#define __VERTEX_CHUNK_H__

#include "modeldata.h"
#include "chunk.h"

class VertexChunk : public Chunk
{
public:
    VertexChunk();
    ~VertexChunk();
	
	virtual int write();

	void setData(ModelData *data);
	
private:
	ModelData *m_data;
};

#endif // __VERTEX_CHUNK_H__
