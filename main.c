/******************************************************************************
 *
 * SONO-SYSTEM by Daisuke IMAI <hine.gdw@gmail.com>
 *
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "usb.h"
#include "usb_host_hid.h"
#include "usb_host_hid_parser.h"
#include "usb_host_hid_device.h"
#include "timer.h"
#include "keyboard.h"
#include "display.h"
#include "character.h"
#include "ttbasic.h"
#include "sound.h"


/*------------------------------------------------------------------------------
	Configuration for PIC32MX695F 
------------------------------------------------------------------------------*/

#include "p32mx695f_config.h"


/*------------------------------------------------------------------------------
	definition
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
	function prototype
------------------------------------------------------------------------------*/

void	InitializeSystem (void);
int     main (void);


/*------------------------------------------------------------------------------
	global variable
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------
	InitializeSystem()
-----------------------------------------------------------------------*/

void InitializeSystem ( void )
{

    int	value;

    // Set System Config
    //SYSTEMConfigPerformance(GetSystemClock());
    value = SYSTEMConfigWaitStatesAndPB( GetSystemClock() );

    // Enable the cache for the best performance
    CheKseg0CacheOn();

    // enable multi vector
    INTEnableSystemMultiVectoredInt();

    value = OSCCON;
    while (!(value & 0x00000020)){
        value = OSCCON;    // Wait for PLL lock to stabilize
    }

    INTEnableInterrupts();

    // ADC input off
    AD1PCFG = 0xffff;
    // disable JTAG
    DDPCONbits.JTAGEN = 0;

    //--- setting I/O pins
    TRISB=0x0020;
    LATB=0xc000;
        // RB5        input,  MMC_CD
        // RB9        output, sound out, initial low
        // RB14,RB15  output, LED monitor, initial high
        // others     output, output level low

    // RC all pins not use
    TRISC = 0x0000;
    LATC = 0x0000;

    LATD=	0x0000;
    TRISD=	0x0004;
        // RD0(OC1)      output, N.C
        // RD1(SCK3/OC2) output, N.C
        // RD2(SDI3/OC3) input,  N.C
        // RD3(SDO3)     output, NTSC video signal
        // RD9           output, NTSC sync
        // others        output, output level low

    // RE all pins not use
    TRISE = 0x0000;
    LATE = 0x0000;

    TRISF = 0x0010;
    LATF = 0x0020;
        // RF4(U2RX) is input.
        // RF5(U2TX) to level high.

    LATG= 0x0200;
    TRISG= 0x0080;
        // RG6(SCK2)   output, MMC_SCK
        // RG7(SDI2)   input,  MMC_SDO
        // RG8(SDO2)   output, MMC_SDI
        // RG9(CS)     output, MMC_CS   initial level high

    //--- internal pullup
    CNPUEbits.CNPUE7=1;	// RB5(CN7) MMC_CD Pull-up
                        // other pins low level output, don't pull up.

} // InitializeSystem


/*==============================================================================
	main
===============================================================================*/

int main ( void )
{
    int  c;

    // Initialize the processor and peripherals.
    InitializeSystem();

    timer_init();
    display_init();
    sound_init();

    putstr("SONO-SYSTEM on SBDBT32(PIC32MX)\r\n\r\n");

    USBTasks();

    if(getHIDnumOfDevice(HID_KEYBOARD)==0){
        putstr("USB Keyboard detecting...\r\n");
        while(1) {
            USBTasks();
            if(getHIDnumOfDevice(HID_KEYBOARD)>0){
                sound_start(13681, 500);
                basic();
            }
        }
    }else{
        basic();
    }

    return 0;
}
/**** end of main.c ************************************************************/
