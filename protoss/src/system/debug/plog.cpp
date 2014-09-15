// plog.cpp
// The log helper functions.
// 
// Copyright 2012 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com

#include "plog.h"

#include <stdarg.h>

#include <PSystem/pcrt.h>
#include <PSystem/pdebugutility.h>

static void P_APIENTRY pLogWrite(PLogLevelEnum level, 
    const pChar* message, 
    pUint32 nchars)
{
    if (level == P_LOG_DEBUG)
    {
        pDebugOutputString(const_cast<pChar*>(message));
    }
    else 
    {
        pprintf(message);
    }
}

void P_CCONV pLog(PLogLevelEnum level, 
    const pChar* file, 
    pUint32 line, 
    const pChar* format, 
    ...)
{
    static const pChar* levelText[] = 
    {
        "(error)",
        "(warning)",
        "(info)",
        "",
    };

    va_list arguments;

    va_start(arguments, format);

    if (pstrlen(format) > 200)
    {
        pChar message[1024];
        pUint32 nchars = psprintf(message, 1024, 
                "(warning)%s:%d,log buffer of format is too small.",
                __FILE__, __LINE__);
        pLogWrite(P_LOG_WARNING, message, nchars);
        return ;
    }

    pChar msg[3000]; 
    pUint32 nchars;
    if (level == P_LOG_ERROR || level == P_LOG_WARNING)
    {
        pChar fmt[256];
        psprintf(fmt, 256, "%s%s:%d,%s.", 
            levelText[level], file, line, format);
        nchars = pvsprintf(msg, 3000, fmt, arguments);
    }
    else 
    {
        nchars = pvsprintf(msg, 3000, format, arguments);
    }

    pLogWrite(level, msg, nchars);
}

