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
