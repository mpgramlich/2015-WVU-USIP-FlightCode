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
OS_SEM BamaTaskStart;

ADC* adc;
DAC* dac;
//Synth* synth;

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
    dac = new DAC(DACSPI);

    OSSemInit(&BamaTaskStart, 0);
    OSSemInit(&PITSem, 0);

    setupTimer();

    RGPIO::SetupRGPIO();

    PWM::initPWM(PWMOutPin, PWMOn, PWMOff, PWMInitVal, PWMResetVal);

    adc->readAll(0);

    RGPIO::SetupRGPIO();

    MCP23017::init();       //default argument sets bus speed to ~1.5Mbits

    DEBUG_PRINT_NET("1: %X\r\n", MCP23017::disableM1());
    OSTimeDly(10);
    DEBUG_PRINT_NET("2: %X\r\n", MCP23017::disableM2());
    OSTimeDly(10);
    DEBUG_PRINT_NET("3: %X\r\n", MCP23017::enableM1());
    OSTimeDly(10);
    DEBUG_PRINT_NET("4: %X\r\n", MCP23017::enableM2());
    OSTimeDly(10);

    DEBUG_PRINT_NET("BamaTaskStart \r\n");
    OSSemPost(&BamaTaskStart);

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


