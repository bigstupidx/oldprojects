#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "ModelData.h"

class Encoder
{
public:
    Encoder();
    ~Encoder();

    void setData(ModelData &data);
    void saveFile(const char *filePath);
    
private:
    ModelData       mData;
};

#endif // __ENCODER_H__
