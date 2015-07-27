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

#ifdef DEBUG_SERIAL_IO__
#include <stdio.h>
#endif

namespace Serial_IO {
	static int serialFd[6];

	//void startSerialReadTask();
	void serialReadTask(void * pd);

	int SerialRxFlush(int fd);

	inline void initSerial()
	{

	#ifdef DEBUG_SERIAL_IO__
		iprintf("Initializing Serial\n");
	#endif

		SerialClose(2);

		Pins[16].function(PIN_16_UART2_TXD); //TX 2
		Pins[13].function(PIN_13_UART2_RXD); //PWM
		serialFd[2] = OpenSerial(2, 115200, 1, 8, eParityNone);
		Pins[13].function(PIN_13_PWM_A3); //PWM

		SerialClose(9);
//		J2[44].function(2); //TX 9
//		J2[41].function(2); //RX 9
		serialFd[6] = OpenSerial(9, 115200, 1, 8, eParityNone);

	#ifdef DEBUG_SERIAL_IO__
		iprintf("Leaving Serial Init\n");
	#endif
	}

	inline int writePend(int* fileDesc, char* data, const int length)
	{
	#ifdef OLD_SERIAL_TRANSMIT
		for(int i = 0; i < 57; i++)
		{
			write(*fileDesc, &data[i], 1);
		}
	#else
		//writeall returns length if succesful
		//or negative if error,
		//TODO do something on error?
		return writeall(*fileDesc, data, length);
	#endif

	#ifdef DEBUG_SERIAL_IO__
		iprintf("Printing to Serial Port\n");
		for(int i = 0; i < 57; i++)
		{
			iprintf("%2x ", data[i]);
		}
	#endif
		//return 0;
	}

};

#endif /* SERIAL_IO_H_ */
