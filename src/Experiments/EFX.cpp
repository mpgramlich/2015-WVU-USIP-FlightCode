/*
 * EFX.cpp
 *
 *  Created on: Aug 3, 2015
 *      Author: Matt Gramlich
 */

#include "EFX.h"

mail::mail_t EFX::package[EFX_NUM_OF_BUFFERS];
EFX::EFXSerialMsg_t EFX::letter[EFX_NUM_OF_BUFFERS];
int EFX::selectedBuffer = 0;
uint16_t EFX::experiementRunCount = 0;

void EFX::runExperiment(ADC* adc)
{
	selectNextBuffer();
	if(selectedBuffer >= 0)
	{
		int i;
		for(i = 0; i < NUM_OF_SAMPLES; i++)
		{
			throttle->startStopwatch(THROTTLE_TIME_TICKS);
			RGPIO::pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
			adc->readAllPtr(letter[selectedBuffer].msg.data[i].adcReading);
			letter[selectedBuffer].msg.data[i].clock_reg_count = timer->readLow();
			letter[selectedBuffer].msg.data[i].clock_reg_reset_count = timer->readHigh();
			OSSemPend(&adc->SPISEM, 0);
			RGPIO::pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
			throttle->busyPendStopwatch();
		}
		letter[selectedBuffer].msg.H1 = MSG_HEADER;
		letter[selectedBuffer].msg.counter = selectedBuffer;
		letter[selectedBuffer].msg.experiment = EFX_EXPERIMENT;
		letter[selectedBuffer].msg.datalength = i;
		letter[selectedBuffer].msg.databegin = DATA_BEGIN_HEADER;
		package[selectedBuffer].data = letter[selectedBuffer].serialData;
		package[selectedBuffer].length = i * sizeof(EFX::data_t) + 14;
		Serial_IO::postToQueue((void*) &package[selectedBuffer]);
	}
}