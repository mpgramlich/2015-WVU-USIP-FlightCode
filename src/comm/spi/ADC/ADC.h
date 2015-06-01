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
#include "ADCTable.h"

class ADC {
public:
	BYTE dspiChannel;
	OS_SEM SPISEM;

	ADC(int dspiChannelInput);
	virtual ~ADC();

	void ADC_Read_Task(void * data);

	inline int readAll(int position)
	{
		return DSPIStart(dspiChannel,NULL,&ADCTable::table[position],
									4,&SPISEM,false,DEASSERT_AFTER_LAST);
	}
};

#endif /* ADC_H_ */
