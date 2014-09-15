// pmeshloader.h
// load objc file, convert to mesh.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Su Yu suyu@cooee.cn
//
// 
#include "pmeshloader.h"

#include <PCore/pstream.h>

PMeshLoader::PMeshLoader(const pChar *pathName)
    : m_data(P_NULL)
{
    PInputStream stream;
    if (stream.createFromFile(pathName, P_STREAM_ENDIANNESS_LITTLE))
    {
        m_data = pNew(MeshData);
        decodeObjc(&stream);
    }
    else
    {
        pLogError("Failed to open mesh file %s", pathName);
    }
}

PMeshLoader::~PMeshLoader()
{
    pDelete(m_data);
}

void PMeshLoader::decodeObjc(PInputStream *stream)
{
    // The outline of objc file:
    // +------+------+------+------+------+------+------+------+
    // | header | chunk | chunk | chunk | chunk | chunk | ... ... | footer |
    // +------+------+------+------+------+------+------+------+
    // A objc file only include chunks besides header and footer.

    // head guard
    pChar header[5];
    pUint32 id;
    stream->readString(4, &header[0]);
    header[4] = 0;
    stream->readUint32(&id);
    if (pstrcmp(header, "PROT") != 0 ||
        id != 0x20061320)
    {
        return;
    }

    // start read chunk
    readChunk(stream);
}

void PMeshLoader::readChunk(PInputStream *stream)
{
    // The outline of a chunk:
    // +------------+--------------+-------------+
    // | pUint32 id | pUint32 size | data[chunk] |
    // +------------+--------------+-------------+
    // Data may contains chunks.
    // size = sizeof(id) + sizeof(size) + sizeof(data)
    // sizeof(data) = size - 8
    //
    // A sample of objc file:
    // primary chunk(id: 0x01004b43)
    //     | object chunk(id: 0x00014b43)
    //     |     | mesh chunk(id: 0x00114b43)
    //     |     |     | mesh vertex chunk(id: 0x10114b43)
    //     |     |     |      | pUint16  vertexCount
    //     |     |     |      | pFloat32 vertexs[vertexCount][3]
    //     |     |     | face chunk(id: 0x11114b43)
    //     |     |     |      | pUint16 faceCount
    //     |     |     |      | pUint16 faces[faceCount][3]
    //     |     |     | texture coordinate chunk(id: 0x12114b43)
    //     |     |     |      | pFloat32 textureCoordinate[vertexCount][2]
    //     |     |     | normal chunk(id: 0x14114b43)
    //     |     |     |      | pFloat32 normals[vertexCount][3]
    // This kind of structure is very easy to extend, for example:
    //     |     | light chunk
    //     | material chunk
    // version chunk()
    //     | pUint32 version
    // We can gradually extend it in the future.

    //
    // There are two formats of vertex buffer. The first one is called separated.
    // Vertex data are clustered together, and then followed by all normals and then
    // by all texture coordinates. 
    // +--------------+---------------+--------------+
    // | v0v1v2v3v4...| n0n1n2n3n4... | t0t1t2t3t4...|
    // +--------------+---------------+--------------+
    //
    // The other format is called interleaved. The data are constructed by putting
    // all data related to one vertex together, like
    // +--------+--------+--------+--------+-------+
    // | v0n0t0 | v1n1t1 | v2n2t2 | v3n3t3 | ...   |
    // +--------+--------+--------+--------+-------+
    //
    // The interleaved format is recommended more as it provides better rendering
    // performance as we used here.

    pInt32 state = 0; // 0: decoding, 1: end, 2: error
    
    while ((state == 0) && !stream->isEndOfStream())
    {
        pUint32 id;
        pUint32 size;
        stream->readUint32(&id);
        stream->readUint32(&size);
        switch (id)
        {
            case 0x53534f54: // footer guard
                if (size != 0x20061320)
                {
                    // since objc file is end with wrong footer, m_data is may not correct.
                    state = 2;
                }
                else
                {
                    state = 1;
                }
                break;
            case 0x01004b43: // primary chunk
                break;
            case 0x00014b43: // object chunk
                break;
            case 0x00114b43: // mesh chunk
                break;
            case 0x10114b43: // mesh vertex chunk
            {
                // read vertex count and alloc vertex buffer memory in mesh vertex chunk.
                stream->readUint16(&m_data->vertexCount);
                m_data->vertexBuffer = pNewArray(pFloat32[m_data->vertexCount * (3 + 2 + 3)]);

                pFloat32 *vertices = pNewArray(pFloat32[m_data->vertexCount * 3]);
                if (!stream->readBytes(m_data->vertexCount * 3 * sizeof(pFloat32),
                    (pUint8 *)vertices))
                {
                    // read stream error.
                    state = 2;
                }
                else
                {
                    // copy vertices to vertex buffer
                    pFloat32 *p = m_data->vertexBuffer;
                    for (int i = 0; i < m_data->vertexCount; i++)
                    {
                        *(p++) = *(vertices++);
                        *(p++) = *(vertices++);
                        *(p++) = *(vertices++);

                        p += 5;
                    }
                }
                pDeleteArray(vertices);
            }
                break;
            case 0x11114b43: // face chunk
            {
                stream->readUint16(&m_data->faceCount);
                m_data->faces = pNewArray(pUint16[m_data->faceCount * 3]);
                if (!stream->readBytes(m_data->faceCount * 3 * sizeof(pUint16),
                    (pUint8 *)m_data->faces))
                {
                    // read stream error.
                    state = 2;
                }
            }
                break;
            case 0x12114b43: // texture coordinate chunk
            {
                pFloat32 *textureCoordinates = pNewArray(pFloat32[m_data->vertexCount * 2]);
                if (!stream->readBytes(m_data->vertexCount * 2 * sizeof(pFloat32),
                    (pUint8 *)textureCoordinates))
                {
                    // read stream error.
                    state = 2;
                }
                else
                {
                    // copy textureCoordinates to vertex buffer
                    pFloat32 *p = m_data->vertexBuffer + 3;
                    for (int i = 0; i < m_data->vertexCount; i++)
                    {
                        *(p++) = *(textureCoordinates++);
                        *(p++) = *(textureCoordinates++);

                        p += 6;
                    }
                }
                pDeleteArray(textureCoordinates);
            }
                break;
            case 0x14114b43: // normal chunk
            {
                pFloat32 *normals = pNewArray(pFloat32[m_data->vertexCount * 3]);
                if (!stream->readBytes(m_data->vertexCount * 3 * sizeof(pFloat32),
                        (pUint8 *)normals))
                {
                    // read stream error.
                    state = 2;
                }
                else
                {
                    // copy normals to vertex buffer
                    pFloat32 *p = m_data->vertexBuffer + 5;
                    for (int i = 0; i < m_data->vertexCount; i++)
                    {
                        *(p++) = *(normals++);
                        *(p++) = *(normals++);
                        *(p++) = *(normals++);

                        p += 5;
                    }
                }
                pDeleteArray(normals);
            }
                break;
            default: // unknown chunk
                stream->skipBytes(size - 8);
                break;
        }
    }

    // We finish the reading the whole stream, but not come across the right footer. 
    // m_data may not be correct now.
    if (state != 1)
    {
        pDelete(m_data);
    }
}

pUint16 PMeshLoader::getVertexCount() const
{
    if (m_data)
    {
        return m_data->vertexCount;
    }

    return 0;
}

pFloat32 *PMeshLoader::getVertexBuffer() const
{
    if (m_data)
    {
        return m_data->vertexBuffer;
    }

    return P_NULL;
}

pUint16 PMeshLoader::getFaceCount() const
{
    if (m_data)
    {
        return m_data->faceCount;
    }
    return 0;
}

pUint16 *PMeshLoader::getIndexBuffer() const
{
    if (m_data)
    {
        return m_data->faces;
    }

    return P_NULL;
}

