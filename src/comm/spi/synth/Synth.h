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
#include "SynthTable.h"

class Synth {
public:
	BYTE dspiChannel;
	OS_SEM SPISEM;

	Synth(int dspiChannelInput);
	virtual ~Synth();

	void Synth_Read_Task(void * data);
};

#endif /* SYNTH_H_ */
