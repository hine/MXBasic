/*******************************************************************************
	timer module
*******************************************************************************/

#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include <stdio.h>
#include <stdlib.h>
#include "usb_config.h"
#include "usb.h"
#include "usb_host_hid.h"
#include "usb_host_hid_parser.h"
#include "timer.h"


/*------------------------------------------------------------------------------
	definition
------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
	function prototype
------------------------------------------------------------------------------*/

void timer_init(void);
void delay_ms(int t);


/*------------------------------------------------------------------------------
	global variable
------------------------------------------------------------------------------*/

static volatile DWORD timer_tick;
static volatile DWORD delay_timer;

volatile DWORD	AplTimer;           // 1msec interval down counter for Application
volatile int    CursorBlink;        // 500msec toggle, 1Hz blink 
volatile int    KeyPolling;         // USB keyboard read interval 
//volatile unsigned short ClockCount; // 1sec interval countdown timer
//volatile int    tempo_strobe;       // 5msec toggle, 100Hz music tempo
extern unsigned int soundcount;
extern volatile int soundon;


/*------------------------------------------------------------------------------
	initialize timer module
------------------------------------------------------------------------------*/

void timer_init(void)
{
    IEC0SET = _IEC0_T1IE_MASK; // enable T1 interrupt
    IFS0CLR = _IFS0_T1IF_MASK; // clear interrupt flag

    IPC1bits.T1IP = 2;

    //--- set interval 1ms timer
    T1CON = 0x0010;	// timer(T1), set prescale 1:8
    TMR1 = 0;
    PR1 = GetPeripheralClock()/8/1000L;	// period 1msec
    T1CONSET = _T1CON_TON_MASK;	// start T1
}

/*------------------------------------------------------------------------------
	Timer T1 1msec interval timer.
------------------------------------------------------------------------------*/

void __attribute__ (( interrupt(ipl2), vector(_TIMER_1_VECTOR) )) _T1Interrupt(void)
{
    //extern void disk_timerproc(void);
    unsigned short key;

    // *** down count, etc timer *******************
    // provide timer
    if(AplTimer) AplTimer--;
    if(delay_timer) delay_timer--;

    // disk i/o command timeout timer
    //disk_timerproc();

    // support Display refresh timing
    //if(RefreshTime) RefreshTime--;

    // support USB keyboard polling(10msec)
    if(!KeyPolling){
        //USBTasks();
        // keyboard_scan();
        KeyPolling=10;
    }else{
        KeyPolling--;
    }

    // *** toggle interval timer *************
    if(soundon == 1){
        soundcount--;
        if(soundcount <= 0) sound_stop();
    }
 
    // update 2Hz cursor blink timer
    if(!(timer_tick % 500)) CursorBlink ^= 1;

    // count up timer_tick
    ++timer_tick;

    // *** 1sec interval process *******
    if(timer_tick >= 1000){
        timer_tick = 0;
    } // tick  

    // clear interrupt flag
    clear_timer();

}

/*---------------------------------------------------------------------------------------------
	generate music frequency by T3 interrupt
---------------------------------------------------------------------------------------------*/

void __attribute__ (( interrupt(ipl2), vector(_TIMER_3_VECTOR) )) _T3Interrupt(void)
{
	IFS0CLR=_IFS0_T3IF_MASK;
	LATBINV = 0x0200;	// toggle RB9
}

/*-----------------------------------------------------------
	delay_ms()
-----------------------------------------------------------*/

void delay_ms(int t)
{
    delay_timer = (DWORD)t;
    while(delay_timer);
}
