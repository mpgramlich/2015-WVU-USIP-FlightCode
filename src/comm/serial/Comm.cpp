/*
 * Comm.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: Matt Gramlich
 */

#include "Comm.h"

extern OS_SEM PITSem;

//See Serial_IO.h, initSerial for indexes
//#define SERIAL_INDEX_UART9 serialFd[1]
#define SERIAL_INDEX_UART2 serialFd[2]

#define LED_FLASH

void Comm::commWriteSerialMsg(void)
{
	datamsg.msg.H1 = 0xFFAAFF00;
	//datamsg.msg.H2 = 'z';


	//datamsg.msg.packet_num = '1';

	datamsg.msg.counter = 0;

	//this changes the endian of the message to little endian
	//and copys the data to a separate buffer for serial output
	DataMsg::copyDataChangeEndian(datamsgl.littleEndianData, datamsg.data,
			&DataMsg::size);

	datamsg.msg.counter++;

	//be sure to post the semaphore so that other functions can access the message
	//and avoid lockups
	//OSSemPost(&NB1toI7Sem);

	//perform the checksum on the little endian data
	datamsg.dataC[DataMsg::size - 1] = DataMsg::doChecksum(datamsg.data,
			&DataMsg::size);

	//write the little endian data
	Serial_IO::writePend(&Serial_IO::SERIAL_INDEX_UART2, datamsg.dataC,
			DataMsg::size);

/* //flash LED every 50 packets
#ifdef LED_FLASH
		if(datamsg.msg.pause_switch == (uint8_t)0xFF)
		{
			J2[48] = 1;
			J2[47] = 1;
		}
		else if(datamsg.msg.counter % 50 == 0)
		{
			J2[48] = J2[48] ^ 1;
			J2[47] = J2[47] ^ 1;
		}
#endif
*/

}

void Comm::commWriteTask(void* inputArg)
{
	datamsg.msg.H1 = 0xFFAAFF00;
	//datamsg.msg.H2 = 'z';


	//datamsg.msg.packet_num = '1';

	datamsg.msg.counter = 0;
	while(1)
	{
		//wait for Programmable Interrupt Timer to post semaphore
		OSSemPend(&PITSem, 100);

		//try to take semaphore for message to avoid half-write-read conditions
		OSSemPend(&DataSem, 100);

		
		//this changes the endian of the message to little endian
		//and copys the data to a separate buffer for serial output
		DataMsg::copyDataChangeEndian(datamsgl.littleEndianData,
										datamsg.data,
										&DataMsg::size);

		datamsg.msg.counter++;
		
		//be sure to post the semaphore so that other functions can access the message
		//and avoid lockups
		//OSSemPost(&NB1toI7Sem);

		//perform the checksum on the little endian data
		datamsg.dataC[DataMsg::size - 1] = DataMsg::doChecksum(datamsg.data,
																	&DataMsg::size);

		//write the little endian data
		Serial_IO::writePend(&Serial_IO::serialFd[2],
				datamsg.dataC, DataMsg::size);


/* //flash LED every 50 packets
#ifdef LED_FLASH
		if(datamsg.msg.pause_switch == (uint8_t)0xFF)
		{
			J2[48] = 1;
			J2[47] = 1;
		}
		else if(datamsg.msg.counter % 50 == 0)
		{
			J2[48] = J2[48] ^ 1;
			J2[47] = J2[47] ^ 1;
		}
#endif
*/

	}
}

BYTE Comm::startCommTask()
{
		//Serial_IO::initSerial();

		OSSimpleTaskCreatewName(Comm::commWriteTask, COMM_WRITE_TASK_PRIO, "Comm Write Task");

	    return 0;
}




