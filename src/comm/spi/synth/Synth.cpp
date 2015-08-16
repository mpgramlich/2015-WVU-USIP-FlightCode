/*
 * Synth.cpp
 *
 *  Created on: May 31, 2015
 *      Author: Matt Gramlich
 */

#include "Synth.h"


//lsb bit 0x800000
Synth::Synth(int dspiChannelInput) {

	dspiChannel = dspiChannelInput;
	OSSemInit(&SPISEM, 0);

	Pins[15].function(0); //FQ_UD
	Pins[31].function(0);  //CLK

	Pins[31] = 0;
	Pins[31] = 1;
	printf("init delay\n");
	OSTimeDly(20);
	Pins[31] = 0;
	printf("init delay\n");
	OSTimeDly(20);
	Pins[15] = 0;
	Pins[15] = 1;
	printf("init delay\n");
	OSTimeDly(20);
	Pins[15] = 0;

	OSTimeDly(20);

	Pins[15].function(PIN_15_DSPI1_PCS0); //FQ_UD
	Pins[31].function(PIN_31_DSPI1_SCK);  //CLK
	Pins[33].function(PIN_33_DSPI1_SIN);  //NA
	Pins[35].function(PIN_35_DSPI1_SOUT); //Data

	printf("DSPI Init %x\n",
			DSPIInit(SYNTHSPI, SYNTHdspiBaudRate, SYNTHtransferSizeBits,
				SYNTHCS, SYNTHCSPolarityIdle,
				1, 1, TRUE, 5, 5, TRUE));
}

void Synth::testOutput()
{
	union {
		uint32_t testnum;
		uint8_t blank[4];
	};
	testnum=0;
	uint8_t tx[5] = {0};
	uint8_t rx[5] = {0};
	tx[0] = 0xf0;
	tx[1] = 0;
	tx[2] = 0;
	tx[3] = 0;
	tx[4] = 0x00;
	OS_SEM test;
	OSSemInit(&test,0);

	//DSPIStart(SYNTHSPI, tx, rx, 5, &test, false, DEASSERT_AFTER_LAST, TRUE);

		testnum = Synth::genTestWord(1500000);
		//printf("in loops\n");
		if(DSPIStart(dspiChannel, tx, rx, 5, &test, false, DEASSERT_AFTER_LAST, TRUE) != 0)
			printf("Bus failure \n");
		OSSemPend(&test, 0);
		//timer->pollingDelay(.001);
		tx[0] = blank[3];
		tx[1] = blank[2];
		tx[2] = blank[1];
		tx[3] = blank[0];
		tx[4] = 0x00;

		OSTimeDly(60);

		testnum = Synth::genTestWord(0);
				//printf("in loops\n");
				if(DSPIStart(dspiChannel, tx, rx, 5, &test, false, DEASSERT_AFTER_LAST, TRUE) != 0)
					printf("Bus failure \n");
				OSSemPend(&test, 0);
				//timer->pollingDelay(.001);
				tx[0] = blank[3];
				tx[1] = blank[2];
				tx[2] = blank[1];
				tx[3] = blank[0];
				tx[4] = 0x00;

}

Synth::~Synth() {
	// TODO Auto-generated destructor stub
}

