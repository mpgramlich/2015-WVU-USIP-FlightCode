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
#include "src/comm/serial/Comm.h"
#include "src/PWM/PWM.h"

//globals
OS_SEM PITSem;
OS_SEM BamaTaskStart;
OS_SEM ExtendBooms;
OS_SEM RetractBooms;
OS_SEM EmptySem; //tasks that are done pend on this forever,
OS_SEM DataSem;

ADC* adc;
DAC* dac;
Synth* synth;

static bool TP70 = false;
static bool TP380 = false;

DataMsg::bigEndianMsg_t datamsg;
DataMsg::littleEndianData_t datamsgl;

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

    Comm::startCommTask();

    SysLogAddress = AsciiToIp(SYSLOGIP);

    DEBUG_PRINT_NET("Application Started\r\n");

    adc = new ADC(ADCSPI);
    //dac = new DAC(DACSPI);
    //synth = new Synth(SYNTHSPI);

    OSSemInit(&BamaTaskStart, 0);
    OSSemInit(&EmptySem, 0);
    OSSemInit(&ExtendBooms, 0);
    OSSemInit(&RetractBooms, 0);

    SetupTimer();

    RGPIO::SetupRGPIO();

    MCP23017::init();       //default argument sets bus speed to ~1.5Mbits
    MCP23017::disableM1();
    MCP23017::disableM2();

    PWM::initPWM(PWMOutPin, PWMOn, PWMOff, PWMInitVal, PWMResetVal);

    //printf("Before Output\n");
    //synth->testOutput();
    //printf("After Output\n");
    union
    {
    	uint32_t raw;
    	char rawchar[4];
    };

    iprintf("Starting Transfer\n");
    USER_ENTER_CRITICAL();
   // for(int i = 0; i < 5000; i += 3)
    {
    	adc->readAll(0);
    	OSSemPend(&adc->SPISEM, 0);
    }
    USER_EXIT_CRITICAL();

    for(int i = 0; i < 5000; i+=3)
    {
    	double volts = 0.0;
    	int32_t actual = 0;
    	//printf("%2X, ", adc->table[i]);
    	rawchar[2] = adc->table[i];
    	rawchar[3] = adc->table[i+1];
    	raw = ((raw<<2)|(0x03&(adc->table[i+2]>>6)));
    	actual = raw;
    	if(raw >= 0x20000)
    	{
    		actual -= 0x3ffff;
    	}
    	volts = (double)actual * 0.000034332275390625;
    	printf("%3.8f\n", volts);
    }
}

void ExperimentStartISR()
{
	sim2.eport.epfr = 0x80;

	if( TP70 && !TP380)
	{
		//ConfigureIrq7(-1, &ExperimentStartISR);
		TP380 = true;
		OSSemPost(&RetractBooms);
	}

	if(!TP70)
	{
		TP70 = true;
		OSSemPost(&ExtendBooms);
	}
	return;

}

void ConfigureIrq7( int polarity, void ( *func )( void ) )
{
    int irqLevel = 7;      // IRQ priority level
    int intCntlNum = 0;    // Interrupt controller number
    int vector = 7;     // Interrupt source number for interrupt controller
    DWORD mask;

#ifdef MOD5441X
   //J2[48].function( PINJ2_48_IRQ7 );
#elif NANO54415
   //Pins[9].function( PIN_9_IRQ7 );
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


