// pnew.h
// The global override new and delete operator. This should
// only be used in the engine development and not release to user.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PNEW_H
#define PNEW_H

#include <PGlobal/pglobal.h>

#define pNew(a) (new a)
#define pNewArray(a) (new a)
#define pDelete(p) do { delete p; p = P_NULL; } while (0);
#define pDeleteThis(p) do {delete p;} while(0);
#define pDeleteArray(p) do { delete [] p; p = P_NULL; } while (0);

// FIXME: Introduce the STL new for placement new and delete. Should
// not expose this system-dependent header in KiWi header.
#if defined P_USE_STL
# include <new>
#else 
P_INLINE void* P_CCONV operator new (size_t size, void* ptr) throw() 
{
    return ptr;
}

P_INLINE void* P_CCONV operator new[] (size_t size, void* ptr) throw()
{
    return ptr;
}

P_INLINE void P_CCONV operator delete(void* ptr, void* voidptr2) throw()
{
}

P_INLINE void P_CCONV operator delete[] (void* ptr, void* voidptr2) throw()
{
}
#endif


#endif // !PNEW_H
