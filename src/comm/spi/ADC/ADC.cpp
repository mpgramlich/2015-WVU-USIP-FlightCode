/*
 * ADC.cpp
 *
 *  Created on: May 31, 2015
 *      Author: Matt Gramlich
 */

#include "ADC.h"

ADC::ADC(int dspiChannelInput) {



	int SPIPins[12] = { 33, 35, 15, 31,  //SPI1
						24, 26, 28, 30,  //SPI2
						32, 34, 36, 38}; //SPI3
	Pins[SPIPins[(dspiChannelInput - 1) * 4 + 0]].function(1); //SPI Input
	Pins[SPIPins[(dspiChannelInput - 1) * 4 + 1]].function(1); //SPI Out
	Pins[SPIPins[(dspiChannelInput - 1) * 4 + 2]].function(1); //SPI chip select 0
	Pins[SPIPins[(dspiChannelInput - 1) * 4 + 3]].function(1); //SPI clock

	dspiChannel = dspiChannelInput;
	/*
	for (int i = 0; i < size; i++)
		table[i] = 0;
	*/

	OSSemInit(&SPISEM, 0);

	DSPIInit(dspiChannel, ADCdspiBaudRate, ADCtransferSizeBits, ADCChipSelects,
			 ADCCSPolarityIdle, ADCClockPolarity, 1, 1, 100, 0, false);

}

ADC::~ADC() {

}

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
