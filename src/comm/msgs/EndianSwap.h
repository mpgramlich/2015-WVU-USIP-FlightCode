/*
 * EndianSwap.h
 *
 *  Created on: Feb 24, 2015
 *      Author: Matt Gramlich
 *
 */
#ifndef ENDIAN_SWAP_H
#define ENDIAN_SWAP_H

#include "../../../Definitions.h"
#include <stdint.h>


namespace EndianSwap
{
	inline void changeToBigEndian(BYTE* littleData, BYTE* bigData, const int* size)
	{
		for(int i = 0; i < *size; i++)
		{
			bigData[i] = littleData[*size-i-1];
		}
	}

	inline void changeToLittleEndian(BYTE* littleData, BYTE* bigData, const int* size)
	{
		for(int i = 0; i < *size; i++)
		{
			littleData[i] = bigData[*size-i-1];
		}
	}
}

#endif
