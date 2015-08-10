/*
 * RGPIO.h
 *
 *  Created on: May 30, 2015
 *      Author: Matt Gramlich
 */

#ifndef RGPIO_H_
#define RGPIO_H_

#include "../../Definitions.h"
#include <HiResTimer.h>
#include <ucos.h>

extern OS_SEM PITSem;
extern OS_SEM BamaTaskStart;

namespace RGPIO {

	void gpioWaitTask(void * pd);

	void bamaWait();

	void SetupRGPIO();

	extern volatile PWORD pRGPIO_BAR;
	extern BYTE val0;
	extern BYTE val1;
	extern BYTE val2;
	extern BYTE val3;
	BYTE inline setPin(int num, BYTE val);
}

BYTE inline RGPIO::setPin(int num, BYTE val)
{
	DEBUG_PRINT_NET("enternet\r\n");
	switch (num)
	{
		case 0:
			if (val != val0)
			{
				DEBUG_PRINT_NET("%d\r\n", num);
				pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
				val0 ^= 1;
			}
			return val0;
		case 1:
			if (val != val1)
			{
				DEBUG_PRINT_NET("%d\r\n", num);
				pRGPIO_BAR[RGPIO_TOG] = RGPIO_1;
				val1 ^= 1;
			}
			return val1;
		case 2:
			if (val != val2)
			{
				DEBUG_PRINT_NET("%d\r\n", num);
				pRGPIO_BAR[RGPIO_TOG] = RGPIO_2;
				val2 ^= 1;
			}
			return val2;
		case 3:
			if (val != val3)
			{
				iprintf("%d\r\n", num);
				pRGPIO_BAR[RGPIO_TOG] = RGPIO_3;
				val3 ^= 1;
			}
			return val3;
	}
}

#endif /* RGPIO_H_ */
