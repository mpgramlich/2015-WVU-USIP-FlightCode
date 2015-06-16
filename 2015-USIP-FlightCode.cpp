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
    OSChangePrio(52);
    EnableAutoUpdate();
    //EnableTaskMonitor();
    EnableSmartTraps();

    SysLogAddress = AsciiToIp("192.168.11.10");

    iprintf("Application started\n");
    adc = new ADC(ADCSPI);

    Pins[GPIO_PIN].function(PIN_12_GPIO);
    Pins[GPIO_PIN] = 0;
    RGPIO::SetupRGPIO();


    OSSemInit(&waitTaskStart, 0);
    OSSemInit(&PITSem, 0);

    //OSSimpleTaskCreate(RGPIO::gpioWaitTask, 51);

    OSTimeDly(100);

    adc->readAll(0);
    OSSemPend(&adc->SPISEM, 0);
    for(int i = 0; i < 4; i++)
        iprintf("%2X|",ADCTable::table[i]);
    iprintf("\r\n");
    OSSemPost(&waitTaskStart);
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


