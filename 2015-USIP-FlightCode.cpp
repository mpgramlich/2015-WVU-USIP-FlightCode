/*
 * Definitions.h
 *
 *  Created on: May 29, 2015
 *      Author: Matt Gramlich
 *      			Greg Lusk
 */

#include "Definitions.h"

#include "src/RGPIO/RGPIO.h"
#include "src/comm/spi/ADC/ADC.h"
#include "src/comm/spi/DAC/DAC.h"
#include "src/comm/spi/Synth/Synth.h"
#include "src/comm/i2c/MCP23017.h"
#include "src/PWM/PWM.h"

//globals
OS_SEM PITSem;
OS_SEM waitTaskStart;

ADC* adc;
//DAC DAC(DACSPI);
//Synth Synth(SYNTHSPI);

//externally linked stuff

extern "C" {
void UserMain(void * pd);
}

void setupTimer();

const char * AppName="2015_USIP_Flight-Code";

void UserMain(void * pd) {
    InitializeStack();
    OSChangePrio(MAIN_TASK_PRIO);
    EnableAutoUpdate();
    EnableTaskMonitor();
    EnableSmartTraps();

    SysLogAddress = AsciiToIp(SYSLOGIP);

    DEBUG_PRINT_NET("Application Started\r\n");

    adc = new ADC(ADCSPI);

    OSSemInit(&waitTaskStart, 0);
    OSSemInit(&PITSem, 0);

    Pins[GPIO_PIN].function(PIN_12_GPIO);
    Pins[GPIO_PIN] = 0;
    setupTimer();
    RGPIO::SetupRGPIO();

    PWM::initPWM(PWMOutPin, PWMOn, PWMOff, PWMInitVal, PWMResetVal);

    MCP23017::init();       //default argument sets bus speed to ~1.5Mbits
    //MCP23017::testOutput();
    for(int i = 0; i < 20; i++)
    {
    	MCP23017::testInput();
    	OSTimeDly(20);
    }

    //OSSemPost(&waitTaskStart);
    while (1)
    {

        OSTimeDly(10);
    }
}

void setupTimer()
{
	timer->clearInterruptFunction();
	timer->init();
	timer->start();
}


