/*
 * DACTable.h
 *
 *  Created on: Apr 3, 2015
 *      Author: Matt Gramlich
 */

#ifndef DACTABLE_H_
#define DACTABLE_H_

#include <ucos.h>

namespace DACTable
{
	const int size = 2388;

	extern int currentPlace;
	extern BYTE table[size] __attribute__ ((aligned(2)));
}


#endif /* DACTABLE_H_ */
