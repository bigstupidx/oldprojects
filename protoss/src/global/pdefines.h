// pdefines.h
// The defines and common macros used in Kiwi.
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PDEFINES_H
#define PDEFINES_H

#if defined _DEBUG || defined _DEBUG
# define P_DEBUG 1
#endif

#ifndef P_GLOBAL
# define P_GLOBAL // an marker to indicate the variable is globally visible.
#endif


//
// Helper marcos
//

// Usage:
// #define SOME_MARCO() P_MULTILINE_MARCO_BEGIN \
// ... \
// ... \
// P_MULTILINE_MARCO_END
#define P_MULTILINE_MACRO_BEGIN { 
#define P_MULTILINE_MACRO_END }

// Function are mangled as a c interface
#define P_EXTERNC_BEGIN extern "C"  {
#define P_EXTERNC_END }          

// Unused arguments.
#define P_UNUSED_ARGUMENT(p)  ((void)p)

#endif // !PDEFINES_H

