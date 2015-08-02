/*
 * ADC.h
 *
 *  Created on: May 31, 2015
 *      Author: Matt Gramlich
 */

#ifndef ADC_H_
#define ADC_H_

#include "../../../../Definitions.h"

#include <dspi.h>
#include <pins.h>
#include "ADCTable.h"

class ADC {
public:
	BYTE dspiChannel;
	OS_SEM SPISEM;
	static const int size = ADCTableSize;
	volatile uint8_t __attribute__ ((aligned(2))) table[size*3]; //samples * 3 bytes each
	volatile int32_t __attribute__ ((aligned(2))) outputCodeTable[size];
	ADC(int dspiChannelInput);
	virtual ~ADC();

	void ADC_Read_Task(void * data);

	//position in the table
	inline int readAll(int position)
	{
		return DSPIStart(dspiChannel,NULL,&table[position],
									3,&SPISEM,false,DEASSERT_AFTER_LAST,FALSE);
	}
};

#endif /* ADC_H_ */
