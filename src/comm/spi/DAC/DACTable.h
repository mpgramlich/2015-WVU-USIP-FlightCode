/*
 * DACTable.h
 *
 *  Created on: Apr 3, 2015
 *      Author: Matt Gramlich
 */

#ifndef DACTABLE_H_
#define DACTABLE_H_

#include <ucos.h>

#define NUM_OF_DAC_POS 292

namespace DACTable
{
	const int size = 876;
	extern BYTE zeroVoltage[3] __attribute__ ((aligned(2)));

	extern int currentPlace;
	extern BYTE table[size] __attribute__ ((aligned(2)));
}

#endif /* DACTABLE_H_ */
