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
#include <constants.h>
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
#include <HiResTimer.h>

//#include <SysLog.h> //comment to remove ethernet debugging statements

//RGPIO
	//#define EnableBamaTask 1.0101 //hertz of 1 ms pulse
	//#define EnableBamaTask 1.0 //hertz of 1 ms pulse
	#define TDIP_PIN 12
	#define MUX_A0 21
	#define MUX_A1 23
	#define SYNTH_RESET_PIN 25
	#define TDIP 0
	#define SYNTH_RESET 1
	#define A0 2
	#define A1 3
	// Addresses of Rapid GPIO registers
	#define RGPIO_BAR 0x8C000000           // Base Address Register

	// Offsets to BAR when accessing registers as a 16-bit word array
	#define RGPIO_DIR (0)   // Data Dir Register
	#define RGPIO_DAT (1)   // Data Register
	#define RGPIO_ENB (2)   // Enable Register
	#define RGPIO_CLR (3)   // Clear
	#define RGPIO_SET (5)   // Set
	#define RGPIO_TOG (7)   // Toggle

	#define RGPIO_0 0x0001     // Pin 37  N11
	#define RGPIO_1 0x0002     // Pin 32  G13
	#define RGPIO_2 0x0004     // Pin 33  H14
	#define RGPIO_3 0x0008     // Pin 34  H13
	#define RGPIO_4 0x0010     // Pin 36  H15
	#define RGPIO_5 0x0020     // Pin 29  E13
	#define RGPIO_6 0x0040     // Pin 23  B11
	#define RGPIO_7 0x0080     // Pin 24  C10
	#define RGPIO_8 0x0100     // Pin 25  D10

//HiResTimers
	static HiResTimer* timer = HiResTimer::getHiResTimer(2);
	static HiResTimer* throttle = HiResTimer::getHiResTimer(3);

//ADC SPI
	#define ADCTableSize 100;

	#define ADCSPI 2 //2
	//#define ADCdspiBaudRate 50000000
	#define ADCdspiBaudRate 20000000
	#define ADCtransferSizeBits 8
	#define ADCChipSelects 0xFF
	#define ADCCSPolarityIdle 0x0E //Chip select polarity at idle
								//ADC Idle Low 0x0E
	#define ADCClockPolarity 0x00

//DAC SPI
	#define DACSPI 3 //3
	#define DACdspiBaudRate 40000000
	#define DACtransferSizeBits 8
	#define DACChipSelects 0xFE
	#define DACCSPolarityIdle 0x01 //Chip select polarity at idle
								//DAC Idle High 0x0F
	#define DACClockPolarity 0x00
	#define DACZeroVoltage

//Synth SPI
	#define SYNTHSPI 1 //1
	#define SYNTHdspiBaudRate 20000000
	//#define SYNTHdspiBaudRate 10000000
	#define SYNTHtransferSizeBits 8
	#define SYNTHCS 0xFE
	#define SYNTHCSPolarityIdle 0x1 //Chip select polarity at idle
								//SYNTH Idle High ??

//SD SPI
	#define SDSPI 1 //1

//PWM
	#define PWMOutPin 	13
	#define PWMOn		0
	#define PWMOff		546
	#define PWMInitVal	0
	#define PWMResetVal	1365

//I2C
	#define MCP23017_Freq_Div 0x1C
	#define MCP23017_Bus_Add 0x20 //Bitwise OR with R/W Bit

	#define DS1307FreqDiv 0x3C

//Network Debugging
	#ifdef SYSLOG_H
	#define SYSLOGIP "192.168.11.10"
	#define DEBUG_PRINT_NET(args...) SysLog(args)
	#else
	#define DEBUG_PRINT_NET(args...)
	#endif

//Task Priorities
	/*
	#define MAIN_TASK_PRIO 37
	#define BAMA_TASK_PRIO MAIN_TASK_PRIO-1
	#define EBOOM_TASK_PRIO MAIN_TASK_PRIO-2
	#define RBOOM_TASK_PRIO MAIN_TASK_PRIO-3
	#define SERIAL_WRITE_TASK_PRIO MAIN_TASK_PRIO-4
	*/

	#define MAIN_TASK_PRIO 52
	#define BAMA_TASK_PRIO 51
	#define EBOOM_TASK_PRIO 50
	#define RBOOM_TASK_PRIO 49
	#define SERIAL_WRITE_TASK_PRIO 48


//Message Specific Definitions
	#define MSG_HEADER 				0xFF0A0BCC
	#define PAYLOAD_ACT_MSG_HEADER	0xEE0F0ABB
	#define DATA_BEGIN_HEADER		0x4D47474C //'MGGL'
	#define DATA_END_FOOTER			0xFA
	#define IDLE 					0x00
	#define LANGMUIR_P_EXPERIMENT 	0x01
	#define EFX_EXPERIMENT 			0x02
	#define RPE_EXPERIMENT 			0x04
	#define BAMA_EXPERIMENT	 		0x08

//Experiment Data Buffers
	#define EFX_NUM_OF_BUFFERS 500
	#define LP_NUM_OF_BUFFERS 500
	#define RPE_NUM_OF_BUFFERS 500
	#define BAMA_NUM_OF_BUFFERS 100


#endif /* DEFINITIONS_H_ */
