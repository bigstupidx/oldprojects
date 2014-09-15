#ifndef __FACE_CHUNK_H__
#define __FACE_CHUNK_H__

#include "modeldata.h"
#include "chunk.h"

class FaceChunk : public Chunk
{
public:
    FaceChunk();
    ~FaceChunk();
	
	virtual int write();

	void setData(ModelData *data);
	
private:
	ModelData *m_data;
};

#endif // __FACE_CHUNK_H__
