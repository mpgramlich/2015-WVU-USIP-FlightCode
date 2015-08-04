/*
 * Serial_IO.h
 *
 *  Created on: Mar 26, 2015
 *      Author: Matt Gramlich
 */

#ifndef SERIAL_IO_H_
#define SERIAL_IO_H_

#include "../../../Definitions.h"

#include <iosys.h>
#include <serial.h>
#include <pins.h>
#include "../msgs/Mailbox-msg.h"

#ifdef DEBUG_SERIAL_IO__
#include <stdio.h>
#endif

#define QUEUE_SIZE 100

namespace Serial_IO
{
	extern void * queueData[QUEUE_SIZE];
	extern OS_Q SerialQueue;
	extern int serialFd[9];

	int SerialRxFlush(int fd);
	void SerialWriteTask(void * pd);
	int StartSerialWriteTask();

	inline BYTE postToQueue(void * msg)
	{
		return OSQPost( &SerialQueue, msg);
	}

	inline void initSerial()
	{
#ifdef DEBUG_SERIAL_IO__
		iprintf("Initializing Serial\n");
#endif
		//SerialClose(0);
		SerialClose(1);
		Pins[34].function(PIN_34_UART1_TXD); //TX 2
		Pins[32].function(PIN_32_UART1_RXD); //RX 2
		serialFd[1] = OpenSerial(1, 115200, 1, 8, eParityNone);

		SerialClose(2);
		Pins[16].function(PIN_16_UART2_TXD); //TX 2
		Pins[13].function(PIN_13_UART2_RXD); //RX 2
		serialFd[2] = OpenSerial(2, 115200, 1, 8, eParityNone);

		SerialClose(9);
//		serialFd[9] = OpenSerial(9, 115200, 1, 8, eParityNone);

#ifdef DEBUG_SERIAL_IO__
		iprintf("Leaving Serial Init\n");
#endif
	}

	inline int writePend(int* fileDesc, char* data, const int length)
	{
		//writeall returns length if succesful
		//or negative if error,
		//TODO do something on error?
		//printf("\nSerial 2 FD: %d\n", *fileDesc);
		return writeall(*fileDesc, data, length);
	}

}

#endif /* SERIAL_IO_H_ */
