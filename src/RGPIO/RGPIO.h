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

static volatile PWORD pRGPIO_BAR = (PWORD) RGPIO_BAR;

extern OS_SEM PITSem;
extern OS_SEM waitTaskStart;

namespace RGPIO {

	void gpioWaitTask(void * pd);

	void SetupRGPIO();

}

#endif /* RGPIO_H_ */
