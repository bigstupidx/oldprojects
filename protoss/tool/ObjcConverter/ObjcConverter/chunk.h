#ifndef __CHUNK__
#define __CHUNK__

#include "writer.h"

// 'C' 'K' 0 1
#define PRIMARY_CHUNK_ID        0x01004b43

// 'C' 'K' 1 0
#define OBJECT_CHUNK_ID         0x00014b43

// 'C' 'K' 11 0
#define MESH_CHUNK_ID           0x00114b43

// 'C' 'K' 11 10
#define MESH_VERTEX_CHUNK_ID    0x10114b43

// 'C' 'K' 11 11
#define MESH_FACE_CHUNK_ID      0x11114b43

// 'C' 'K' 11 12
#define MESH_UV_CHUNK_ID        0x12114b43

// 'C' 'K' 11 13
#define MESH_MTL_CHUNK_ID       0x13114b43

// 'C' 'K' 11 14
#define MESH_NORMAL_CHUNK_ID    0x14114b43

// 'C' 'K' 20 00
#define MTL_CHUNK_ID            0x00204b43

// 'C' 'K' 21 00
#define MTL_NAME_CHUNK_ID       0x00214b43

// 'C' 'K' 21 01
#define MTL_KA_CHUNK_ID         0x01214b43

// 'C' 'K' 21 02
#define MTL_KD_CHUNK_ID         0x02214b43

// 'C' 'K' 21 03
#define MTL_KS_CHUNK_ID         0x03214b43

class Chunk
{
public:
    Chunk();
    virtual ~Chunk();

    virtual int write();

protected:
    unsigned int m_id;
    unsigned int m_size;
};

#endif // __CHUNK__
