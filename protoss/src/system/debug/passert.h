// passert.h
// Assert used in debug.
//
// Copyright 2012 by Hongwei Li. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PASSERT_H
#define PASSERT_H

#include <PGlobal/pglobal.h>

//
// Assert that will be checked at compile time.
// the predicate needs to be decidable at compile time.
// The call can only be made were a C statement is expected.
//
#define P_COMPILE_TIME_ASSERT(pred) switch(0) { case 0: case (pred): break; }

// The styles of the assert.
enum PAssertStyleEnum
{
    P_ASSERT_STYLE_LOGANDEXIT,     ///< write to stdout/logcat and exit.
    P_ASSERT_STYLE_POPUP_BOX,      ///< use popup dialog box.
    P_ASSERT_STYLE_DEBUG_BREAK,    ///< OutputDebugString + debug break
    P_ASSERT_STYLE_DEBUG_INFO,     ///< outputDebugString

    P_ASSERT_STYLE_DEFAULT = P_ASSERT_STYLE_DEBUG_BREAK,
};

//
// Assert function.
// \param condition the condition string.
// \param file in which file this assert is triggered.
// \param line at which line this assert is.
// \param style how to present this assert to user.
P_EXTERN void P_APIENTRY pAssertFunction(const pChar* condition, const pChar* file, pUint32 line, const PAssertStyleEnum style);

extern PAssertStyleEnum g_assertStyle;

// Set the assert style in the application-wise scope. The default style is P_ASSERT_STYLE_DEBUG_BREAK.
P_EXTERN void P_APIENTRY pAssertSetStyle(PAssertStyleEnum style);

#if defined P_DEBUG

#define pAssert(condition) P_MULTILINE_MACRO_BEGIN \
    if (!(condition)) \
    { \
        pAssertFunction((#condition), __FILE__, __LINE__, g_assertStyle); \
    } \
P_MULTILINE_MACRO_END

#define pAssertInfo(condition, text) P_MULTILINE_MACRO_BEGIN \
    if (!(condition)) \
    { \
        pAssertFunction(text, __FILE__, __LINE__, g_assertStyle); \
    } \
P_MULTILINE_MACRO_END

#define pAssertNotReachable() \
        pAssertFunction("should not reach here", __FILE__, __LINE__, g_assertStyle); 

#define pAssertNotImplemented() \
        pAssertFunction("not implemented", __FILE__, __LINE__, g_assertStyle); 

#else

#define pAssert(condition)
#define pAssertInfo(condition, text)
#define pAssertNotReachable() 
#define pAssertNotImplemented() 

#endif // P_DEBUG


#endif // !pASSERT_H
