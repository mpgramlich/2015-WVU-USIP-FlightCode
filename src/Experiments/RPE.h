/*
 * RPE.h
 *
 *  Created on: Aug 3, 2015
 *      Author: Matt Gramlich
 */
 
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

#ifndef RPE_H_
#define RPE_H_

#include "../../Definitions.h"
#include "../comm/msgs/Data-msg.h"
#include "../comm/msgs/Mailbox-msg.h"
#include "../comm/serial/Serial_IO.h"
#include "../comm/spi/ADC/ADC.h"
#include "../comm/spi/Synth/Synth.h"
#include "../comm/i2c/MCP23017/MCP23017.h"
#include "../RGPIO/RGPIO.h"

#define NUM_OF_SAMPLES_PER_FREQ 15
#define THROTTLE_TIME_TICKS 120000 //stopwatch count to value, one tick = 1/125000000 seconds

namespace RPE
{
	struct __attribute__((packed)) data_t;
	struct __attribute__((packed)) RPEmsg_t;
	union RPESerialMsg_t;

	extern mail::mail_t package[RPE_NUM_OF_BUFFERS];
	extern RPESerialMsg_t letter[RPE_NUM_OF_BUFFERS];
	extern int selectedBuffer;
	extern uint16_t experimentRunCount;

	//choose next available buffer,
	//toggle its inUse flag,
	//return its index in the buffer array
	//returns -1 if no buffer is available
	void inline selectNextBuffer()
	{
		//selectedBuffer = RPE_NUM_OF_BUFFERS - 1;
		for(; selectedBuffer >= 0; selectedBuffer--)
		{
			if(package[selectedBuffer].inUse == FALSE)
			{
				package[selectedBuffer].inUse = TRUE;
				break;
			}
		}
	}

	int runExperiment(ADC* adc, Synth* synth);

}; /* namespace RPE */

struct __attribute__((packed)) RPE::data_t
{
	uint16_t clock_reg_reset_count;
	uint32_t clock_reg_count;
	BYTE sampleNum;
	BYTE synthTablePosition;
	BYTE adcReading[3];
	BYTE footer;
};

#define RPE_MSG_SIZE_MINUS_DATA 16
struct __attribute__((packed)) RPE::RPEmsg_t
{
	uint32_t H1;
	uint16_t counter;
	uint16_t experiment; //0 idle, 1 Langmuir Probe, RPE, Radio Plasma, Triple Probe
	uint8_t VCOStat;
	uint8_t bufnum;
	uint16_t datalength;
	uint32_t databegin;
	//uint16_t checksum;
	data_t data[800];
};

union RPE::RPESerialMsg_t
{
	RPEmsg_t msg;
	char serialData[sizeof(RPEmsg_t)];
};

#endif /* RPE_H_ */
