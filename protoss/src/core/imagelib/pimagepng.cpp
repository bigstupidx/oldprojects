// pimagepng.cpp
// Read and write PNG file using libpng.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pimagepng_private.h"

extern "C" {
#include <png.h>
}

#include <PCore/pstream.h>

#include <PSystem/pdebug.h>
#include <PSystem/pmemory.h>

static void pImagePNGReadFunction(png_structp png_ptr, png_bytep data, png_size_t length)
{
    PInputStream* inputStream = (PInputStream*)png_get_io_ptr(png_ptr);

    bool ret = inputStream->readBytes(length, (pUint8*)data);
    pAssert(ret);
}

static void pImagePNGWriteFunction(png_structp png_ptr, png_bytep data, png_size_t length)
{
    POutputStream* outputStream = (POutputStream*)png_get_io_ptr(png_ptr);

    bool ret = outputStream->writeBytes(length, (pUint8*)data);
    pAssert(ret);
}

static void pImagePNGFlushFunction(png_structp png_ptr)
{
    // This function has been intentionally left empty. 
}

static png_voidp pImagePNGMallocFunction(png_structp png_ptr, png_size_t size)
{
    png_voidp allocatedBlock = pNewArray(pUint8[size]);
    pAssert(allocatedBlock != P_NULL);

    return allocatedBlock;
}

static void pImagePNGFreeFunction(png_structp png_ptr, png_voidp data)
{
    pUint8* p = (pUint8*)data;
    pDeleteArray(p);
}

bool P_APIENTRY pImagePNGRead(PInputStream& inputStream, pUint32& width, pUint32& height, 
    PImagePixelFormatEnum& format, pUint8*& data)
{
    pUint8** rowPointers = P_NULL;

    // LibPNG specific structures. 
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_infop end_ptr = NULL; 
    png_byte pbSig[8];
    png_uint_32 png_result;

    if (!inputStream.readBytes(8, (pUint8*)pbSig))
    {
        return false;
    }

    // Check that we're reading valid PNG file. 
    if (!png_sig_cmp(pbSig, 0, 8))
    {
        pLogError("not a valid PNG image (incorrect signature)");
        return false;
    }

    // Our png_ptr is used by the libpng library to maintain, basically, state
    // information about the PNG file as it is being read in by the library.
    // It's used for housekeeping by the libpng library.  The other two
    // pointers, info_ptr and end_ptr, are used to help us extract data from
    // the PNG file. 
    png_ptr = png_create_read_struct_2(
            PNG_LIBPNG_VER_STRING, 
            NULL, // error function pointer 
            NULL, // error printing function
            NULL, // warning function
            NULL, // memory pointer
            pImagePNGMallocFunction, // memory allocation function pointer 
            pImagePNGFreeFunction); // memory deallocation function pointer
    if (png_ptr == P_NULL)
    {
        pLogError("can't create PNG reading structure");
        return false;
    }
    
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
        pDeleteArray(data);
        pDeleteArray(rowPointers);
        return false;
    }

    // Create png info structure.
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
        png_destroy_read_struct(&png_ptr, (png_infopp)P_NULL, (png_infopp)P_NULL);
        pLogError("can't create PNG info structure");
        return false;
    }

    end_ptr = png_create_info_struct(png_ptr);
    if (end_ptr == NULL) 
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
        pLogError("can't create PNG info structure");
        return false;
    }

    png_set_read_fn(png_ptr, (png_voidp)&inputStream, pImagePNGReadFunction);
    png_set_sig_bytes(png_ptr, 8);

    // Read png info. 
    png_read_info(png_ptr, info_ptr);

    // Read image info (width, height, color format) and data. 
    pInt32 bitDepth;
    pInt32 colorType;
    pUint32 channelCount;

    // Fetch image width, height, bit depth, color type. 
    png_result = png_get_IHDR(png_ptr, info_ptr, (png_uint_32*)&width, 
            (png_uint_32*)&height, &bitDepth, &colorType, NULL, NULL, NULL);
    if (png_result == 0)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
        pLogError("PNG image has invalid header");
        return false;
    }

    // See how many channels this png contains. 
    channelCount = (pUint32)png_get_channels(png_ptr, info_ptr);

    // Non-paletted image. 
    if (colorType != PNG_COLOR_TYPE_PALETTE)
    {
        // Support only for 8 bit depth pixels. 
        if (bitDepth == 8)
        {
            switch (channelCount)
            {
                case 1: format = P_IMAGE_PIXELFORMAT_R8; break;
                case 2: format = P_IMAGE_PIXELFORMAT_RA88; break;
                case 3: format = P_IMAGE_PIXELFORMAT_RGB888; break;
                case 4: format = P_IMAGE_PIXELFORMAT_RGBA8888; break;
                default: 
                         png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
                         pLogError("Unsupported PNG pixel format");
                         return false;
            }
        }
        else
        {
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
            pLogError("Unsupported PNG pixel format");
            return false;
        }
    }
    else
    {
        // Paletted image. 
        format = P_IMAGE_PIXELFORMAT_RGB888;
    }

    if (bitDepth == 16)
    {
        png_set_strip_16(png_ptr);
        bitDepth = 8;
    }

    pUint32 rowSize = width * channelCount * (pUint32)bitDepth / 8;

    // Create row pointers for libpng and unpack the data to new buffers, finally assigning to image. 
    data = pNewArray(pUint8[rowSize * height]);
    pAssert(data != P_NULL);
    if (data == P_NULL)
    {
        pLogError("new pUint8 [%d] failed", rowSize * height);
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
        return false;
    }

    // Assign pointers for each row. 
    rowPointers = pNewArray(pUint8*[height]);
    pAssert(rowPointers != P_NULL);
    if (rowPointers == P_NULL)
    {
        pDeleteArray(data);
        pLogError("rowPointers = new pUint8* [%d] failed", height);
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
        return false;
    }

    pUint8* datap = data;
    for (pUint32 i = 0; i < height; ++i)
    {
        rowPointers[i] = datap;

        datap += rowSize;
    }

    // Read image data using libpng.
    png_read_image(png_ptr, (png_bytepp)rowPointers);
    png_read_end(png_ptr, NULL);

    pDeleteArray(rowPointers);

    /* Convert to RGB data in case of paletted png. */
    if (colorType == PNG_COLOR_TYPE_PALETTE)
    {
        png_colorp palette;
        pInt32 numPalette;

        png_result = png_get_PLTE(png_ptr, info_ptr, &palette, &numPalette);
        if(png_result == 0)
        {
            pDeleteArray(data);
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
            pLogError("invalid PNG palette");
            return false;
        }

        pUint8* convertedImage = pNewArray(pUint8[width * height * 3]);
        pAssert(convertedImage != P_NULL);
        if (convertedImage == P_NULL)
        {
            pDeleteArray(data);
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
            pLogError("convertedImage = new pUint8 [%d] failed", height * width * 3);
            return false;
        }

        // 4-bit palette, assign 2 pixels at a time. 
        if (bitDepth == 4)
        {
            pUint32 offset = 0;
            pUint32 imageSize = width * channelCount * (pUint32)bitDepth * height / 8;

            // If both width and height are odd, no support for loading. 
            if ((width & 1) != 0 && (height & 1) != 0)
            {
                pDeleteArray(data);
                pDeleteArray(convertedImage);
                png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
                pLogError("4bit paletted png image with width and height having odd values not supported");
                return false;
            }

            for (pUint32 i = 0; i < imageSize; ++i)
            {
                pUint32 highByte = (pUint32)(data[i] >> 4);
                pUint32 lowByte = (pUint32)(data[i] & 0x0F);
                convertedImage[offset++] = (pUint8)palette[highByte].red;
                convertedImage[offset++] = (pUint8)palette[highByte].green;
                convertedImage[offset++] = (pUint8)palette[highByte].blue;
                convertedImage[offset++] = (pUint8)palette[lowByte].red;
                convertedImage[offset++] = (pUint8)palette[lowByte].green;
                convertedImage[offset++] = (pUint8)palette[lowByte].blue;
            }
        }
        // 8 bit palette, assign colors by fetching from palette. 
        else if (bitDepth == 8)
        {
            pUint32 offset = 0;
            pUint32 imageSize = rowSize * height;
            for (pUint32 i = 0; i < imageSize; i++)
            {
                pUint8 colorValue = data[i];
                convertedImage[offset++] = (pUint8)palette[colorValue].red;
                convertedImage[offset++] = (pUint8)palette[colorValue].green;
                convertedImage[offset++] = (pUint8)palette[colorValue].blue;
            }
        }
        else
        {
            pDeleteArray(data);
            pDeleteArray(convertedImage);
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
            pLogError("Invalid paletted image format");
            return false;
        }

        pDeleteArray(data);
        data = convertedImage;
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);

    return true;
}

bool P_APIENTRY pImagePNGWrite(POutputStream& outputStream, pUint32 width, pUint32 height, 
    PImagePixelFormatEnum format, const pUint8* data)
{
    pAssert(format == P_IMAGE_PIXELFORMAT_RGB888 ||
             format == P_IMAGE_PIXELFORMAT_RGBA8888);
    if (format != P_IMAGE_PIXELFORMAT_RGBA8888 &&
        format != P_IMAGE_PIXELFORMAT_RGB888)
    {
        pLogError("unsupported pixel format by PNG");
        return false;
    }

    /* Create the write struct for png. */
    png_structp png_ptr = png_create_write_struct_2(
            PNG_LIBPNG_VER_STRING, 
            NULL, 
            NULL, 
            NULL, 
            NULL, 
            pImagePNGMallocFunction, 
            pImagePNGFreeFunction);
    if (png_ptr == NULL)
    {
        pLogError("error in writing PNG image");
        return false;
    }

    // Create the info struct for png. Info struct contains info such as width,
    // height, bit depth and other attributes of image. 
    png_infop info_ptr = png_create_info_struct (png_ptr);
    if(info_ptr == NULL)
    {
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        pLogError("Error in writing PNG image");
        return false;
    }

    png_set_write_fn(png_ptr, (png_voidp)&outputStream, pImagePNGWriteFunction, pImagePNGFlushFunction);

    // Set png to non-interlaced, non-compressed RGB mode. 
    png_set_IHDR(png_ptr, info_ptr, (png_uint_32)width, (png_uint_32)height, 8,
                 format == P_IMAGE_PIXELFORMAT_RGB888 ? PNG_COLOR_TYPE_RGB : PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);

    // Write the image data. 
    pUint32 rowSize = width * PImage::getBPP(format);

    pUint8** rowPointers = pNewArray(pUint8*[height]);
    pAssert(rowPointers != P_NULL);
    if (rowPointers == P_NULL)
    {
        pLogError("rowPointers = new pUint8* [%d] failed", height);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return false;
    }

    pUint8* datap = const_cast<pUint8*>(data);

    for (pUint32 i = 0; i < height; ++i)
    {
        rowPointers[i] = datap;
        datap += rowSize;
    }

    png_write_image(png_ptr, (png_bytepp)rowPointers);
    png_write_end(png_ptr, NULL);

    png_destroy_write_struct(&png_ptr, &info_ptr);

    pDeleteArray(rowPointers);

    return true;
}

