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
#include "src/comm/i2c/MCP23017/MCP23017.h"
#include "src/comm/serial/Serial_IO.h"
#include "src/PWM/PWM.h"

//globals
OS_SEM PITSem;
OS_SEM BamaTaskStart;

ADC* adc;
DAC* dac;
//Synth* synth;

static bool TP70 = false;
static bool TP380 = false;

//externally linked stuff

extern "C" {
void UserMain(void * pd);
}

void ConfigureIrq7( int polarity, void ( *func )( void ) );
void ExperimentStartISR();
void SetupTimer();

const char * AppName="2015_USIP_Flight-Code";

void UserMain(void * pd) {
    InitializeStack();
    OSChangePrio(MAIN_TASK_PRIO);
    EnableAutoUpdate();
    EnableTaskMonitor();
    EnableSmartTraps();

    Serial_IO::initSerial();

    ReplaceStdio(1, Serial_IO::serialFd[2]);

    SysLogAddress = AsciiToIp(SYSLOGIP);

    DEBUG_PRINT_NET("Application Started\r\n");

    adc = new ADC(ADCSPI);
    dac = new DAC(DACSPI);
    //synth = new Synth(SYNTHSPI);

    OSSemInit(&BamaTaskStart, 0);
    OSSemInit(&PITSem, 0);

    SetupTimer();

    RGPIO::SetupRGPIO();

    MCP23017::init();       //default argument sets bus speed to ~1.5Mbits
    MCP23017::disableM1();
    MCP23017::disableM2();

    PWM::initPWM(PWMOutPin, PWMOn, PWMOff, PWMInitVal, PWMResetVal);

    //adc->readAll(0);

    ConfigureIrq7(0, &ExperimentStartISR);

    //DEBUG_PRINT_NET("BamaTaskStart \r\n");
    //OSSemPost(&BamaTaskStart);

    //pRGPIO_BAR[RGPIO_TOG] = RGPIO_0;

    //MCP23017::extendBooms();

/*
    union
    {
    	BYTE rx_t;
    	char rxtest;
    };
    BYTE temp = 0;
    bool od = true;
    bool td = true;

    while(od & td)
    {
        MCP23017::pollInput(true, &rx_t);
        temp = rx_t;
        temp &= 0x30;
        if((temp & 0x10) == 0x10)
        	od = true;
        else
        	od = false;
        if((temp & 0x20) == 0x20)
        	td = true;
        else
        	td = false;
        MCP23017::enableM2();
        printf("%X\r\n", rxtest);
        Serial_IO::writePend(&Serial_IO::serialFd[2], &rxtest, 1);
        //write(Serial_IO::serialFd[2], &rxtest, 1);
    }
    MCP23017::disableM2();*/

    MCP23017::retractBoomsTask(0);

    while (1)
    {
        OSTimeDly(10);
    }
}

void ExperimentStartISR()
{
	sim2.eport.epfr = 0x80;

	if( TP70 && !TP380)
		TP380 = true;

	if(!TP70)
		TP70 = true;

}

void ConfigureIrq7( int polarity, void ( *func )( void ) )
{
	Pins[9].function(PIN_9_GPIO);
	Pins[9] = 0;
	Pins[9].function(PIN_9_IRQ7);

    int irqLevel = 7;      // IRQ priority level
    int intCntlNum = 0;    // Interrupt controller number
    int vector = 7;     // Interrupt source number for interrupt controller
    DWORD mask;

#ifdef MOD5441X
   J2[48].function( PINJ2_48_IRQ7 );
#elif NANO54415
   Pins[9].function( PIN_9_IRQ7 );
#endif

    /* Set irq polarity
       EPPAR settings
        00 Pin IRQn level-sensitive
        01 Pin IRQn rising edge triggered
        10 Pin IRQn falling edge triggered
        11 Pin IRQn falling edge and rising edge triggered
    */
    sim2.eport.eppar &= 0x3FFF;         // Clear IRQ7 bits
    if ( polarity > 0 )
       sim2.eport.eppar |= 0x4000;      // Positive edge trigger
    else if ( polarity < 0 )
       sim2.eport.eppar |= 0x8000;      // Negative edge trigger
    else
       sim2.eport.eppar |= 0xC000;      // Both edges

    sim2.eport.epddr &= ~80;            // Configure IRQ7 pin as an input

    // Set the interrupt level for the corresponding interrupt source
    sim2.intc[intCntlNum].icrn[vector] = ( irqLevel & 7 );

    vector_base.table[( intCntlNum * 64 ) + 64 + vector] = (unsigned long)func;

    sim2.eport.epier |= 0x80;           // Enable interrupt

    // Unmask/enable the level 7 IRQ in the interrupt controller
    mask = ( 1 << vector );
    sim2.intc[intCntlNum].imrl &= ~mask;
}

void SetupTimer()
{
	timer->clearInterruptFunction();
	timer->init();
	timer->start();
}


