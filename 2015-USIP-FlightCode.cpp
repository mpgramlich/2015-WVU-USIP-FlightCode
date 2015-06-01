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

//globals
OS_SEM PITSem;
OS_SEM waitTaskStart;

ADC ADC(ADCSPI);
DAC DAC(DACSPI);
Synth Synth(SYNTHSPI);

//externally linked stuff

extern "C" {
void UserMain(void * pd);
}

void setupTimer();

const char * AppName="2015_USIP_Flight-Code";

void UserMain(void * pd) {
    InitializeStack();
    OSChangePrio(52);
    EnableAutoUpdate();
    //EnableTaskMonitor();
    EnableSmartTraps();

    SysLogAddress = AsciiToIp("10.20.15.10");

    Pins[GPIO_PIN].function(PIN_12_GPIO);
    Pins[GPIO_PIN] = 0;
    RGPIO::SetupRGPIO();

    OSSemInit(&waitTaskStart, 0);
    OSSemInit(&PITSem, 0);

    OSSimpleTaskCreate(RGPIO::gpioWaitTask, 51);

    iprintf("Application started\n");
    OSTimeDly(100);
    OSSemPost(&waitTaskStart);
    while (1)
    {
    	iprintf("Main\r\n");
        OSTimeDly(10);
    }
}

void setupTimer()
{
	timer->clearInterruptFunction();
	timer->init();
	timer->start();
}


