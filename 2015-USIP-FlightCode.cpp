
#include "Definitions.h"

#include "src/RGPIO/RGPIO.h"

//globals
OS_SEM PITSem;
OS_SEM waitTaskStart;

//externally linked stuff

extern "C" {
void UserMain(void * pd);
}

const char * AppName="2015_USIP_Flight-Code";

void UserMain(void * pd) {
    InitializeStack();
    OSChangePrio(52);
    EnableAutoUpdate();
    //EnableTaskMonitor();

    #ifndef _DEBUG
    EnableSmartTraps();
    #endif

    #ifdef _DEBUG
    InitializeNetworkGDB_and_Wait();
    #endif

    Pins[GPIO_PIN].function(PIN_12_GPIO);
    Pins[GPIO_PIN] = 0;
    RGPIO::SetupRGPIO();

    timer->clearInterruptFunction();
    timer->init();
    timer->start();

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


