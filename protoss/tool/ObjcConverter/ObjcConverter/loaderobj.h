#ifndef __LOADER_OBJ_H__
#define __LOADER_OBJ_H__

#include "modeldata.h"


#define MaxVertex   1000


class LoaderObj
{
public:
    LoaderObj();
    ~LoaderObj();

    bool loadFile(const char *filePath);
    void dispose();
    void cloneData(ModelData &data);
    
private:
    bool readToBuffer(const char *filePath);
    bool readLine(unsigned int length, unsigned char* buffer);
    void decoder();

    // file buffer
    unsigned char   *m_pBuffer;
    int             m_nBufferSize;
    int             m_nPosition;
    
    // vertexs
    int             m_nVertexCount;
    float           *m_pVertexs;                // 3 * m_nVertexCount, vector3(x, y, z)
    
    // texture coordinate
    int             m_nTextureCoordinateCount;
    float           *m_pTextureCoordinates;     // 2 * m_nTextureCoordinateCount, vector2(x, y)
    
    // normal
    int             m_nNormalCount;
    float           *m_pNormals;                // 3 * m_nNormalCount, vector3(x, y, z)
    
    // face
    int             m_nFaceCount;
    int             *m_pFaces;                  // 9 * m_nFaceCount, vector3[3], vertex, texture coordinate, normal index
};

#endif // __LOADER_OBJ_H__
