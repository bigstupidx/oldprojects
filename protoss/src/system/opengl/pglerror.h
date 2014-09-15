// pglerror.h
// To detect and return the graphics error.
// 
// Copyright 2012 by Hongwei Li. All rights reserved.
// 
// Hongwei Li lihw81@gmail.com
// 

#ifndef P_GLERROR_H
#define P_GLERROR_H

#include <PSystem/plog.h>

P_EXTERN bool P_APIENTRY pGlErrorCheck(const pChar* file, pUint32 line, PLogLevelEnum logLevel);
#define pGlErrorCheckError() pGlErrorCheck(__FILE__, __LINE__, P_LOG_ERROR)
#define pGlErrorCheckWarning() pGlErrorCheck(__FILE__, __LINE__, P_LOG_WARNING)
#define pGlErrorCheckAbort() if (!pGlErrorCheck(__FILE__, __LINE__, P_LOG_ERROR)) { return false; }

#endif  // P_GLERROR_H


