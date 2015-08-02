/*
 * DAC.cpp
 *
 *  Created on: May 31, 2015
 *      Author: Matt Gramlich
 */

#include "DAC.h"

DAC::DAC(int dspiChannelInput) {

	int SPIPins[12] = { 33, 35, 15, 31,  //SPI1
						24, 26, 28, 30,  //SPI2
						32, 34, 36, 38}; //SPI3
	Pins[SPIPins[(dspiChannelInput - 1) * 4 + 0]].function(1); //SPI Input
	Pins[SPIPins[(dspiChannelInput - 1) * 4 + 1]].function(1); //SPI Out
	Pins[SPIPins[(dspiChannelInput - 1) * 4 + 2]].function(1); //SPI chip select 0
	Pins[SPIPins[(dspiChannelInput - 1) * 4 + 3]].function(1); //SPI clock

	dspiChannel = dspiChannelInput;

	OSSemInit(&SPISEM, 0);

	DSPIInit(dspiChannel, DACdspiBaudRate, DACtransferSizeBits, DACChipSelects,
			 DACCSPolarityIdle, DACClockPolarity, 1, 1, 1, 1, false);

}

DAC::~DAC() {
	// TODO Auto-generated destructor stub
}

