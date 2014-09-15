// passert.cpp
// Assert used in debug.
//
// Copyright 2012 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "passert.h" 

#include <PSystem/pcrt.h>
#include <PSystem/pdebugutility.h>
#include <PSystem/plog.h>

PAssertStyleEnum g_assertStyle = P_ASSERT_STYLE_DEFAULT;

void P_APIENTRY pAssertFunction(const pChar* condition, const pChar* file, pUint32 line, const PAssertStyleEnum style)
{
    static pChar buffer[1024];

    switch (style) 
    {
        case P_ASSERT_STYLE_LOGANDEXIT:
            {
                pLogInfo("Assert: %s!", condition);
                pDebugPrintStack(2);
                pabort();
                break;
            }
        case P_ASSERT_STYLE_DEBUG_BREAK:
            psprintf(buffer, 1024, "Assert: %s\n", condition);
            pDebugOutputString(buffer);
            pDebugBreak();
            break;
        case P_ASSERT_STYLE_DEBUG_INFO:
            psprintf(buffer, 1024, "Assert: %s\nPosition: %s(%d)\n", condition, file, line);
            pDebugOutputString(buffer);
            break;
        default:
            // ??
            break;
    }
}

void P_APIENTRY pAssertSetStyle(PAssertStyleEnum style)
{
    g_assertStyle = style;
}
