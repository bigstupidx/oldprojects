// pwin32crt.cpp 
// standard C functions and system functions wrapper
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "../pcrt.h"


#include <PSystem/pmemory.h>

#include <windows.h>
#include <stdio.h>


pUint32 P_CCONV pprintf(const pChar* format, ...)
{
    va_list arguments;

    va_start(arguments, format);   

    return vprintf(format, arguments);
}

pUint32 P_CCONV pvsprintf(pChar* buffer, pUint32 size, const pChar* format, va_list arguments)
{
    return vsprintf_s(buffer, size, format, arguments);
}

pUint32 P_CCONV psprintf(pChar* buffer, pUint32 size, const pChar* format, ...)
{
    va_list arguments;

    va_start(arguments, format);   

    return vsprintf_s(buffer, size, format, arguments);
}

#include <string.h>

void P_APIENTRY pstrncpy(pChar* dst, const pChar* src, pUint32 n)
{
    strncpy_s(dst, n + 1, src, _TRUNCATE);
}

void P_APIENTRY pstrcpy(pChar* dst, const pChar* src)
{
    strcpy_s(dst, strlen(dst), src);
}

pInt32 P_APIENTRY pstrcmp(const pChar* left, const pChar* right)
{
    return strcmp(left, right);
}

pInt32 P_APIENTRY pstrncmp(const pChar* left, const pChar* right, pUint32 n)
{
    return strncmp(left, right, n);
}

pUint32 P_APIENTRY pstrlen(const pChar* str)
{
    return (pUint32)strlen(str);
}

pChar* P_APIENTRY pstrdup(const pChar* str)
{
    if (str == P_NULL)
    {
        return P_NULL;
    }

    pChar* ret = P_NULL;
    pUint32 l = (pUint32)strlen(str);

    ret = pNew(pChar[l + 1]);
    strncpy_s(ret, l + 1, str, _TRUNCATE);

    return ret;
}

const pChar* P_APIENTRY pstrrchr(const pChar* str, pChar d)
{
    return strrchr(str, d);
}

const pChar* P_APIENTRY pstrchr(const pChar* str, pChar d)
{
    return strrchr(str, d);
}

#include <stdlib.h>

void* P_APIENTRY pmalloc(pUint32 size)
{
    return malloc((size_t)size);
}

void P_APIENTRY pfree(void* pointer)
{
    free(pointer);
}

void* P_APIENTRY prealloc(void* pointer, pUint32 newSize)
{
    return realloc(pointer, newSize);
}

void P_APIENTRY pexit(pInt32 exitCode)
{
    exit(exitCode);
}

void P_APIENTRY pmemset(void* pointer, pUint8 c, pUint32 nbytes)
{
    memset(pointer, c, nbytes);
}

void P_APIENTRY pmemcpy(void* dst, const void* src, pUint32 nbytes)
{
    memcpy(dst, src, nbytes);
}

pInt32 P_APIENTRY patoi(const pChar* text)
{
    return atoi(text);
}

pFloat32 P_APIENTRY patof(const pChar* text)
{
    return (pFloat32)atof(text);
}

void P_APIENTRY pabort()
{
    abort();
}


static const pInt32 P_FILE_SEEK_TABLE[] = {SEEK_SET, SEEK_CUR, SEEK_END};

PFile* P_APIENTRY pfopen(const pChar* fileName, const pChar* mode)
{
    FILE* file;
    if (!fopen_s(&file, fileName, mode))
    {
        return (PFile*)(file);
    }
    return P_NULL;    
}

pInt32 P_APIENTRY pfclose(PFile* file)
{
    return (pInt32)fclose((FILE*)file);
}

bool P_APIENTRY pfeof(PFile* file)
{
    return feof((FILE*)file) != 0;
}

pInt32 P_APIENTRY pferror(PFile* file)
{
    return (pInt32)ferror((FILE*)file);
}

pInt32 P_APIENTRY pfseek(PFile* file, pInt32 offset, PFileOriginEnum origin)
{
    return (pInt32)fseek((FILE*)file, (pInt32)offset, P_FILE_SEEK_TABLE[origin]);
}

pInt32 P_APIENTRY pftell(PFile* file)
{
    return (pInt32)ftell((FILE*)file);
}

pInt32 P_APIENTRY pfflush(PFile* file)
{
    return (pInt32)fflush((FILE*)file);
}

pInt32 P_APIENTRY pfgetc(PFile* file)
{
    return (pInt32)fgetc((FILE*)file);
}

pInt32 P_APIENTRY pfputc(pInt32 character, PFile* file)
{
    return (pInt32)fputc(character, (FILE*)file);
}

pUint32 P_APIENTRY pfread(void* buffer, pUint32 elementSize, pUint32 elementCount, PFile* file)
{
    return (pUint32)fread(buffer, elementSize, elementCount, (FILE*)file);
}

pUint32 P_APIENTRY pfwrite(const void* buffer, pUint32 elementSize, pUint32 elementCount, PFile* file)
{
    return (pUint32)fwrite(buffer, elementSize, elementCount, (FILE*)file);
}

pChar* P_APIENTRY pfgets(pChar* buffer, pUint32 size, PFile* file)
{
    return fgets(buffer, size, (FILE*)file);
}

pInt32 P_APIENTRY pfputs(pChar* buffer, PFile* file)
{
    return fputs(buffer, (FILE*)file);
}

