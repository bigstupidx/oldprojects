// ptime.h
// Fetch and set the system time.
// 
// Copyright 2012 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//


#ifndef PTIME_H
#define PTIME_H

#include <PGlobal/pglobal.h>


struct PTime
{
    pUint32 m_hours;   ///< Hours 0-23 
    pUint32 m_minutes; ///< Minutes 0-59. 
    pUint32 m_seconds; ///< Seconds 0-59. 
    pUint32 m_day;     ///< Day of month. 1 is the first day. 
    pUint32 m_month;   ///< Month of year. 1 is January. 
    pUint32 m_year;    ///< Year. 
};

// Returns the current time and date in a structure. 
// \return the current time in PTime structure.
P_EXTERN PTime P_APIENTRY pTimeGetTime(void);

// Sets the current time and date. 
// \param time the target current time. 
P_EXTERN void P_APIENTRY pTimeSetTime(const PTime* time);

// Returns current time from the system in milliseconds.
// Values should be only used relative to each other because starting time is not specified.
// \return the current timestamp.
P_EXTERN pUint32 P_APIENTRY pTimeGetCurrentTimestamp(void);

#if defined P_MSC
# pragma comment (lib, "winmm.lib") // for timeGetTime();
#endif

#endif
