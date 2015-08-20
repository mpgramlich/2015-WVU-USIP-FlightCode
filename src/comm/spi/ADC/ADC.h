/*
 * ADC.h
 *
 *  Created on: May 31, 2015
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
	//static const int size = ADCTableSize;
	//volatile uint8_t __attribute__ ((aligned(2))) table[size*3]; //samples * 3 bytes each
	//volatile int32_t __attribute__ ((aligned(2))) outputCodeTable[size];
	ADC(int dspiChannelInput);
	virtual ~ADC();

	void ADC_Read_Task(void * data);

	/*
	//position in the table
	inline int readAll(int position)
	{
		return DSPIStart(dspiChannel,NULL,&table[position],
								3,&SPISEM,false,DEASSERT_AFTER_LAST,FALSE);
	}
	*/

	inline int readAllPtr(BYTE* bufPtr)
	{
		return DSPIStart(dspiChannel,NULL,bufPtr,
							3,&SPISEM,false,DEASSERT_AFTER_LAST,FALSE);
	}
};

#endif /* ADC_H_ */
