// plog.h
// The log helper functions.
// 
// Copyright 2012 by Hongwei Li. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PLOG_H
#define PLOG_H

#include <PGlobal/pglobal.h>

class KwLogAbstractOutput;

//
// The levels of the log
enum PLogLevelEnum
{
    P_LOG_INFO,
    P_LOG_DEBUG,
    P_LOG_WARNING,
    P_LOG_ERROR,
    
};

// Output the log in the formatted way
// \param level the level of this log message
// \param file at which file this log message is generated.
// \param line at which line of the file this log message is created.
// \param format the format specifier as the one in printf.
P_EXTERN void P_CCONV pLog(PLogLevelEnum level, const pChar* file, pUint32 line, const pChar* format, ...);

#if defined P_LOG_ENABLED
# if defined P_GCC
#  define pLogError(fmt, ...) \
    do { pLog(P_LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__); } while (0)
#  define pLogWarning(fmt, ...) \
    do { pLog(P_LOG_WARNING, __FILE__, __LINE__, fmt, ##__VA_ARGS__); } while (0)
#  define pLogInfo(fmt, ...) \
    do { pLog(P_LOG_INFO, P_NULL, 0, fmt, ##__VA_ARGS__); } while (0)
# elif defined P_MSC
#  define pLogError(fmt, ...) \
    do { pLog(P_LOG_ERROR, __FILE__, __LINE__, fmt, __VA_ARGS__); } while (0)
#  define pLogWarning(fmt, ...) \
    do { pLog(P_LOG_WARNING, __FILE__, __LINE__, fmt, __VA_ARGS__); } while (0)
#  define pLogInfo(fmt, ...) \
    do { pLog(P_LOG_INFO, P_NULL, 0, fmt, __VA_ARGS__); } while (0)
# else
#  error "unsupported platform"
# endif
# if defined P_DEBUG
#  if defined P_GCC
#   define pLogDebug(fmt, ...) \
     do{ pLog(P_LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__); } while (0)
#   define pLogDebugIf(cond, fmt, ...) \
     { if ((cond)) { pLog(P_LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__); } }
#  elif defined P_MSC
#   define pLogDebug(fmt, ...) \
     do { pLog(P_LOG_DEBUG, __FILE__, __LINE__, fmt, __VA_ARGS__); } while (0)
#   define pLogDebugIf(cond, fmt, ...) \
     { if ((cond)) { pLog(P_LOG_DEBUG, __FILE__, __LINE__, fmt, __VA_ARGS__); } }
#  else
#   error "unsupported platform"
#  endif
# else
#   define pLogDebug(fmt, ...) 
#   define pLogDebugIf(cond, fmt, ...) 
# endif
#else
# define pLogError(fmt, ...) 
# define pLogWarning(fmt, ...) 
# define pLogInfo(fmt, ...)
# define pLogDebug(fmt, ...)
# define pLogDebugIf(cond, fmt, ...)
#endif // PLOG_ENABLED


#endif // !PLOG_H
