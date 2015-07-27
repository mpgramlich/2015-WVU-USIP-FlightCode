/*
 * NBtoI7msg.h
 *
 *  Created on: March 2, 2015
 *      Author: Matt Gramlich
 */
#ifndef DATAMSG_H
#define DATAMSG_H

//#include "../../../Definitions.h"

#include "EndianSwap.h"

//externally linked union types are defined at the bottom

namespace DataMsg
{
/*
Do not use pointers to access this struct's data, pointers to data members
	do not necessarily inherit the ((packed)) attribute
Do not use this struct else where, this struct is already initialized
	below in the union as msg.
Include this header and write to msg below, send data by using the
	array 'data'
*/

	struct __attribute__((packed)) msg_t
	{
		uint32_t H1;
		uint8_t counter;
		uint8_t experimentRunning; //0 idle
		uint32_t clock_reg_count;
		uint32_t clock_reg_reset_count;
		uint8_t checksum;
	};

	const int size = sizeof(msg_t);

	 union bigEndianMsg_t {
		msg_t msg;
		BYTE data[size+3];
		char dataC[size+3];
	};

	 union littleEndianData_t {
		BYTE littleEndianData[size+3];
		char littleEndianDataChar[size+3];
	};

	inline void copyDataChangeEndian(BYTE* LE, BYTE* BE, const int* length)
	{
		EndianSwap::changeToLittleEndian(LE, BE, length);
	}

	inline BYTE doChecksum(BYTE* LE, const int* length)
	{
		BYTE checksum = 0;
		for(uint8_t i = 3; i < size - 1; i++)
		{
			checksum = (checksum + static_cast<uint8_t>(LE[i])) & 255;
		}
		return checksum;
	}
};

extern DataMsg::bigEndianMsg_t datamsg;
extern DataMsg::littleEndianData_t datamsgl;

#endif
