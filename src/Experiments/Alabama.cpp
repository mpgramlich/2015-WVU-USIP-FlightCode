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
uint16_t BAMA::experiementRunCount = 0;

int BAMA::runExperiment(ADC* adc, Synth* synth)
{
	/*
	int ret = 0;
	selectNextBuffer();
	if(selectedBuffer >= 0)
	{
		int i;
		int dataPos = 0;
		BYTE VCOStatus = 0;
		//RGPIO::setMuxBAMA();

		for (i = 0; i < NUM_OF_SAMPLES_PER_FREQ; i++)
		{
			throttle->startStopwatch(THROTTLE_TIME_TICKS);
			//RGPIO::pRGPIO_BAR[RGPIO_TOG] = RGPIO_0; //testing pulses
			adc->readAllPtr(letter[selectedBuffer].msg.data[dataPos].adcReading);
			letter[selectedBuffer].msg.data[dataPos].clock_reg_count = timer->readLow();
			letter[selectedBuffer].msg.data[dataPos].clock_reg_reset_count = (uint16_t) timer->readHigh();
			letter[selectedBuffer].msg.data[dataPos].sampleNum = i;
			letter[selectedBuffer].msg.data[dataPos].synthTablePosition = 0;
			letter[selectedBuffer].msg.data[dataPos].footer = DATA_END_FOOTER;
			OSSemPend(&adc->SPISEM, 0);
			//RGPIO::pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
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
		letter[selectedBuffer].msg.counter = experiementRunCount;
		letter[selectedBuffer].msg.experiment = BAMA_EXPERIMENT;
		letter[selectedBuffer].msg.VCOStat = VCOStatus;
		letter[selectedBuffer].msg.bufnum = selectedBuffer;
		letter[selectedBuffer].msg.datalength = dataPos;
		letter[selectedBuffer].msg.databegin = DATA_BEGIN_HEADER;
		package[selectedBuffer].data = letter[selectedBuffer].serialData;
		package[selectedBuffer].length = dataPos * sizeof(BAMA::data_t) + 16;
		experiementRunCount++;
		Serial_IO::postToQueue((void*) &package[selectedBuffer]);
		MCP23017::disableVCO();

	}
	else
	{
		ret = -1;
	}
	return ret;
	*/
}
