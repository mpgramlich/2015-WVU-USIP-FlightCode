/*
 * MCP23017.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: Matt
 */

#include "MCP23017.h"

BYTE MCP23017::init(BYTE frqDiv)
{

	//Pins[29].function( PIN_29_I2C0_SDA);  // Set Pins to I2C
	//Pins[27].function( PIN_27_I2C0_SCL);
	I2CInit(MCP23017_Freq_Div);

	txBuf[0] = MCP23017_IODIRA;
	txBuf[1] = IODIRA_VAL; //set first two to output, rest to inputs
	txBuf[2] = IODIRB_VAL; //set all to inputs

	return I2CSendBuf(MCP23017_Bus_Add, txBuf, 3);
/*
	DEBUG_PRINT_NET("1 %X\r\n",Master_I2CStart(MCP23017_Bus_Add, I2C_START_WRITE, 10));
	DEBUG_PRINT_NET("2 %X\r\n",Master_I2CSend(MCP23017_IODIRA, 10));
	DEBUG_PRINT_NET("3 %X\r\n",Master_I2CSend(IODIRA_VAL, 10));
	DEBUG_PRINT_NET("4 %X\r\n",Master_I2CSend(IODIRB_VAL, 10));
	DEBUG_PRINT_NET("5 %X\r\n",Master_I2CStop(10));*/
}

//modifies pointer passed in
//returns state of bus when finished
//recommend placing in external task to prevent bus lockups from stalling system
BYTE MCP23017::pollInput(bool AnotB, BYTE* rx)
{
	if(AnotB)
		rx[0] = MCP23017_GPIO_A;
	else
		rx[0] = MCP23017_GPIO_B;

	I2CSendBuf(MCP23017_Bus_Add, rx, 1);
	return I2CReadBuf(MCP23017_Bus_Add, rx, 1);
}

void MCP23017::extendBoomsTask(void * pd)
{
	while(!boomsExtended)
	{
		OSTimeDly(10);
		pollInput(true, rxBuf);
		if((rxBuf[0] & BOOMS_EXTENDED) == BOOMS_EXTENDED)
		{
			disableM1();
			disableM2();
			boomsExtended = true;
			boomsRetracted = false;
		}
		else
		{
			boomsExtended = false;
			boomsRetracted = true;
			enableM1();
			enableM2();
		}
	}
}

void MCP23017::retractBoomsTask(void * pd)
{
	printf("Retracting Booms");
	boomsExtended = true;

	while(boomsExtended)
	{
		pollInput(true, rxBuf);
		rxBuf[0] = ~rxBuf[0];
		if((rxBuf[0] & BOOMS_RETRACTED) == BOOMS_RETRACTED)
		{
			printf("1. %x", rxBuf[0]);
			disableM1();
			disableM2();
			boomsExtended = false;
			boomsRetracted = true;
		}
		else
		{
			printf("2. %X", rxBuf[0]);
			boomsExtended = true;
			boomsRetracted = false;
			//enableM1();
			enableM2();
		}
		OSTimeDly(4);
	}
	printf("Booms Retracted");
	return;
}

void MCP23017::testInput()
{
	rxBuf[0] = 0x12;
	I2CSendBuf(MCP23017_Bus_Add, rxBuf, 1);
	DEBUG_PRINT_NET("%X\r\n", I2CReadBuf(MCP23017_Bus_Add, rxBuf, 1));
	DEBUG_PRINT_NET("rxBuf: %X\r\n", rxBuf[0]);
}

void MCP23017::testOutput()
{
	txBuf[0] = MCP23017_OLATA;
	txBuf[1] = 0x01;
	for(int i = 0; i < 10; i++)
	{
		txBuf[1] = 0x01;
		DEBUG_PRINT_NET("%X\r\n", I2CSendBuf(MCP23017_Bus_Add, txBuf, 2));
		OSTimeDly(20);
		txBuf[1] = 0x00;
		DEBUG_PRINT_NET("%X\r\n", I2CSendBuf(MCP23017_Bus_Add, txBuf, 2));
		OSTimeDly(20);
	}

	/*
	DEBUG_PRINT_NET("6 %X\r\n",Master_I2CStart(MCP23017_Bus_Add, I2C_START_WRITE));
	DEBUG_PRINT_NET("7 %X\r\n",Master_I2CSend(MCP23017_OLATA, 2));
	DEBUG_PRINT_NET("8 %X\r\n",Master_I2CSend(0x01, 2));
	DEBUG_PRINT_NET("9 %X\r\n",Master_I2CStop(2));
	*/
}



