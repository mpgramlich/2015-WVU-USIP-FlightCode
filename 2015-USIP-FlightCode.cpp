/*
 * Definitions.h
 *
 *  Created on: May 29, 2015
 *      Author: Matt Gramlich
 *      			Greg Lusk
 */
 
/*
The MIT License (MIT)

Copyright (c) 2015 Matthew Gramlich
				   Greg Lusk

Permission is hereby granted, free of charge, 
to any person obtaining a copy of this software 
and associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, 
copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit 
persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission
notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT 
WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Definitions.h"

#include "src/RGPIO/RGPIO.h"
#include "src/comm/spi/ADC/ADC.h"
#include "src/comm/spi/DAC/DAC.h"
#include "src/comm/spi/SDCard/FileSystemUtils.h"
#include "src/comm/spi/Synth/Synth.h"
#include "src/comm/spi/Synth/SynthTable.h"
#include "src/comm/i2c/MCP23017/MCP23017.h"
#include "src/comm/serial/Serial_IO.h"
#include "src/PWM/PWM.h"


#include "src/Experiments/EFX.h"
#include "src/Experiments/LangmuirProbe.h"
#include "src/Experiments/RPE.h"
#include "src/Experiments/Alabama.h"
#include "src/comm/msgs/Data-msg.h"
#include "src/comm/msgs/Mailbox-msg.h"

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

DataMsg::dataMsg_t payloadActivatedMsg;
mail::mail_t payloadActivatedLetter;

//externally linked stuff
volatile bool TP70 = false;
volatile bool TP380 = false;

extern "C" {
	void UserMain(void * pd);
	void SetIntc(int intCntlNum,  long func, int vector, int irqLevel);
	void ExperimentStartISR(void);
}

void ConfigureIrq7( int polarity, void ( *func )( void ) );
void SetupTimer();

const char * AppName="2015_USIP_Flight-Code";

void UserMain(void * pd) {
    InitializeStack();
    OSChangePrio(MAIN_TASK_PRIO);
    EnableAutoUpdate();
    EnableTaskMonitor();
    EnableSmartTraps();

    Serial_IO::initSerial();
    ReplaceStdio(0, Serial_IO::serialFd[2]);
    Serial_IO::StartSerialWriteTask();

//    SetupTimer();
#ifdef SYSLOG_H
    SysLogAddress = AsciiToIp(SYSLOGIP);
#endif

    DEBUG_PRINT_NET("Application Started\r\n");

    //ConfigureIrq7(1, &ExperimentStartISR);
    Pins[9].function( PIN_9_GPIO );

    adc = new ADC(ADCSPI);
    dac = new DAC(DACSPI);
    synth = new Synth(SYNTHSPI);

    OSSemInit(&BamaTaskStart, 0);
    OSSemInit(&EmptySem, 0);
    OSSemInit(&ExtendBooms, 0);
    OSSemInit(&RetractBooms, 0);

    RGPIO::SetupRGPIO();

    MCP23017::init();       //default argument sets bus speed to ~1.5Mbits
    MCP23017::disableVCO();
    MCP23017::disableM1();
    MCP23017::disableM2();

    PWM::initPWM(PWMOutPin, PWMOn, PWMOff, PWMInitVal, PWMResetVal);

    SetupTimer();

    bool visitedActivated = false;
    bool visitedDeactivated= false;
    DWORD startoverflow = timer->readHigh();

    //DEBUG_PRINT_NET("RUNNING \r\n");
    payloadActivatedMsg.msg.H1 = MSG_HEADER;
    payloadActivatedMsg.msg.counter = 0x00;
    payloadActivatedMsg.msg.experiment = 0xFF;
    payloadActivatedMsg.msg.databegin = DATA_BEGIN_HEADER;
    payloadActivatedMsg.msg.F1 = DATA_END_FOOTER;
    payloadActivatedLetter.length = DataMsg::size;
    payloadActivatedLetter.inUse = TRUE;

    while(1)
    {
    	if(Pins[9].read() && !visitedActivated)
    	{
    		visitedActivated = true;
    		//writestring(Serial_IO::serialFd[2], "activated\r\n");
    		DEBUG_PRINT_NET("activated\r\n");
    		startoverflow = timer->readHigh();
    		payloadActivatedMsg.msg.clock_reg_count = timer->readLow();
    		payloadActivatedMsg.msg.clock_reg_reset_count = (uint16_t)timer->readHigh();
    		payloadActivatedLetter.data = payloadActivatedMsg.serialData;
    		MCP23017::enableM1();
    		MCP23017::enableM2();
    		Serial_IO::postToQueue((void*) &payloadActivatedLetter); //doesn't matter when this is sent, data is already recorded
    		OSTimeDly(10*20);
    		MCP23017::disableM1();
    		MCP23017::disableM2();
    	}
    	else if(timer->readHigh() > 8 && !Pins[9].read() && visitedActivated && !visitedDeactivated)
    	{
    		visitedDeactivated = true;
    		DEBUG_PRINT_NET("de-activated\r\n");
    		payloadActivatedMsg.msg.clock_reg_count = timer->readLow();
    		payloadActivatedMsg.msg.clock_reg_reset_count = (uint16_t)timer->readHigh();
    		payloadActivatedMsg.msg.experiment = 0xAA; //payload deactivated
    		payloadActivatedLetter.data = payloadActivatedMsg.serialData;
    		MCP23017::enableM1();
    		MCP23017::enableM2();
    		Serial_IO::postToQueue((void*) &payloadActivatedLetter); //doesn't matter when this is sent, data is already recorded
    		OSTimeDly(10*20);
    		MCP23017::disableM1();
    		MCP23017::disableM2();

			//slow way of writing SD card Data
			f_enterFS();
			InitExtFlash();

			//to write all data from RPE
			//RPE::letter[RPE::selectedBuffer].serialData   (pointer to beginning of data)
			//(RPE_NUM_OF_BUFFERS - RPE::selectedBuffer) * sizeof(RPE::RPEmsg_t)  (total length of data block)
			WriteFile(
					reinterpret_cast<BYTE*>(RPE::letter[RPE::selectedBuffer].serialData),
					"RPE_Experiment_Data.bin",
					(RPE_NUM_OF_BUFFERS - RPE::selectedBuffer)
							* ((DWORD) sizeof(RPE::RPEmsg_t)));

			WriteFile(
					reinterpret_cast<BYTE*>(LP::letter[LP::selectedBuffer].serialData),
					"LP_Experiment_Data.bin",
					(LP_NUM_OF_BUFFERS - LP::selectedBuffer)
							* ((DWORD) sizeof(LP::LPmsg_t)));

			WriteFile(
					reinterpret_cast<BYTE*>(BAMA::letter[BAMA::selectedBuffer].serialData),
					"BAMA_Experiment_Data.bin",
					(BAMA_NUM_OF_BUFFERS - BAMA::selectedBuffer)
							* ((DWORD) sizeof(BAMA::BAMAmsg_t)));

			UnmountExtFlash();
			f_releaseFS();

			//Mission Finished, post deactivation message. Enter never ending loop.
			Serial_IO::postToQueue((void*) &payloadActivatedLetter); //doesn't matter when this is sent, data is already recorded
			while (1)
			{
				OSTimeDly(20);
			}
    	}
    	else if(visitedActivated && !visitedDeactivated)
    	{
    		//DEBUG_PRINT_NET("timer value %u\r\noverlfows value %u\r\npin value %d\r\n", timer->readLow(), timer->readHigh(), Pins[9].read());
    		RPE::runExperiment(adc, synth);
    		BAMA::runExperiment(adc);
    		//EFX::runExperiment(adc);
    		LP::runExperiment(adc, dac);
    		BAMA::runExperiment(adc);
    	}
    	//DEBUG_PRINT_NET("overlfows value %u\r\n", timer->readHigh());
    	//DEBUG_PRINT_NET("deciaml overlfows value %u\r\n", timer->readHigh());
    	//OSTimeDly(3);
    }


}

void ExperimentStartISR()
{
	sim2.eport.epfr = 0x80;

	if(!TP70)
	{
		TP70 = true;
		return;
	}
	TP380 = true;
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
//   Pins[9].function( PIN_9_IRQ7 );
#endif

   Pins[9].function( PIN_9_IRQ7 );
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

	throttle->clearInterruptFunction();
	throttle->init();
	throttle->start();
}


