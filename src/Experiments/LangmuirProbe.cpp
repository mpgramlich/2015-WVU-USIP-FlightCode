/*
 * LangmuirProbe.cpp
 *
 *  Created on: Aug 3, 2015
 *      Author: Matt Gramlich
 */

#include "LangmuirProbe.h"

mail::mail_t LP::package[LP_NUM_OF_BUFFERS];
LP::LPSerialMsg_t LP::letter[LP_NUM_OF_BUFFERS];
int LP::selectedBuffer = 0;
uint16_t LP::experimentRunCount = 1;

int LP::runExperiment(ADC* adc, DAC* dac)
{
	RGPIO::setMuxLP();
	int ret = 0;
	selectNextBuffer();
	if(selectedBuffer >= 0)
	{
		int i;
		DACTable::currentPlace = 0;
		for(i = 0; i < NUM_OF_DAC_POS/2; i++)
		{
			dac->writePos(DACTable::currentPlace);
			letter[selectedBuffer].msg.data[i].dacPosition = (BYTE)i;
			OSSemPend(&dac->SPISEM, 0);
			adc->readAllPtr(letter[selectedBuffer].msg.data[i].adcReading);
			letter[selectedBuffer].msg.data[i].clock_reg_count = timer->readLow();
			letter[selectedBuffer].msg.data[i].clock_reg_reset_count = (uint16_t)timer->readHigh();
			letter[selectedBuffer].msg.data[i].footer = DATA_END_FOOTER;
			OSSemPend(&adc->SPISEM, 0);
			DACTable::currentPlace += 3;
		}
		letter[selectedBuffer].msg.H1 = MSG_HEADER;
		letter[selectedBuffer].msg.counter = experimentRunCount;
		letter[selectedBuffer].msg.experiment = LANGMUIR_P_EXPERIMENT;
		letter[selectedBuffer].msg.bufnum = selectedBuffer;
		letter[selectedBuffer].msg.datalength = i;
		letter[selectedBuffer].msg.databegin = DATA_BEGIN_HEADER;
		package[selectedBuffer].data = letter[selectedBuffer].serialData;
		package[selectedBuffer].length = i * sizeof(LP::data_t) + LP_MSG_SIZE_MINUS_DATA;
		experimentRunCount++;
		Serial_IO::postToQueue((void*) &package[selectedBuffer]);
	}
	else
	{
		ret = -1;
	}
	dac->zeroDacOutput();
	return ret;
}

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
