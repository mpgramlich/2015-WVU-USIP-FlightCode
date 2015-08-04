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

}

#endif /* RGPIO_H_ */
