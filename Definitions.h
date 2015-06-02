/*
 * Definitions.h
 *
 *  Created on: May 29, 2015
 *      Author: Matt Gramlich
 *      			Greg Lusk
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include "predef.h"
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>
#include <autoupdate.h>
#include <smarttrap.h>
#include <taskmon.h>
#include <system.h>
#include <init.h>
#include <utils.h>
#include <stdlib.h>
#include <pins.h>
#include <pitr_sem.h>
#include <sim5441x.h>
#include <SysLog.h>
#include <NetworkDebug.h>
#include <HiResTimer.h>

//RGIO
	#define GPIO_PIN 12
	// Addresses of Rapid GPIO registers
	#define RGPIO_BAR 0x8C000000           // Base Address Register

	// Offsets to BAR when accessing registers as a 16-bit word array
	#define RGPIO_DIR (0)   // Data Dir Register
	#define RGPIO_DAT (1)   // Data Register
	#define RGPIO_ENB (2)   // Enable Register
	#define RGPIO_CLR (3)   // Clear
	#define RGPIO_SET (5)   // Set
	#define RGPIO_TOG (7)   // Toggle

	#define RGPIO_0 0x0001     // Pin 12

//HiResTimers
	static HiResTimer* timer = HiResTimer::getHiResTimer(2);

//ADC SPI
	#define ADCTableSize 100;

	#define ADCSPI 2
	#define ADCdspiBaudRate 10000
	#define ADCtransferSizeBits 24
	#define ADCChipSelects 0x0F
	#define ADCCSPolarityIdle 0x0E //Chip select polarity at idle
								//ADC Idle Low 0x0E
	#define ADCClockPolarity 0x00

//DAC SPI
	#define DACSPI 3
	#define DACdspiBaudRate 20000000
	#define DACtransferSizeBits 24
	#define DACChipSelects 0x00
	#define DACCSPolarityIdle 0x0F //Chip select polarity at idle
								//DAC Idle High 0x0F
	#define DACClockPolarity 0x00

//Synth SPI
	#define SYNTHSPI 1
	#define SYNTHdspiBaudRate 20000000
	#define SYNTHtransferSizeBits 24
	#define SYNTHCSPolarityIdle 0x0F //Chip select polarity at idle
								//SYNTH Idle High ??

#endif /* DEFINITIONS_H_ */