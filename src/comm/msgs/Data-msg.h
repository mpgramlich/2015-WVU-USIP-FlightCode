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
*/

	struct __attribute__((packed)) msg_t
	{
		uint32_t H1;
		uint8_t counter;
		uint8_t experiment; //0 idle, 1 Langmuir Probe, EFX, Radio Plasma, Triple Probe, 0xff Exp Start
		uint32_t databegin;
		uint32_t clock_reg_count;
		uint32_t clock_reg_reset_count;
		uint8_t F1;
	};

	struct __attribute__((packed)) msglarge_t
	{
		uint32_t H1;
		uint8_t counter;
		uint8_t experiment; //0 idle, 1 Langmuir Probe, EFX, Radio Plasma, Triple Probe
		uint32_t databegin;
		uint32_t clock_reg_count;
		uint32_t clock_reg_reset_count;
		uint8_t F1;
	};

	const int size = sizeof(msg_t);
	const int sizelarge = sizeof(msglarge_t);

	union dataMsg_t {
		msg_t msg;
		BYTE data[size+3];
		char serialData[size+3];
	};

	union dataMsgLarge_t {
		msglarge_t msg;
		BYTE data[sizelarge+3];
		char serialData[sizelarge+3];
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
		for(uint16_t i = 3; i < size - 1; i++)
		{
			checksum = (checksum + static_cast<uint8_t>(LE[i])) & 255;
		}
		return checksum;
	}
};

#endif
