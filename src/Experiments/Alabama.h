/*
 * BAMA.h
 *
 *  Created on: Aug 3, 2015
 *      Author: Matt Gramlich
 */

#ifndef BAMA_H_
#define BAMA_H_

#include "../../Definitions.h"
#include "../comm/msgs/Data-msg.h"
#include "../comm/msgs/Mailbox-msg.h"
#include "../comm/serial/Serial_IO.h"
#include "../comm/spi/ADC/ADC.h"
#include "../comm/spi/Synth/Synth.h"
#include "../comm/i2c/MCP23017/MCP23017.h"
#include "../RGPIO/RGPIO.h"

#define TIMER_TICKS 125000 //stopwatch count to value, one tick = 1/125000000 seconds

namespace BAMA
{
	struct __attribute__((packed)) data_t;
	struct __attribute__((packed)) BAMAmsg_t;
	union BAMASerialMsg_t;

	extern mail::mail_t package[BAMA_NUM_OF_BUFFERS];
	extern BAMASerialMsg_t letter[BAMA_NUM_OF_BUFFERS];
	extern int selectedBuffer;
	extern uint16_t experimentRunCount;

	//choose next available buffer,
	//toggle its inUse flag,
	//return its index in the buffer array
	//returns -1 if no buffer is available
	void inline selectNextBuffer()
	{
		selectedBuffer = BAMA_NUM_OF_BUFFERS - 1;
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

}; /* namespace BAMA */

struct __attribute__((packed)) BAMA::data_t
{
	uint16_t clock_reg_reset_count;
	uint32_t clock_reg_count;
	BYTE sampleNum;
	BYTE synthTablePosition;
	BYTE adcReading[3];
	BYTE footer;
};

#define BAMA_MSG_SIZE_MINUS_DATA 15
struct __attribute__((packed)) BAMA::BAMAmsg_t
{
	uint32_t H1;
	uint16_t counter;
	uint16_t experiment; //0 idle, 1 Langmuir Probe, BAMA, Radio Plasma, Triple Probe
	//uint8_t VCOStat;
	uint8_t bufnum;
	uint16_t datalength;
	uint32_t databegin;
	//uint16_t checksum;
	data_t data[500];
};

union BAMA::BAMASerialMsg_t
{
	BAMAmsg_t msg;
	char serialData[sizeof(BAMAmsg_t)];
};

#endif /* BAMA_H_ */
