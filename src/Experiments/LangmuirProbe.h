/*
 * LangmuirProbe.h
 *
 *  Created on: Aug 3, 2015
 *      Author: Matt Gramlich
 */

#ifndef LANGMUIRPROBE_H_
#define LANGMUIRPROBE_H_

#define THROTTLE_TIME_TICKS 120000 //stopwatch count to value, one tick = 1/125000000 seconds

#include "../../Definitions.h"
#include "../comm/msgs/Data-msg.h"
#include "../comm/msgs/Mailbox-msg.h"
#include "../comm/serial/Serial_IO.h"
#include "../comm/spi/ADC/ADC.h"
#include "../comm/spi/DAC/DAC.h"
#include "../comm/spi/DAC/DACTable.h"
#include "../RGPIO/RGPIO.h"

namespace LP
{
	struct __attribute__((packed)) data_t;
	struct __attribute__((packed)) LPmsg_t;
	union LPSerialMsg_t;

	extern mail::mail_t package[LP_NUM_OF_BUFFERS];
	extern LPSerialMsg_t letter[LP_NUM_OF_BUFFERS];
	extern int selectedBuffer;
	extern uint16_t experimentRunCount;

	//choose next available buffer,
	//toggle its inUse flag,
	//return its index in the buffer array
	//returns -1 if no buffer is available
	void inline selectNextBuffer()
	{
		selectedBuffer = LP_NUM_OF_BUFFERS - 1;
		for(; selectedBuffer >= 0; selectedBuffer--)
		{
			if(package[selectedBuffer].inUse == FALSE)
			{
				package[selectedBuffer].inUse = TRUE;
				break;
			}
		}
	}

	int runExperiment(ADC* adc, DAC* dac);

}; /* namespace LP */

struct __attribute__((packed)) LP::data_t
{
	uint16_t clock_reg_reset_count;
	uint32_t clock_reg_count;
	BYTE dacPosition;
	BYTE adcReading[3];
	BYTE footer;
};

#define LP_MSG_SIZE_MINUS_DATA 15
struct __attribute__((packed)) LP::LPmsg_t
{
	uint32_t H1;
	uint16_t counter;
	uint16_t experiment; //0 idle, 1 Langmuir Probe, RPE, Radio Plasma, Triple Probe
	//uint8_t VCOStat;
	uint8_t bufnum;
	uint16_t datalength;
	uint32_t databegin;
	//uint16_t checksum;
	data_t data[240]; //this assumes a 2000Hz sample rate for 2.5 seconds
};

union LP::LPSerialMsg_t
{
	LPmsg_t msg;
	char serialData[sizeof(LPmsg_t)];
};


#endif /* LANGMUIRPROBE_H_ */
