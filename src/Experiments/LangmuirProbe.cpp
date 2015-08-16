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
uint16_t LP::experiementRunCount = 0;

int LP::runExperiment(ADC* adc, DAC* dac)
{
	RGPIO::setMuxLP();
	int ret = 0;
	//selectNextBuffer();
	if(selectedBuffer >= 0)
	{
		int i;
		DACTable::currentPlace = 0;
		for(i = 0; i < NUM_OF_DAC_POS/2; i++)
		{
			dac->writePos(DACTable::currentPlace);
			OSSemPend(&dac->SPISEM, 0);
			DACTable::currentPlace += 3;
		}
	}
	else
	{
		ret = -1;
	}
	return ret;
}
