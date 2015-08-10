/*
 * Synth.h
 *
 *  Created on: May 31, 2015
 *      Author: Matt Gramlich
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

	inline uint32_t genTestWord(double freq)
	{
		return freq * 4294967296.0 / 125000000;
	}
};

#endif /* SYNTH_H_ */
