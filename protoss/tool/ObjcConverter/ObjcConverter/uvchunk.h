#ifndef __UV_CHUNK_H__
#define __UV_CHUNK_H__

#include "modeldata.h"
#include "chunk.h"

class UvChunk : public Chunk
{
public:
    UvChunk();
    ~UvChunk();
	
	virtual int write();

	void setData(ModelData *data);
	
private:
	ModelData *m_data;
};

#endif // __UV_CHUNK_H__
