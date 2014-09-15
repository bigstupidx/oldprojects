// pimagepng_private.h
// Read and write PNG file using libpng.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PIMAGEPNG_PRIVATE_H
#define PIMAGEPNG_PRIVATE_H

#include <PCore/pimage.h>

class PInputStream;
class POutputStream;

P_EXTERN bool P_APIENTRY pImagePNGRead(PInputStream& inputStream, pUint32& width, pUint32& height, 
    PImagePixelFormatEnum& format, pUint8*& data);

P_EXTERN bool P_APIENTRY pImagePNGWrite(POutputStream& outputStream, pUint32 width, pUint32 height, 
    PImagePixelFormatEnum format, const pUint8* data);


#endif // !PIMAGEPNG_PRIVATE_H
