/*
 * Comm.h
 *
 *  Created on: Apr 10, 2015
 *      Author: Matt Gramlich
 */

#ifndef COMM_H_
#define COMM_H_

#include "../../../Definitions.h"

#include <ucos.h>
#include "../msgs/EndianSwap.h"

#include "../msgs/Data-msg.h"

#include "Serial_IO.h"

//#ifdef DEBUG_COMM__
//#define DEBUG_PRINT(args...) iprintf(args)
//#else
//#define DEBUG_PRINT(args...)
//#endif

namespace Comm
{
	//DWORD commStack[USER_TASK_STK_SIZE];

	//simple version of write task that only requires a function call to run
	void commWriteSerialMsg(void);

	//serial write task that runs on a Programmable Interrupt Timer
	//call startCommTask() to start the serial write task
	void commWriteTask(void*);

	BYTE startCommTask(); //UDP Write and Serial Write are in the same Task
						  //UDP  Read and Serial  Read are in different Tasks
						  //UDP Read is higher Priority than Serial Read

}

#endif /* COMM_H_ */
