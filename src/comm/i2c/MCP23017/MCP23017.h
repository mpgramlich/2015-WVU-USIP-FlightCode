/*
 * MCP23017.h
 *
 *  Created on: Jun 17, 2015
 *      Author: Matt
 */

#ifndef MCP23017_H_
#define MCP23017_H_

#include "../../../../Definitions.h"
#include <i2cmaster.h>

extern OS_SEM ExtendBooms;
extern OS_SEM RetractBooms;
extern OS_SEM EmptySem;

namespace MCP23017
{
	extern BYTE txBuf[10];
	extern BYTE rxBuf[10];
	extern BYTE currOutRegs;
	extern volatile bool boomsExtended;
	extern volatile bool boomsRetracted;
	extern volatile int retVal;

	//frqDiv is the system bus rate divisor that determines i2c bus speed
	BYTE init(BYTE frqDiv = MCP23017_Freq_Div);
	BYTE pollInput(bool AnotB, BYTE* rx);

	void extendBoomsTask(void * pd);
	void retractBoomsTask(void * pd);

	void testInput();
	void testOutput();

	BYTE inline disableM1();
	BYTE inline disableM2();
	BYTE inline enableM1();
	BYTE inline enableM2();
	BYTE inline enableVCO();
	BYTE inline disableVCO();
	void inline retractBooms();
	void inline extendBooms();
}

#define BOOMS_RETRACTED 0x14
#define BOOMS_EXTENDED 0x28

#define IODIRA_VAL 0xFC //1111 1100
#define IODIRB_VAL 0xFF //1111 1111

#define MCP23017_GPIO_A 0x12
#define MCP23017_GPIO_B 0x13

// registers
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14

#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

BYTE inline MCP23017::disableM1()
{
	txBuf[0] = MCP23017_OLATA;
	txBuf[1] = currOutRegs | 0x01;
	currOutRegs = txBuf[1];
	return I2CSendBuf(MCP23017_Bus_Add, txBuf, 2);
}
BYTE inline MCP23017::disableM2()
{
	txBuf[0] = MCP23017_OLATA;
	txBuf[1] = currOutRegs | 0x02;
	currOutRegs = txBuf[1];
	return I2CSendBuf(MCP23017_Bus_Add, txBuf, 2);
}
BYTE inline MCP23017::enableM1()
{
	txBuf[0] = MCP23017_OLATA;
	txBuf[1] = currOutRegs & 0xFE;
	currOutRegs = txBuf[1];
	return I2CSendBuf(MCP23017_Bus_Add, txBuf, 2);
}
BYTE inline MCP23017::enableM2()
{
	txBuf[0] = MCP23017_OLATA;
	txBuf[1] = currOutRegs & 0xFD;
	currOutRegs = txBuf[1];
	return I2CSendBuf(MCP23017_Bus_Add, txBuf, 2);
}

BYTE inline MCP23017::enableVCO()
{
	txBuf[0] = MCP23017_OLATA;
	txBuf[1] = currOutRegs & 0x04;
	currOutRegs = txBuf[1];
	return I2CSendBuf(MCP23017_Bus_Add, txBuf, 2);
}

BYTE inline MCP23017::disableVCO()
{
	txBuf[0] = MCP23017_OLATA;
	txBuf[1] = currOutRegs & 0xFB;
	currOutRegs = txBuf[1];
	return I2CSendBuf(MCP23017_Bus_Add, txBuf, 2);
}

void inline MCP23017::extendBooms()
{
	OSSimpleTaskCreatewName(MCP23017::extendBoomsTask, EBOOM_TASK_PRIO,
								"Extend Booms Task");
}
void inline MCP23017::retractBooms()
{
	OSSimpleTaskCreatewName(MCP23017::retractBoomsTask, RBOOM_TASK_PRIO,
								"Retract Booms Task");
}

#endif /* MCP23017_H_ */
