/*
 * Serial_IO.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: Matt Gramlich
 */

#include "Serial_IO.h"

int Serial_IO::serialFd[9];
OS_Q Serial_IO::SerialQueue;
void * Serial_IO::queueData[QUEUE_SIZE];

int Serial_IO::SerialRxFlush(int fd)
{
	//static char buf[2048];
	if (dataavail(fd))
		return read(fd, NULL, 2048);
	return 0;
}

void Serial_IO::SerialWriteTask(void * pd)
{
	BYTE err;
	mail::mail_t* datamsg;
	while(true)
	{
		datamsg = (mail::mail_t*)OSQPend(&SerialQueue, 0, &err);
		if(err == OS_NO_ERR || err == OS_Q_FULL)
		{
			Serial_IO::writePend(&Serial_IO::serialFd[2], datamsg->data, datamsg->length);
		}
		//datamsg->inUse = FALSE;
		err = 0;
	}
}

int Serial_IO::StartSerialWriteTask()
{
	int ret = 0;
	ret = OSQInit(&SerialQueue, queueData, QUEUE_SIZE);
	if(ret != OS_NO_ERR)
	{
		return ret;
	}
	OSSimpleTaskCreatewName(Serial_IO::SerialWriteTask, SERIAL_WRITE_TASK_PRIO, "Serial Write Task");
	return 0;
}

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
