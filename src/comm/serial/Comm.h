/*
 * Comm.h
 *
 *  Created on: Apr 10, 2015
 *      Author: Matt Gramlich
 */

#ifndef COMM_H_
#define COMM_H_

#include "../../../Definitions.h"


//#include <ucos.h>
#include "../msgs/EndianSwap.h"

//externally linked message semaphores
//extern OS_SEM I7toNB1Sem;
extern OS_SEM DataSem;

//#include "../WatchDog/WatchDog.h"
//#include "msgs/I7toNBmsg.h"
#include "../msgs/datamsg.h"

//externally linked message structures
extern DataMsg::bigEndianMsg_t datamsg;
extern DataMsg::littleEndianData_t datamsgl;

//extern I7toNB::bigEndianMsg_t I7toNB1msg;
//extern I7toNB::littleEndianData_t I7toNB1msgData;

//#include "UDP/UDP_IO.h"
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
