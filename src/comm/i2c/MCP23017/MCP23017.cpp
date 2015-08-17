/*
 * MCP23017.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: Matt
 */

#include "MCP23017.h"

BYTE MCP23017::txBuf[10] = {0x00};
BYTE MCP23017::rxBuf[10] = {0x00};
BYTE MCP23017::currOutRegs = 0x00;
volatile bool MCP23017::boomsExtended = false;
volatile bool MCP23017::boomsRetracted = true;
volatile  int MCP23017::retVal = 0;

BYTE MCP23017::init(BYTE frqDiv)
{

	Pins[29].function( PIN_29_I2C0_SDA);  // Set Pins to I2C
	Pins[27].function( PIN_27_I2C0_SCL);
	Master_I2CInit(MCP23017_Freq_Div);

	txBuf[0] = MCP23017_IODIRA;
	txBuf[1] = IODIRA_VAL; //set first two to output, rest to inputs
	txBuf[2] = IODIRB_VAL; //set all to inputs

	return Master_I2CSendBuf(MCP23017_Bus_Add, txBuf, 3);
/*
	DEBUG_PRINT_NET("1 %X\r\n",Master_I2CStart(MCP23017_Bus_Add, I2C_START_WRITE, 10));
	DEBUG_PRINT_NET("2 %X\r\n",Master_I2CSend(MCP23017_IODIRA, 10));
	DEBUG_PRINT_NET("3 %X\r\n",Master_I2CSend(IODIRA_VAL, 10));
	DEBUG_PRINT_NET("4 %X\r\n",Master_I2CSend(IODIRB_VAL, 10));
	DEBUG_PRINT_NET("5 %X\r\n",Master_I2CStop(10));
*/
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

	retVal = Master_I2CSendBuf(MCP23017_Bus_Add, rx, 1);
	if(retVal > 3)
		return retVal;
	retVal = Master_I2CReadBuf(MCP23017_Bus_Add, rx, 1);
	rx[0] = ~rx[0];
	return retVal;
}

void MCP23017::extendBoomsTask(void * pd)
{
	//OSSemPend(&ExtendBooms, 0);
	int start = TimeTick;
	printf("Extending Booms\r\n");
	enableM1();
	enableM2();
	OSTimeDly(20*10);
	/*
	boomsExtended = false;
	boomsRetracted = true;
	bool M2 = false;
	bool M1 = false;
	while((!M1 || !M2) && (TimeTick - start) < 300)
	{
		if(pollInput(true, rxBuf) > 3)
		{
			continue;
		}

		rxBuf[0] = ~rxBuf[0];
		if((rxBuf[0] & 0x20) == 0x20 && !M2)
		{
			disableM2();
			M2 = true;
		}
		if((rxBuf[0] & 0x08) == 0x08 && !M1)
		{
			disableM1();
			M1 = true;
		}
		printf("2. %X", rxBuf[0]);
		//OSTimeDly(5);
	}
	 */
	printf("Booms Extended\r\n");
	boomsExtended = true;
	boomsRetracted = false;
	disableM1();
	disableM2();
	//OSSemPend(&EmptySem, 0);
	return;
}

void MCP23017::retractBoomsTask(void * pd)
{
	//OSSemPend(&RetractBooms, 0);
	int start = TimeTick;
	printf("Retracting Booms\r\n");
	enableM1();
	enableM2();
	OSTimeDly(20*10);
	/*
	 boomsExtended = true;
	boomsRetracted = false;
	bool M2 = false;
	bool M1 = false;
	while((!M1 || !M2) && (TimeTick - start) < 300)
	{
		if(pollInput(true, rxBuf) > 3)
		{
			continue;
		}
		rxBuf[0] = ~rxBuf[0];
		if((rxBuf[0] & 0x10) == 0x10)
		{
			disableM2();
			M2 = true;
		}
		if((rxBuf[0] & 0x04) == 0x04)
		{
			disableM1();
			M1 = true;
		}
		printf("2. %X", rxBuf[0]);
		//OSTimeDly();
	}

	*/
	printf("Booms Retracted");
	boomsExtended = false;
	boomsRetracted = true;
	disableM1();
	disableM2();
	//OSSemPend(&EmptySem, 0);
	return;
}

void MCP23017::testInput()
{
	rxBuf[0] = 0x12;
	Master_I2CSendBuf(MCP23017_Bus_Add, rxBuf, 1);
	DEBUG_PRINT_NET("%X\r\n", Master_I2CReadBuf(MCP23017_Bus_Add, rxBuf, 1));
	DEBUG_PRINT_NET("rxBuf: %X\r\n", rxBuf[0]);
}

void MCP23017::testOutput()
{
	txBuf[0] = MCP23017_OLATA;
	txBuf[1] = 0x01;
	for(int i = 0; i < 10; i++)
	{
		txBuf[1] = 0x01;
		DEBUG_PRINT_NET("%X\r\n", Master_I2CSendBuf(MCP23017_Bus_Add, txBuf, 2));
		OSTimeDly(20);
		txBuf[1] = 0x00;
		DEBUG_PRINT_NET("%X\r\n", Master_I2CSendBuf(MCP23017_Bus_Add, txBuf, 2));
		OSTimeDly(20);
	}

	/*
	DEBUG_PRINT_NET("6 %X\r\n",Master_I2CStart(MCP23017_Bus_Add, I2C_START_WRITE));
	DEBUG_PRINT_NET("7 %X\r\n",Master_I2CSend(MCP23017_OLATA, 2));
	DEBUG_PRINT_NET("8 %X\r\n",Master_I2CSend(0x01, 2));
	DEBUG_PRINT_NET("9 %X\r\n",Master_I2CStop(2));
	*/
}



