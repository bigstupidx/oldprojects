// pcrt.h
// C runtime library wrapper
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PCRT_H
#define PCRT_H

#include <PGlobal/pglobal.h>

#include <stdarg.h>


//
// <cstdio>
//

P_EXTERN pUint32 P_CCONV pprintf(const pChar* format, ...);

P_EXTERN pUint32 P_CCONV pvsprintf(pChar* buffer, pUint32 size, const pChar* format, va_list arguments); 

P_EXTERN pUint32 P_CCONV psprintf(pChar* buffer, pUint32 size, const pChar* format, ...);

//
// <cstring>
//
// n should be less than the size of destination buffer size excluding the ending '\0'
P_EXTERN void P_APIENTRY pstrncpy(pChar* dst, const pChar* src, pUint32 n);

P_EXTERN pInt32 P_APIENTRY pstrcmp(const pChar* left, const pChar* right);

P_EXTERN pInt32 P_APIENTRY pstrncmp(const pChar* left, const pChar* right, pUint32 n);

P_EXTERN void P_APIENTRY pstrcpy(pChar* dst, const pChar* src);

P_EXTERN pUint32 P_APIENTRY pstrlen(const pChar* str);

P_EXTERN const pChar* P_APIENTRY pstrrchr(const pChar* str, pChar d);

P_EXTERN const pChar* P_APIENTRY pstrchr(const pChar* str, pChar d);

P_EXTERN pChar* P_APIENTRY pstrdup(const pChar* str);

//
// <cstdlib>
//
P_EXTERN void* P_APIENTRY pmalloc(pUint32 size);

P_EXTERN void P_APIENTRY pfree(void* pointer);

P_EXTERN void* P_APIENTRY prealloc(void* pointer, pUint32 newSize);

P_EXTERN void P_APIENTRY pexit(pInt32 exitCode);

P_EXTERN void P_APIENTRY pmemset(void* pointer, pUint8 c, pUint32 nbytes);

P_EXTERN void P_APIENTRY pmemcpy(void* dst, const void* src, pUint32 nbytes);

P_EXTERN pInt32 P_APIENTRY patoi(const pChar* text);

P_EXTERN pFloat32 P_APIENTRY patof(const pChar* text);

P_EXTERN void P_APIENTRY pabort();


// <cstdio>
typedef void PFile;

#define P_FILE_WRITEONLY          "w"
#define P_FILE_WRITEONLY_BINARY   "wb"
#define P_FILE_READONLY           "r"
#define P_FILE_READONLY_BINARY    "rb"

enum PFileOriginEnum
{
    P_FILE_SEEK_FROM_BEGINNING,
    P_FILE_SEEK_FROM_HERE,
    P_FILE_SEEK_FROM_END,
};

// \return when some errors happen, it returns P_NULL.
P_EXTERN PFile* P_APIENTRY pfopen(const pChar* fileName, const pChar* mode);
P_EXTERN pInt32 P_APIENTRY pfclose(PFile* file);
P_EXTERN pInt32 P_APIENTRY pferror(PFile* file);
P_EXTERN bool P_APIENTRY pfeof(PFile* file);
P_EXTERN bool P_APIENTRY pfeof(PFile* file);
P_EXTERN pInt32 P_APIENTRY pfseek(PFile* file, pInt32 offset, PFileOriginEnum origin);
P_EXTERN pInt32 P_APIENTRY pftell(PFile* file);
P_EXTERN pInt32 P_APIENTRY pfflush(PFile* file);
P_EXTERN pInt32 P_APIENTRY pfgetc(PFile* file);
P_EXTERN pInt32 P_APIENTRY pfputc(PFile* file);
P_EXTERN pChar* P_APIENTRY pfgets(pChar* buffer, pUint32 size, PFile* file);
P_EXTERN pInt32 P_APIENTRY pfputs(pChar* buffer, PFile* file);
P_EXTERN pUint32 P_APIENTRY pfread(void* buffer, pUint32 elementSize, pUint32 elementCount, PFile* file);
P_EXTERN pUint32 P_APIENTRY pfwrite(const void* buffer, pUint32 elementSize, pUint32 elementCount, PFile* file);

#endif // !PCRT_H
