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
#include <pins.h>
#include "DACTable.h"

class DAC {
public:
	BYTE dspiChannel;
	OS_SEM SPISEM;

	DAC(int dspiChannelInput);
	virtual ~DAC();

	void DAC_Read_Task(void * data);

	//do NOT send (int32_t)4719617 or (Binary) 10010000000010000000001
	inline int writePos(int positionInTable, int numToWrite)
	{
		return DSPIStart(dspiChannel, &DACTable::table[positionInTable], NULL,
							3, &SPISEM, false, DEASSERT_AFTER_LAST, FALSE);
	}
};

#endif /* DAC_H_ */
