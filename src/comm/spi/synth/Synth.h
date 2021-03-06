/*
 * Synth.h
 * For use with the AD9850
 *  Created on: May 31, 2015
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

#ifndef SYNTH_H_
#define SYNTH_H_

#include "../../../../Definitions.h"

#include <dspi.h>
#include <pins.h>
#include "SynthTable.h"

//refclock = 100MHz
//freqOut = 32BitWord * Refclock / 2^32
//32BitWord = (freqOut / refClock) * 2^32

class Synth {
public:
	BYTE dspiChannel;
	OS_SEM SPISEM;

	Synth(int dspiChannelInput);
	virtual ~Synth();

	void Synth_Read_Task(void * data);

	void testOutput();

	inline int writePos(int positionInTable)
	{
		return DSPIStart(dspiChannel, &SynthTable::table[positionInTable], NULL,
							5, &SPISEM, false, DEASSERT_AFTER_LAST, TRUE);
	}

	inline uint32_t genTestWord(double freq) __attribute__((unused))
	{
		return freq * 4294967296.0 / 125000000;
	}
};

#endif /* SYNTH_H_ */
