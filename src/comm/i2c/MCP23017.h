/*
 * MCP23017.h
 *
 *  Created on: Jun 17, 2015
 *      Author: Matt
 */

#ifndef MCP23017_H_
#define MCP23017_H_

#include "../../../Definitions.h"
#include <i2cmaster.h>

namespace MCP23017
{
	static BYTE txBuf[10] = {0x00};
	static BYTE rxBuf[10] = {0x00};
	//frqDiv is the system bus rate divisor that determines i2c bus speed
	void init(BYTE frqDiv = MCP23017_Freq_Div);

	void testInput();
	void testOutput();
}

#define IODIRA_VAL 0xFC //1111 1100
#define IODIRB_VAL 0xFF //1111 1111

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


#endif /* MCP23017_H_ */
