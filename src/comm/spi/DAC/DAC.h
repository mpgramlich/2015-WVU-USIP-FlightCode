/*
 * DAC.h
 *
 *  Created on: May 31, 2015
 *      Author: Matt Gramlich
 */

#ifndef DAC_H_
#define DAC_H_

#include "../../../../Definitions.h"

#include <dspi.h>
#include "DACTable.h"

class DAC {
public:
	BYTE dspiChannel;
	OS_SEM SPISEM;

	DAC(int dspiChannelInput);
	virtual ~DAC();

	void DAC_Read_Task(void * data);
};

#endif /* DAC_H_ */
