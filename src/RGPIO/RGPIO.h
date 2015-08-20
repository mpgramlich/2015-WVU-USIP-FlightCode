/*
 * RGPIO.h
 *
 *  Created on: May 30, 2015
 *      Author: Matt Gramlich
 */
 
 /*
The MIT License (MIT)

Copyright (c) 2015 Matthew Gramlich

Permission is hereby granted, free of charge, 
to any person obtaining a copy of this software 
and associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, 
copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit 
persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission
notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT 
WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

	void inline setMuxLP()
	{
		setPin(A0, FALSE);
		setPin(A1, FALSE);
	}
	void inline setMuxRPE()
	{
		setPin(A0, FALSE);
		setPin(A1, TRUE);
	}
	void inline setMuxEFX()
	{
		setPin(A0, TRUE);
		setPin(A1, FALSE);
	}
	void inline resetSynth()
	{
		setPin(SYNTH_RESET, FALSE);
		setPin(SYNTH_RESET, TRUE);
		setPin(SYNTH_RESET, FALSE);
	}
}

BYTE inline RGPIO::setPin(int num, BYTE val)
{
	DEBUG_PRINT_NET("entered setPin\r\n");
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
	return -1;
}

#endif /* RGPIO_H_ */
