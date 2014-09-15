#include "writer.h"
#include <string.h>

static Writer *s_sharedWriter = NULL;

Writer *Writer::shardedWriter()
{
    if (s_sharedWriter == NULL)
    {
        s_sharedWriter = new Writer();
    }
    return s_sharedWriter;
}

Writer::Writer()
{
}

Writer::~Writer()
{
    closeFile();
}

bool Writer::openFile(const char *filePath)
{
    // close first
    closeFile();
    
    fopen_s(&m_file, filePath, "wb");
    m_nPosition = 0;
    
    return (m_file != NULL);
}

void Writer::closeFile()
{
    if (m_file)
    {
        fclose(m_file);
        m_file = NULL;
    }
}

void Writer::writeInt(unsigned int data)
{
    int bWritten = fwrite(&data, sizeof(unsigned int), 1, m_file);
    
    m_nPosition += sizeof(unsigned int);
}

void Writer::writeFloat(float data)
{
    fwrite(&data, sizeof(float), 1, m_file);
    
    m_nPosition += sizeof(float);
}

void Writer::writeChars(const char *string)
{
    fwrite(string, strlen(string), 1, m_file);
    
    m_nPosition += strlen(string);
}

int Writer::getPosition() const
{
    return m_nPosition;
}

void Writer::seek(int position)
{
    fseek(m_file, position, SEEK_SET);
    m_nPosition = position;
}
