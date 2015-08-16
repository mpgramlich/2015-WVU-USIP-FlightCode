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
	MCP23017::enableVCO();
	RGPIO::setMuxRPE();
	RGPIO::bamaWait();

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
			OSTimeDly(3*20);
		}

	}
	else
	{
		ret = -1;
	}
	MCP23017::disableVCO();
	return ret;
}
