// p_global_functions.h
// Some frequently used functions.
//
// Copyright 2012 by Hongwei Li. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PT_GLOBAL_FUNCTIONS_H
#define PT_GLOBAL_FUNCTIONS_H

template<typename T>
const T& pMin(const T& a, const T& b)
{
    return a < b? a : b;
}

template<typename T>
const T& pMax(const T& a, const T& b)
{
    return a > b? a : b;
}

template<typename T>
void pSwap(T& a, T& b)
{
    T c(a);
    a = b;
    b = c;
}

#endif // !PT_GLOBAL_FUNCTIONS_H
