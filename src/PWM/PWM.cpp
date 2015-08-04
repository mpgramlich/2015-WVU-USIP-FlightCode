/*
 * PWM.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: Matt Gramlich
 */

#include "PWM.h"

void PWM::initPWM(int pin, int16_t on, int16_t off, int16_t init, int16_t reset)
{
	int submod = 3;
	bool AnotB = 1;

	switch (pin)
	{
		case 13:
			Pins[pin].function(PIN_13_PWM_A3);
			break;
		case 15:
			Pins[pin].function(PIN_15_PWM_A1);
			break;
		case 16:
			Pins[pin].function(PIN_16_PWM_B3);
			break;
		case 31:
			Pins[pin].function(PIN_31_PWM_A0);
			break;
		case 33:
			Pins[pin].function(PIN_33_PWM_B0);
			break;
		case 35:
			Pins[pin].function(PIN_35_PWM_B2);
			break;
		case 37:
			Pins[pin].function(PIN_37_PWM_A2);
			break;
		case 39:
			Pins[pin].function(PIN_39_PWM_B1);
			break;
	}
	switch (pin)
	{
		case 13:
			submod = 3;
			AnotB = 1;
			break;
		case 15:
			submod = 1;
			AnotB = 1;
			break;
		case 16:
			submod = 3;
			AnotB = 0;
			break;
		case 31:
			submod = 0;
			AnotB = 1;
			break;
		case 33:
			submod = 0;
			AnotB = 0;
			break;
		case 35:
			submod = 2;
			AnotB = 0;
			break;
		case 37:
			submod = 2;
			AnotB = 1;
			break;
		case 39:
			submod = 1;
			AnotB = 0;
			break;
	}

	if (sim1.mcpwm.mcr & 0x000F == 0x000F)
	{
		sim1.mcpwm.mcr |= 0x00F0;
	}

	sim1.mcpwm.mcr &= 0xFFFF;

	sim1.mcpwm.sm[submod].init = init; //Inital Value = 0
	if (AnotB)
		sim1.mcpwm.sm[submod].val[2] = on; //PWM_A On = 0
	else
		sim1.mcpwm.sm[submod].val[4] = on; //PWM_B On = 0

	sim1.mcpwm.sm[submod].val[0] = reset / 2; //Median 0

	if (!AnotB)
		sim1.mcpwm.sm[submod].val[5] = off; //PWM_B Off = 256
	else
		sim1.mcpwm.sm[submod].val[3] = off; //PWM_A Off = 256

	sim1.mcpwm.sm[submod].val[1] = reset;

	//Enable Control Registers
	sim1.mcpwm.sm[submod].cr1 = 0x0470; //0000_0100_0111_0000
	sim1.mcpwm.sm[submod].cr2 = 0x2000; //0010_0000_0000_0000

	//Clear Comparison Flags
	sim1.mcpwm.sm[submod].sr |= 0x001F; //Setting 1 to the last 5 positions clears flags.

	//Disable all Faults
	sim1.mcpwm.sm[submod].dismap &= 0xF000; //The last 3 hex digits are fault enables.

	//Outputs not inverted
	sim1.mcpwm.sm[submod].ocr &= 0xE0C0; //The second hex digit controls bit inversion.

	//Set output mask to 0
	sim1.mcpwm.mask = 0;

	//Enable the pwm output
	if (AnotB)
		sim1.mcpwm.outen |= (0x0001 << (8 + submod)); //Second hex bit enables A signals.
	else
		sim1.mcpwm.outen |= (0x0001 << (4 + submod)); //Third hex bit enables B signals.

	//Set PWM_MCR[LDOK]
	sim1.mcpwm.mcr |= 0x000F; //Each of the last 4 bits correspond to the each of the 4 PWM module's LDOK

	//Set PWM_MCR[RUN]
	sim1.mcpwm.mcr |= 0x0F00; //Each bit of the second hex digit correspond to the corresponding 4 PWM modules RUN
}

