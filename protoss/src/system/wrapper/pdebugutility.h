// pdebugutility.h
// Debug utility wrapper
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PDEBUGUTILITY_H
#define PDEBUGUTILITY_H

#include <PGlobal/pglobal.h>


P_EXTERN void P_APIENTRY pDebugOutputString(pChar* message);

P_EXTERN void P_APIENTRY pDebugBreak();

P_EXTERN void P_APIENTRY pDebugPrintStack(pInt32 skip);

// FIXME: win32 needs to link dgbhelp.lib
#if defined P_MSC
# pragma comment (lib, "dbghelp.lib")
#endif 


#endif // !PDEBUGUTILITY_H
