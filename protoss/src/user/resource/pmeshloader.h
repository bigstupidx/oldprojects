// pmeshloader.h
// load objc file, convert to mesh.
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Su Yu suyu@cooee.cn
//
// 
#ifndef PMESHLOADER_H
#define PMESHLOADER_H

#include <PGlobal/pglobal.h>

#include <PSystem/pmemory.h>

class PInputStream;

class P_DLLEXPORT PMeshLoader
{
private:
    struct MeshData
    {
        MeshData()
            : vertexCount(0)
            , vertexBuffer(P_NULL)
            , faceCount(0)
            , faces(P_NULL)
        {
        }

        ~MeshData()
        {      
            vertexCount = 0;            
            if (vertexBuffer)
            {
                pDeleteArray(vertexBuffer);
            }
            
            faceCount = 0;
            if (faces)
            {
                pDeleteArray(faces);
            }
        }
        
        pUint16             vertexCount;
        pFloat32            *vertexBuffer;          // include position, texture coordinate and normal buffers:
                                                    // position:                pFloat32 [vertexCount][3]
                                                    // texture coordinate:  pFloat32 [vertexCount][2]
                                                    // normal:                  pFloat32 [vertexCount][3]
        pUint16             faceCount;
        pUint16             *faces;                 // pUint16 [vertexCount][3]

        pBool isNil()
        {
            return (vertexCount == 0);
        }
    };

public:
    PMeshLoader(const pChar *pathName);
    ~PMeshLoader();

    P_INLINE pUint16 getVertexCount() const;
    P_INLINE pFloat32 *getVertexBuffer() const;
    P_INLINE pUint16 getFaceCount() const;
    P_INLINE pUint16 *getIndexBuffer() const;

private:
    // FIXME: it would be better that separate objc decoder from here.
    void decodeObjc(PInputStream *stream);
    void readChunk(PInputStream *stream);

private:
    MeshData        *m_data;
};


#endif // PMESHLOADER_H
