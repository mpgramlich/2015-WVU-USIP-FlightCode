/*
 * RGPIO.cpp
 *
 *  Created on: May 30, 2015
 *      Author: Matt Gramlich
 */
#include "RGPIO.h"

void RGPIO::gpioWaitTask(void * pd)
{
	iprintf("waitTask started\r\n");
	OSSemPend(&waitTaskStart, 0);
	InitPitOSSem(1, &PITSem, 1.0101);
	while(1)
	{
		OSSemPend(&PITSem,0);
		USER_ENTER_CRITICAL();
			//heres where we disable all other experiments
		timer->pollingDelay(.002);
		asm("nop");
		pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
		timer->pollingDelay(.001);
		pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
		USER_EXIT_CRITICAL();
	}
}

void inline RGPIO::bamaWait()
{
	USER_ENTER_CRITICAL();
	//heres where we disable all other experiments
	timer->pollingDelay(.002);
	asm("nop");
	pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
	timer->pollingDelay(.001);
	pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
	USER_EXIT_CRITICAL();
}

void RGPIO::SetupRGPIO()
{
   // Enable processor access to the RGPIO module
   asm(" move.l #0x8C000035,%d0");  // All bits fixed except bit 0, set to 1 to enable
   asm(" movec %d0,#0x009");        // Use movec to write to control register

   pRGPIO_BAR[RGPIO_DIR] = RGPIO_0;    // Set RGPIO to be an output
   pRGPIO_BAR[RGPIO_ENB] = RGPIO_0;    // Enable RGPIO pin

   // Set DSPI0 & One-Wire Slew Rate Control Register (SRCR_DSPIOW) to their maximum freq
   sim1.gpio.srcr_dspiow = 0x33;
}



