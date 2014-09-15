#ifndef __MACRO_H__
#define __MACRO_H__

#ifndef NULL
#define NULL 0
#endif

template<typename T>
const T& min(const T& a, const T& b)
{
    return a < b? a : b;
}

#define deleteThis(p) do {if (p) delete p;} while(0);
#define deleteArray(p) do { if (p) { delete [] p; p = NULL; } } while (0);

#endif // __MACRO_H__