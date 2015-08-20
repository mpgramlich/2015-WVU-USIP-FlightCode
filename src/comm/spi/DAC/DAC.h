/*
 * DAC.h
 *
 *  Created on: May 31, 2015
 *      Author: Matt Gramlich
 */

#ifndef DAC_H_
#define DAC_H_

#include "../../../../Definitions.h"

#include <dspi.h>
#include <pins.h>
#include "DACTable.h"

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

class DAC {
public:
	BYTE dspiChannel;
	OS_SEM SPISEM;

	DAC(int dspiChannelInput);
	virtual ~DAC();

	void DAC_Read_Task(void * data);

	//do NOT send (int32_t)4719617 or (Binary) 10010000000010000000001
	inline int writePos(int positionInTable)
	{
		return DSPIStart(dspiChannel, &DACTable::table[positionInTable], NULL,
							3, &SPISEM, false, DEASSERT_AFTER_LAST, FALSE);
	}

	inline int zeroDacOutput()
	{
		return DSPIStart(dspiChannel, DACTable::zeroVoltage, NULL,
		        			3, &SPISEM, false, DEASSERT_AFTER_LAST, FALSE);
	}
};

#endif /* DAC_H_ */
