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


#ifndef _EFFS_TIME_H
#define _EFFS_TIME_H

// Set the system time using a Network Time Server
DWORD SetTimeNTP();

// Set the system time manually
void SetTimeManual( int month, int day, int weekday, int year, int hour, int min, int sec );

// Set the system time using a Real-Time clock
void SetTimeRTC();

void DisplaySystemTime();

// This function is deprecated. Use tzsetchar for proper timezone management
void SetTimeZone( int hour_offset, int isdst ) __attribute__((deprecated));
void WasSetTimeZone( int hour_offset, int isdst );



 extern "C"
{
   void tzsetchar(char * tzenv);
}



#endif   /* _EFFS_TIME_H */



