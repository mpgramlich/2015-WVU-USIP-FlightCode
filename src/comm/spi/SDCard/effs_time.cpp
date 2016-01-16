/* Revision: 2.7.3 */

/******************************************************************************
* Copyright 1998-2015 NetBurner, Inc.  ALL RIGHTS RESERVED
*
*    Permission is hereby granted to purchasers of NetBurner Hardware to use or
*    modify this computer program for any use as long as the resultant program
*    is only executed on NetBurner provided hardware.
*
*    No other rights to use this program or its derivatives in part or in
*    whole are granted.
*
*    It may be possible to license this or other NetBurner software for use on
*    non-NetBurner Hardware. Contact sales@Netburner.com for more information.
*
*    NetBurner makes no representation or warranties with respect to the
*    performance of this computer program, and specifically disclaims any
*    responsibility for any damages, special or consequential, connected with
*    the use of this program.
*
* NetBurner
* 5405 Morehouse Dr.
* San Diego, CA 92121
* www.netburner.com
******************************************************************************/


/*-------------------------------------------------------------------
  Time functions that can be used for EFFS file time stamps.
 ------------------------------------------------------------------*/
#include "predef.h"
#include <stdio.h>
#include <stdlib.h>
#include <startnet.h>
#include <tcp.h>
#include <basictypes.h>
#include <nbtime.h>
#include <time.h>

#if ( !defined PK70 && !defined SB70LC && !defined CB34EX && !defined NANO54415 && !defined MOD5441X )
#include "rtc.h"
#endif

#include <ethernet.h>
#include <dns.h>



/*-------------------------------------------------------------------
  SetTimeNTP() - Acquires time from a NTP server and sets the system
  time. For this function to operate correctly you need to have:
  - Access to the Internet
  - Valid IP address, mask, gateway and DNS set on your NetBurner device
 -------------------------------------------------------------------*/
BOOL SetTimeNTP()
{

   if( !(EtherLink()) )
      OSTimeDly( (WORD)(1.5 * TICKS_PER_SECOND) );

   iprintf( "Acquiring time from NTP server... " );

   if ( SetTimeNTPFromPool() )
   {
      iprintf( "Complete\r\n" );
      return TRUE;
   }
   else
   {
      iprintf( "Failed\r\n" );
      iprintf("Verify you have correct IP address, mask, gateway AND DNS set\r\n");
   }
   return FALSE;
}


/*-------------------------------------------------------------------
   SetTimeManual() - Manually set the system time.

   This purpose of this function is to illustrate how to use the
   time structures, variables and functions to set the system time
   manually. You can use these functions to interface to any custom
   time source you may have access to instead of NTP or the RTC
   on the NetBurner development board.

   The time functions use the following structures and types:

   typedef struct tm {
      int tm_hour;   // hour (0 - 23)
      int tm_isdst;  // daylight saving time enabled/disabled
      int tm_mday;   // day of month (1 - 31)
      int tm_min;    // minutes (0 - 59)
      int tm_mon;    // month (0 - 11 : 0 = January)
      int tm_sec;    // seconds (0 - 59)
      int tm_wday;   // Day of week (0 - 6 : 0 = Sunday)
      int tm_yday;   // Day of year (0 - 365)
      int tm_year;   // Year less 1900
   }

   time_t: When interpreted as a calendar time value, it represents the
   number of seconds elapsed since 00:00:00 on January 1, 1970,
   Coordinated Universal Time. It is of type DWORD, and used for time
   calculations.

 -------------------------------------------------------------------*/
void SetTimeManual( int month, int day, int weekday, int year, int hour, int min, int sec )
{
    struct tm SetTime;

    SetTime.tm_mon  = month;
    SetTime.tm_mday = day;
    SetTime.tm_wday = weekday;
    SetTime.tm_year = year - 1900;
//    SetTime.tm_yday = 165;

    SetTime.tm_hour = hour;
    SetTime.tm_min  = min;
    SetTime.tm_sec  = sec;

    /* set_time() need a parameter of time_t, so use mktime() to convert
       a struct tm type to a time_t type.
    */
    set_time( mktime( &SetTime ) );
}




/*-------------------------------------------------------------------
 Set the system time with a real-time clcok. This function will only
 work if you actually have RTC hardware connected to your NetBurner
 device, such as the RTC on the development board.

 If you are using NTP or the Manual method to set time, and want to
 set the RTC to the current value, you can use the function:
    int RTCSetRTCfromSystemTime()
 -------------------------------------------------------------------*/
void SetTimeRTC()
{
   /* Synchronize the RTC with the system time. */
   #if ( !defined PK70 && !defined SB70LC && !defined CB34EX && !defined NANO54415 && !defined MOD5441X )
   int n = RTCSetSystemFromRTCTime();
   #else
   int n = 1;
   #endif
   if ( n == 0 )
   {
      iprintf( "Set system time from RTC\r\n" );
   }
   else
   {
      iprintf( "Error: could not set system time from RTC\r\n" );
   }
}


/*-------------------------------------------------------------------
  DisplaySystemTime
 -------------------------------------------------------------------*/
 void DisplaySystemTime()
 {
    time_t RawTime;
    struct tm *TimeInfo;

    time( &RawTime );  // Get system time in time_t format
    TimeInfo = localtime( &RawTime );  // Convert to struct tm format
    iprintf("Current time: %s\r\n", asctime( TimeInfo ) );

    // Example of strftime() usage
    char buf[80];
    /* size_t strftime(char *s,
                       size_t maxsize,
                       const char *format,
                       const struct tm *timp);
    */
    strftime( buf, 79, "%l:%M:%S %p", TimeInfo );
    iprintf("Formatted time string: %s\r\n", buf );
}




#include <sys/types.h>
#include <sys/time.h>


/*-------------------------------------------------------------------
  SetTimeZone
 -------------------------------------------------------------------*/
void WasSetTimeZone( int hour_offset, int isdst )
{
	   _timezone =hour_offset*3600; 
	   _daylight =(isdst!=0);
	   _tzname[0] = "USER";
	   _tzname[1] = "USER";

}

void SetTimeZone( int hour_offset, int isdst )
{
    // This function is deprecated. Use tzsetchar for proper timezone management
    WasSetTimeZone(hour_offset,isdst);
}


