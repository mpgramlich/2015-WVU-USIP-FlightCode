/*
 * EndianSwap.h
 *
 *  Created on: Feb 24, 2015
 *      Author: Matt Gramlich
 *
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
