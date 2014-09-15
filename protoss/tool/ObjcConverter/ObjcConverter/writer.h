#ifndef __WRITER_H__
#define __WRITER_H__

#include <stdio.h>

class Writer
{
public:
    Writer();
    ~Writer();

	static Writer *shardedWriter();

	bool openFile(const char *filePath);
	void closeFile();

	void writeInt(unsigned int data);
	void writeFloat(float data);
	void writeChars(const char *string);
	int getPosition() const;	
	void seek(int position);
	
private:
    FILE 	*m_file;
	int 	m_nPosition;
};

#endif // __WRITER_H__
