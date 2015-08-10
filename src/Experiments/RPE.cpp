/*
 * RPE.cpp
 *
 *  Created on: Aug 3, 2015
 *      Author: Matt Gramlich
 */

#include "RPE.h"

mail::mail_t RPE::package[RPE_NUM_OF_BUFFERS];
RPE::RPESerialMsg_t RPE::letter[RPE_NUM_OF_BUFFERS];
int RPE::selectedBuffer = 0;
uint16_t RPE::experiementRunCount = 0;

int RPE::runExperiment(ADC* adc, Synth* synth)
{
	int ret = 0;
	selectNextBuffer();
	if(selectedBuffer >= 0)
	{
		int dataPos = 0;
		for(int j = 0; j < SynthTable::numOfPositions; j++)
		{
			int i;
			SynthTable::currentPosition = j * 5;
			synth->writePos(SynthTable::currentPosition);
			for(i = 0; i < NUM_OF_SAMPLES_PER_FREQ; i++)
			{
				throttle->startStopwatch(THROTTLE_TIME_TICKS);
				//RGPIO::pRGPIO_BAR[RGPIO_TOG] = RGPIO_0; //testing pulses
				adc->readAllPtr(letter[selectedBuffer].msg.data[dataPos].adcReading);
				letter[selectedBuffer].msg.data[dataPos].clock_reg_count = timer->readLow();
				letter[selectedBuffer].msg.data[dataPos].clock_reg_reset_count = (uint16_t)timer->readHigh();
				letter[selectedBuffer].msg.data[dataPos].footer = DATA_END_FOOTER;
				OSSemPend(&adc->SPISEM, 0);
				//RGPIO::pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
				throttle->busyPendStopwatch();
				dataPos++;
			}
		}
		letter[selectedBuffer].msg.H1 = MSG_HEADER;
		letter[selectedBuffer].msg.counter = selectedBuffer;
		letter[selectedBuffer].msg.experiment = RPE_EXPERIMENT;
		letter[selectedBuffer].msg.datalength = dataPos;
		letter[selectedBuffer].msg.databegin = DATA_BEGIN_HEADER;
		package[selectedBuffer].data = letter[selectedBuffer].serialData;
		package[selectedBuffer].length = dataPos * sizeof(RPE::data_t) + 14;
		Serial_IO::postToQueue((void*) &package[selectedBuffer]);
	}
	else
	{
		ret = -1;
	}
	return ret;
}
