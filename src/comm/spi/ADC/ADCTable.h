/*
 * ADCTable.h
 *
 *  Created on: Apr 4, 2015
 *      Author: Matt
 */

#ifndef ADCTABLE_H_
#define ADCTABLE_H_

#include "../../../../Definitions.h"

namespace ADCTable
{
	static const int size = ADCTableSize;

	static volatile uint8_t __attribute__ ((aligned(2))) table[size*3] = { 0 }; //samples * 3 bytes each
	static volatile int32_t __attribute__ ((aligned(2))) outputCodeTable[size] = { 0 };


	//static volatile int32_t timeTable[size*3] = { 0 };
}

#endif /* ADCTABLE_H_ */
