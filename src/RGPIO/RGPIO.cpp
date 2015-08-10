/*
 * RGPIO.cpp
 *
 *  Created on: May 30, 2015
 *      Author: Matt Gramlich
 */
#include "RGPIO.h"

volatile PWORD RGPIO::pRGPIO_BAR = (PWORD) RGPIO_BAR;
BYTE RGPIO::val0 = FALSE;
BYTE RGPIO::val1 = FALSE;
BYTE RGPIO::val2 = FALSE;
BYTE RGPIO::val3 = FALSE;

void RGPIO::gpioWaitTask(void * pd)
{
#ifdef EnableBamaTask
	iprintf("waitTask started\r\n");
	OSSemPend(&BamaTaskStart, 0);
	InitPitOSSem(1, &PITSem, EnableBamaTask);
	while(1)
	{
		OSSemPend(&PITSem,0);
		DEBUG_PRINT_NET("output\r\n");
		USER_ENTER_CRITICAL();
			//heres where we disable all other experiments
		timer->pollingDelay(.002);
		asm("nop");
		pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
		//timer->pollingDelay(.001);
		timer->pollingDelay(.100);
		pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
		USER_EXIT_CRITICAL();
	}
#endif
}

void RGPIO::bamaWait()
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
	Pins[TDIP_PIN].function(PIN_12_GPIO);
	Pins[TDIP_PIN] = 0;
	Pins[MUX_A0].function(PIN_21_GPIO);
	Pins[MUX_A0] = 0;
	Pins[MUX_A1].function(PIN_23_GPIO);
	Pins[MUX_A1] = 0;
    // Enable processor access to the RGPIO module
	asm(" move.l #0x8C000035,%d0");  // All bits fixed except bit 0, set to 1 to enable
	asm(" movec %d0,#0x009");        // Use movec to write to control register

	pRGPIO_BAR[RGPIO_DIR] = RGPIO_0 | RGPIO_2 | RGPIO_3;    // Set RGPIO to be an output
   	pRGPIO_BAR[RGPIO_ENB] = RGPIO_0 | RGPIO_2 | RGPIO_3;    // Enable RGPIO pin

    // Set DSPI0 & One-Wire Slew Rate Control Register (SRCR_DSPIOW) to their maximum freq
   	sim1.gpio.srcr_dspiow = 0x33;

#ifdef EnableBamaTask
    OSSimpleTaskCreate(RGPIO::gpioWaitTask, BAMA_TASK_PRIO);
#endif

}



