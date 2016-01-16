/*
 * RPE.cpp
 *
 *  Created on: Aug 3, 2015
 *      Author: Matt Gramlich
 */

#include "RPE.h"

mail::mail_t RPE::package[RPE_NUM_OF_BUFFERS];
RPE::RPESerialMsg_t RPE::letter[RPE_NUM_OF_BUFFERS];
int RPE::selectedBuffer = RPE_NUM_OF_BUFFERS - 1;
uint16_t RPE::experimentRunCount = 1;

int RPE::runExperiment(ADC* adc, Synth* synth)
{
	int ret = 0;
	selectNextBuffer();
	if(selectedBuffer >= 0)
	{
		int i;
		int dataPos = 0;
		BYTE VCOStatus = 0;
		RGPIO::setMuxRPE();

		for (i = 0; i < NUM_OF_SAMPLES_PER_FREQ; i++)
		{
			throttle->startStopwatch(THROTTLE_TIME_TICKS);
			adc->readAllPtr(letter[selectedBuffer].msg.data[dataPos].adcReading);
			letter[selectedBuffer].msg.data[dataPos].clock_reg_count = timer->readLow();
			letter[selectedBuffer].msg.data[dataPos].clock_reg_reset_count = (uint16_t) timer->readHigh();
			letter[selectedBuffer].msg.data[dataPos].sampleNum = i;
			letter[selectedBuffer].msg.data[dataPos].synthTablePosition = 0;
			letter[selectedBuffer].msg.data[dataPos].footer = DATA_END_FOOTER;
			OSSemPend(&adc->SPISEM, 0);
			throttle->busyPendStopwatch();
			dataPos++;
		}

		VCOStatus = MCP23017::enableVCO();
		throttle->startStopwatch(THROTTLE_TIME_TICKS * 2);
		throttle->busyPendStopwatch();

		for(int j = 0; j < SynthTable::numOfPositions; j++)
		{
			SynthTable::currentPosition = j * 5;
			synth->writePos(SynthTable::currentPosition);
			for(i = 0; i < NUM_OF_SAMPLES_PER_FREQ; i++)
			{
				throttle->startStopwatch(THROTTLE_TIME_TICKS);
				//RGPIO::pRGPIO_BAR[RGPIO_TOG] = RGPIO_0; //testing pulses
				adc->readAllPtr(letter[selectedBuffer].msg.data[dataPos].adcReading);
				letter[selectedBuffer].msg.data[dataPos].clock_reg_count = timer->readLow();
				letter[selectedBuffer].msg.data[dataPos].clock_reg_reset_count = (uint16_t)timer->readHigh();
				letter[selectedBuffer].msg.data[dataPos].sampleNum = (uint8_t)i;
				letter[selectedBuffer].msg.data[dataPos].synthTablePosition = (uint8_t)j + (uint8_t)1;
				letter[selectedBuffer].msg.data[dataPos].footer = DATA_END_FOOTER;
				OSSemPend(&adc->SPISEM, 0);
				//RGPIO::pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
				throttle->busyPendStopwatch();
				dataPos++;
			}
		}
		letter[selectedBuffer].msg.H1 = MSG_HEADER;
		letter[selectedBuffer].msg.counter = experimentRunCount;
		letter[selectedBuffer].msg.experiment = RPE_EXPERIMENT;
		letter[selectedBuffer].msg.VCOStat = VCOStatus;
		letter[selectedBuffer].msg.bufnum = selectedBuffer;
		letter[selectedBuffer].msg.datalength = dataPos;
		letter[selectedBuffer].msg.databegin = DATA_BEGIN_HEADER;
		package[selectedBuffer].data = letter[selectedBuffer].serialData;
		package[selectedBuffer].length = dataPos * sizeof(RPE::data_t) + RPE_MSG_SIZE_MINUS_DATA;
		experimentRunCount++;
		Serial_IO::postToQueue((void*) &package[selectedBuffer]);
		MCP23017::disableVCO();

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
