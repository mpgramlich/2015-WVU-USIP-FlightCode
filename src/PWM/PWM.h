/*
 * PWM.h
 *
 *  Created on: Jun 15, 2015
 *      Author: Matt Gramlich
 */

#ifndef PWM_H_
#define PWM_H_

#include "../../Definitions.h"

namespace PWM
{
	//duty cycle = (off/reset)*100
	//125MHz/off/2/reset = frequency
	void initPWM(int pin, int16_t on, int16_t off, int16_t init, int16_t reset);

}

#endif /* PWM_H_ */

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
