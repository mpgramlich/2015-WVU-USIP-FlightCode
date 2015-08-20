/*
 * Serial_IO.h
 *
 *  Created on: Mar 26, 2015
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

#ifndef SERIAL_IO_H_
#define SERIAL_IO_H_

#include "../../../Definitions.h"

#include <iosys.h>
#include <serial.h>
#include <pins.h>
#include <stdarg.h>
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
		//SerialClose(1);
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

	inline void debugPrintUart(int *fileDesc, const char *format, ...)
	{
		int rv;
		char printBuffer[255];
		va_list arg_ptr;
		va_start(arg_ptr, format);
		rv = vsnprintf(printBuffer, 255, format, arg_ptr);
		va_end(arg_ptr);
		if (rv)
		{
			writeall(*fileDesc, printBuffer, rv);
		}
	}

}

#endif /* SERIAL_IO_H_ */
