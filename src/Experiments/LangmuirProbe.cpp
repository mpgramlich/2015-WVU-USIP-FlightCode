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
	int ret = 0;
	selectNextBuffer();
	if(selectedBuffer >= 0)
	{
		int i;
		DACTable::currentPlace = 0;
		for(i = 0; i < NUM_OF_DAC_POS/2; i++)
		{
			RGPIO::pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
			dac->writePos(DACTable::currentPlace);
			letter[selectedBuffer].msg.data[i].dacPosition = (BYTE)i;
			OSSemPend(&dac->SPISEM, 0);
			adc->readAllPtr(letter[selectedBuffer].msg.data[i].adcReading);
			letter[selectedBuffer].msg.data[i].clock_reg_count = timer->readLow();
			letter[selectedBuffer].msg.data[i].clock_reg_reset_count = (uint16_t)timer->readHigh();
			letter[selectedBuffer].msg.data[i].footer = DATA_END_FOOTER;
			OSSemPend(&adc->SPISEM, 0);
			RGPIO::pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
			DACTable::currentPlace += 3;
		}
		letter[selectedBuffer].msg.H1 = MSG_HEADER;
		letter[selectedBuffer].msg.counter = selectedBuffer;
		letter[selectedBuffer].msg.experiment = LANGMUIR_P_EXPERIMENT;
		letter[selectedBuffer].msg.datalength = i;
		letter[selectedBuffer].msg.databegin = DATA_BEGIN_HEADER;
		package[selectedBuffer].data = letter[selectedBuffer].serialData;
		package[selectedBuffer].length = i * sizeof(LP::data_t) + 14;
		Serial_IO::postToQueue((void*) &package[selectedBuffer]);
	}
	else
	{
		ret = -1;
	}
	return ret;
}
