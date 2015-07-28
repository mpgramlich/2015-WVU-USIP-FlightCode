/*
 * Serial_IO.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: Matt Gramlich
 */

#include "Serial_IO.h"

int Serial_IO::serialFd[6];

void serialReadTask(void * pd)
{

};

int SerialRxFlush(int fd)
{
	//static char buf[2048];
	if (dataavail(fd))
		return read(fd, NULL, 2048);
	return 0;
};
