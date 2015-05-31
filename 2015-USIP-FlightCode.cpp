#include "predef.h"
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>
#include <autoupdate.h>
#include <smarttrap.h>
#include <taskmon.h>
#include <system.h>
#include <init.h>
#include <utils.h>
#include <stdlib.h>
#include <pins.h>
#include <HiResTimer.h>
#include <pitr_sem.h>
#include <NetworkDebug.h>

#define GPIO_PIN 12
// Addresses of Rapid GPIO registers
#define RGPIO_BAR 0x8C000000           // Base Address Register

// Offsets to BAR when accessing registers as a 16-bit word array
#define RGPIO_DIR (0)   // Data Dir Register
#define RGPIO_DAT (1)   // Data Register
#define RGPIO_ENB (2)   // Enable Register
#define RGPIO_CLR (3)   // Clear
#define RGPIO_SET (5)   // Set
#define RGPIO_TOG (7)   // Toggle

#define RGPIO_0 0x0001     // Pin 12

volatile PWORD pRGPIO_BAR = (PWORD) RGPIO_BAR;

//globals
HiResTimer* timer = HiResTimer::getHiResTimer(2);
OS_SEM waitTaskStart;//
OS_SEM PITSem;

extern "C" {
void UserMain(void * pd);
}

const char * AppName="2015_USIP_Flight-Code";

void waitTask(void * pd);
void SetupRGPIO();

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
    SetupRGPIO();

    timer->clearInterruptFunction();
    timer->init();
    timer->start();

    OSSemInit(&waitTaskStart, 0);
    OSSemInit(&PITSem, 0);

    OSSimpleTaskCreate(waitTask, 51);

    iprintf("Application started\n");
    OSTimeDly(100);
    OSSemPost(&waitTaskStart);
    while (1)
    {
    	iprintf("Main\r\n");
        OSTimeDly(10);
    }
}

void waitTask(void * pd)
{
	iprintf("waitTask started\r\n");
	OSSemPend(&waitTaskStart, 0);
	InitPitOSSem(1, &PITSem, 1.0101);
	while(1)
	{
		OSSemPend(&PITSem,0);
		USER_ENTER_CRITICAL();
		timer->pollingDelay(.002);
		asm("nop");
		pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
		timer->pollingDelay(.001);
		pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;
		USER_EXIT_CRITICAL();
	}
}

void SetupRGPIO()
{
   // Enable processor access to the RGPIO module
   asm(" move.l #0x8C000035,%d0");  // All bits fixed except bit 0, set to 1 to enable
   asm(" movec %d0,#0x009");        // Use movec to write to control register

   pRGPIO_BAR[RGPIO_DIR] = RGPIO_0;    // Set RGPIO to be an output
   pRGPIO_BAR[RGPIO_ENB] = RGPIO_0;    // Enable RGPIO pin

   // Set DSPI0 & One-Wire Slew Rate Control Register (SRCR_DSPIOW) to their maximum freq
   sim1.gpio.srcr_dspiow = 0x33;
}
