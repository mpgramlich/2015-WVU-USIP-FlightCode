/*
 * BAMA.cpp
 *
 *  Created on: Aug 3, 2015
 *      Author: Matt Gramlich
 */

#include "Alabama.h"

mail::mail_t BAMA::package[BAMA_NUM_OF_BUFFERS];
BAMA::BAMASerialMsg_t BAMA::letter[BAMA_NUM_OF_BUFFERS];
int BAMA::selectedBuffer = 0;
uint16_t BAMA::experimentRunCount = 1;

int BAMA::runExperiment(ADC* adc)
{

	int ret = 0;
	selectNextBuffer();
	if(selectedBuffer >= 0)
	{
		int i = 0;
		int dataPos = 0;
		BYTE VCOStatus = MCP23017::disableVCO();

		throttle->startStopwatch(TIMER_TICKS);
		RGPIO::setPin(TDIP, TRUE);
		do {
			adc->readAllPtr(letter[selectedBuffer].msg.data[dataPos].adcReading);
			letter[selectedBuffer].msg.data[dataPos].clock_reg_count = timer->readLow();
			letter[selectedBuffer].msg.data[dataPos].clock_reg_reset_count = (uint16_t) timer->readHigh();
			letter[selectedBuffer].msg.data[dataPos].sampleNum = i;
			letter[selectedBuffer].msg.data[dataPos].synthTablePosition = 0;
			letter[selectedBuffer].msg.data[dataPos].footer = DATA_END_FOOTER;
			OSSemPend(&adc->SPISEM, 0);
			dataPos++;
		}
		while(!((throttle->simTimer_->ter & 0x2) == 0x2));
		RGPIO::setPin(TDIP, FALSE);

		letter[selectedBuffer].msg.H1 = MSG_HEADER;
		letter[selectedBuffer].msg.counter = experimentRunCount;
		letter[selectedBuffer].msg.experiment = BAMA_EXPERIMENT;
		letter[selectedBuffer].msg.VCOStat = VCOStatus;
		letter[selectedBuffer].msg.bufnum = selectedBuffer;
		letter[selectedBuffer].msg.datalength = dataPos;
		letter[selectedBuffer].msg.databegin = DATA_BEGIN_HEADER;
		package[selectedBuffer].data = letter[selectedBuffer].serialData;
		package[selectedBuffer].length = dataPos * sizeof(BAMA::data_t) + BAMA_MSG_SIZE_MINUS_DATA;
		experimentRunCount++;
		Serial_IO::postToQueue((void*) &package[selectedBuffer]);

	}
	else
	{
		ret = -1;
	}
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
