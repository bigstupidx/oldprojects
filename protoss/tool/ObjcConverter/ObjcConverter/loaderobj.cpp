#include "loaderobj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LoaderObj::LoaderObj()
: m_pBuffer(NULL)
, m_nBufferSize(0)
, m_nPosition(0)
{
}

LoaderObj::~LoaderObj()
{
    dispose();
}

bool LoaderObj::readToBuffer(const char *filePath)
{
    FILE *f;
	fopen_s(&f, filePath, "rb");
    if (!f)
    {
        return false;
    }
	fseek(f, 0, SEEK_END);
	m_nBufferSize = ftell(f);
	fseek(f, 0, SEEK_SET);
    m_pBuffer = new unsigned char[m_nBufferSize];
	memset(m_pBuffer, 0, m_nBufferSize);
    if (!m_pBuffer)
    {
        fclose(f);
        return false;
    }
    int bRead = fread(m_pBuffer, 1, m_nBufferSize, f);
    m_nPosition = 0;
	fclose(f);
	return true;
}

bool LoaderObj::readLine(unsigned int length, unsigned char* buffer)
{
    int l = min((int)length - 1, (int)m_nBufferSize - (int)m_nPosition);
    int i;
        
    if (l <= 0)
    {
        return false;
    }

    for (i = 0; i < l; i++)
    {
        buffer[i] = m_pBuffer[m_nPosition + i];

        if (buffer[i] == '\n')
        {
            break;
        }
    }
    buffer[i + 1] = 0;
    m_nPosition += i + 1;
    return true;
}

void LoaderObj::decoder()
{
    char line[100];
    while (readLine(sizeof(line) - 1, (unsigned char *)line))
    {
        switch (line[0])
        {
            case 'v':
                // Vertices
                switch (line[1])
                {
                    case ' ':
                    {
                        // Vertices
                        char *f = &line[1];
                        int index = 3 * m_nVertexCount;
                        for (int i = 0; i < 3; ++i)
                        {
                            f = strchr(f, ' ') + 1;
                            while (*(f) == ' ')
                            {
                                f++;
                            }
                            m_pVertexs[index++] = (float)atof(f);
                        }
                        m_nVertexCount++;
                    }
                        break;
                    case 't':
                    {
                        // Texture vertices
                        char *f = &line[2];
                        int index = 2 * m_nTextureCoordinateCount;
                        for (int i = 0; i < 2; ++i)
                        {
                            f = strchr(f, ' ') + 1;
                            while (*(f) == ' ')
                            {
                                f++;
                            }
                            m_pTextureCoordinates[index++] = (float)atof(f);
                        }
                        m_nTextureCoordinateCount++;
                    }
                        break;
                    case 'n':
                    {
                        // Normals vertices
                        char *f = &line[2];
                        int index = 3 * m_nNormalCount;
                        for (int i = 0; i < 3; ++i)
                        {
                            f = strchr(f, ' ') + 1;
                            while (*(f) == ' ')
                            {
                                f++;
                            }
                            m_pNormals[index++] = (float)atof(f);
                        }
                        m_nNormalCount++;
                    }
                        break;
                }
                break;

            case 'f':
            {
                // Face
                char *f = &line[1];
                int index = 9 * m_nFaceCount;
                for (int i = 0; i < 3; ++i)
                {
                    f = strchr(f, ' ') + 1;
                    while (*(f) == ' ')
                    {
                        f++;
                    }

                    // vertex                    
                    m_pFaces[index++] = atoi(f);
                    f = strchr(f , '/') + 1;

                    // texture coordinate
                    m_pFaces[index++] = atoi(f);
                    f = strchr(f , '/') + 1;

                    // normal
                    m_pFaces[index++] = atoi(f);
                    
                }
                m_nFaceCount++;
            }
                break;
        }

        memset(line, 0, sizeof(line));
    }
}

bool LoaderObj::loadFile(const char *filePath)
{
    dispose();
    
    // Read file to buffer
    if (!readToBuffer(filePath))
    {
        return false;
    }

    // malloc
    m_pVertexs = new float[3 * MaxVertex];
    m_pTextureCoordinates = new float[2 * MaxVertex];
    m_pNormals = new float[3 * MaxVertex];
    m_pFaces = new int[9 * MaxVertex];
    
    // Decoder
    decoder();

    // Log
    printf("vertex count = %d\n", m_nVertexCount);
    printf("texture count = %d\n", m_nTextureCoordinateCount);
    printf("normal count = %d\n", m_nNormalCount);
    printf("face count = %d\n", m_nFaceCount);

	return true;
}

void LoaderObj::dispose()
{
    deleteArray(m_pBuffer);
    m_nBufferSize = 0;
    m_nPosition = 0;
    
    deleteArray(m_pVertexs);
    m_nVertexCount = 0;
    
    deleteArray(m_pTextureCoordinates);
    m_nTextureCoordinateCount = 0;
    
    deleteArray(m_pNormals);
    m_nNormalCount = 0;
    
    deleteArray(m_pFaces);
    m_nFaceCount = 0;
}

void LoaderObj::cloneData(ModelData &data)
{
    data.vertexCount = m_nVertexCount;
    data.vertexs = new float [3 * data.vertexCount];
    memcpy(data.vertexs, m_pVertexs, sizeof(float) * 3 * data.vertexCount);

    data.textureCoordinateCount = m_nTextureCoordinateCount;
    data.textureCoordinates = new float [2 * data.textureCoordinateCount];
    memcpy(data.textureCoordinates, m_pTextureCoordinates, sizeof(float) * 2 * data.textureCoordinateCount);

    data.normalCount = m_nNormalCount;
    data.normals = new float [3 * data.normalCount];
    memcpy(data.normals, m_pNormals, sizeof(float) * 3 * data.normalCount);

    data.faceCount = m_nFaceCount;
    data.faces = new int [9 * data.faceCount];
    memcpy(data.faces, m_pFaces, sizeof(int) * 9 * data.faceCount);
}
