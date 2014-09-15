#ifndef __NORMAL_CHUNK_H__
#define __NORMAL_CHUNK_H__

#include "modeldata.h"
#include "chunk.h"

class NormalChunk : public Chunk
{
public:
    NormalChunk();
    ~NormalChunk();
	
	virtual int write();

	void setData(ModelData *data);
	
private:
	ModelData *m_data;
};

#endif // __NORMAL_CHUNK_H__
