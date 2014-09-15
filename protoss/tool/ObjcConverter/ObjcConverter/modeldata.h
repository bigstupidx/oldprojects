#ifndef __MODEL_DATA_H__
#define __MODEL_DATA_H__

#include "macro.h"

typedef struct ModelData
{
    // vertexs
    int             vertexCount;
    float           *vertexs;                // 3 * m_nVertexCount, vector3(x, y, z)

    // texture coordinate
    int             textureCoordinateCount;
    float           *textureCoordinates;     // 2 * m_nTextureCoordinateCount, vector2(x, y)

    // normal
    int             normalCount;
    float           *normals;                // 3 * m_nNormalCount, vector3(x, y, z)

    // face
    int             faceCount;
    int             *faces;                  // 9 * m_nFaceCount, vector3[3], vertex, texture coordinate, normal index

	// mtl
	char			mtlName[80];
	
    void dispose()
    {
        deleteArray(vertexs);
        vertexCount = 0;
        
        deleteArray(textureCoordinates);
        textureCoordinateCount = 0;
        
        deleteArray(normals);
        normalCount = 0;
        
        deleteArray(faces);
        faceCount = 0;
    }
} ModelData;

#endif // __MODEL_DATA_H__
