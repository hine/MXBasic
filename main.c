/******************************************************************************

    main.c

    Test demo program for multiple HID devices.

    Test hardware is SBDBT32 board, it has PIC32MX695F512H.

    (C) S.Suwa 2013/11/22       http://www.suwa-koubou.jp

    2013/11/22 support multiple HID device.
               mouse, keyboard, joystick

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
#include "display.h"
#include "character.h"
#include "ttbasic.h"
#include "uart2.h"


/*------------------------------------------------------------------------------
	Configuration for PIC32MX695F 
------------------------------------------------------------------------------*/

#include "p32mx695f_config.h"


/*------------------------------------------------------------------------------
	definition
------------------------------------------------------------------------------*/

//#define	putstr(x)	UART2PrintString(x)
#define	inkey()		UART2IsPressed()
//#define	getch()		UART2GetChar()
//#define	puthex(x)	UART2PutHex(x)
//#define	putch(x)	UART2PutChar(x)
//#define	putdec(x)	UART2PutDec(x)


/*------------------------------------------------------------------------------
	function prototype
------------------------------------------------------------------------------*/

void	InitializeSystem (void);
int     main (void);
void    keyboard_test(void);
BYTE    toAscii(USB_KEYBOARD_DATA *data);

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

    /*
     * Init UART
     *
     * caution:
     *  SBDBT32 must use UART1�@because UART2 is not usable.
     *  I corrected 'uart2.c', in order to use UART1 instead of UART2 by USE_SBDBT32 macro switch. 
     *  Please see 'uart2.c' and 'uart2to1.c'.
     */
    //UART2Init();

} // InitializeSystem


/*============================================================================================
	BOOL USB_ApplicationEventHandler ( BYTE address, USB_EVENT event, void *data, DWORD size )
============================================================================================*/

BOOL USB_ApplicationEventHandler ( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    //putstr("EVENT:"); putdec(event); putstr("\r\n");

    // Handle specific events.
    switch (event){

    case EVENT_OVERRIDE_CLIENT_DRIVER_SELECTION:
        return FALSE;
 
    case EVENT_VBUS_RELEASE_POWER:
    case EVENT_VBUS_REQUEST_POWER:
    case EVENT_UNSUPPORTED_DEVICE:
    case EVENT_CANNOT_ENUMERATE:
    case EVENT_CLIENT_INIT_ERROR:
    case EVENT_OUT_OF_MEMORY:
    case EVENT_UNSPECIFIED_ERROR:
        break;

    default:
       break;
   }

   return TRUE;

} // USB_ApplicationEventHandler


/*-------------------------------------------------------------------------------
	BOOL USB_ApplicationDataEventHandler ( BYTE address, USB_EVENT event, void *data, DWORD size )
-------------------------------------------------------------------------------*/

BOOL USB_ApplicationDataEventHandler ( BYTE address, USB_EVENT event, void *data, DWORD size )
{
	return TRUE;
}


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

    putstr("SBDBT32 system\r\n\r\n");

    USBTasks();

    if(getHIDnumOfDevice(HID_KEYBOARD)==0){
        putstr("USB Keyboard detecting...\r\n");
        while(1) {
            USBTasks();
            if(getHIDnumOfDevice(HID_KEYBOARD)>0){
                // keyboard_test();
                basic();
            }
        }
    }else{
        keyboard_test();
        basic();
    }

    return 0;
}


/*===============================================================================
	keyboard test (added this test function, 2013/11/13)
===============================================================================*/

void	keyboard_test(void)
{
	USB_KEYBOARD_DATA   keyd;
	int rc;
	BYTE c, prev;


	putstr("\r\n*** Start USB keyboard test. \r\n");
	putstr("Please press a key of USB keyboard.\r\n");
	putstr(" If you press Ctrl+C, to stop the keyboard test.\r\n"); 

	for(c = prev = 0;;){

		do {
			rc = keyboard_read(1, &keyd);
			if(rc == -1){
				putstr("\r\nKeyboard detached. Stop the keyboard test! \r\n");
				return;
			}
		}while(rc == 0);

		if((keyd.modifier.left_ctrl || keyd.modifier.right_ctrl) &&
			keyd.keycode[0] == 0x06){
				putstr("\r\nYou pressed Ctrl+C, to stop the keyborad test! \r\n");
				return;
		}

		c = toAscii(&keyd);
		if(c && c != prev) putch(c);
		if(c == '\r') putch('\n');
		prev = c;

	}

}

BYTE	getch(void)
{
    USB_KEYBOARD_DATA   keyd;
    int rc;
    BYTE c, prev;

    do {
        rc = keyboard_read(1, &keyd);
        if(rc == -1){
            putstr("\r\nKeyboard detached. Stop the keyboard test! \r\n");
            return;
        }
    }while(rc == 0);

    c = toAscii(&keyd);
    return c;
}

BYTE	kbhit(void)
{
    USB_KEYBOARD_DATA   keyd;
    int rc;
    BYTE c, prev;

    rc = keyboard_read(1, &keyd);
    if(rc == -1){
        putstr("\r\nKeyboard detached. Stop the keyboard test! \r\n");
        return -1;
    }

    if (rc) {
        c = toAscii(&keyd);
        return c;
    }

    return 0;
}

/*------------------------------------------------------------------------------
	BYTE toAscii()
------------------------------------------------------------------------------*/

const BYTE tblAscii[]={
/*           00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F */
/*00-0f*/     0,  0,  0,  0,'a','b','c','d','e','f','g','h','i','j','k','l',
/*10-1f*/   'm','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2',
/*20-2f*/   '3','4','5','6','7','8','9','0','\r', 0,0x08,'\t',' ','-','^','@',
/*30-3f*/   '[',  0,']',';',':', 0 ,',','.','/',  0,  0,  0,  0,  0,  0,  0,
/*40-4f*/     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/*50-5f*/     0,  0,  0,  0,'/','*','-','+',  0,'1','2','3','4','5','6','7',
/*60-6f*/   '8','9','0',  0,  0,  0,  0,'\\',  0,'\\',  0,  0,  0,  0,  0,  0,
};

const BYTE tblAsciiWithShift[]={
/*           00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F */
/*00-0f*/     0,  0,  0,  0,'A','B','C','D','E','F','G','H','I','J','K','L',
/*10-1f*/   'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','!','"',
/*20-2f*/   '#','$','%','&','\'','(',')','0','\r', 0,0x08,'\t',' ','=','~','`',
/*30-3f*/   '{',  0,'}','+','*',  0,'<','>','?',  0,  0,  0,  0,  0,  0,  0,
/*40-4f*/     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/*50-5f*/     0,  0,  0,  0,'/','*','-','+',  0,'1','2','3','4','5','6','7',
/*60-6f*/   '8','9','0',  0,  0,  0,  0,'_',  0,'|',  0,  0,  0,  0,  0,  0,
};
 
BYTE toAscii(USB_KEYBOARD_DATA *data)
{
	if(data->keycode[0] == 0x87 || data->keycode[0] == 0x89)data->keycode[0] -= 0x20;

	if(data->keycode[0] >= 0x70) return 0;

	if(data->modifier.left_shift || data->modifier.right_shift){
		return tblAsciiWithShift[data->keycode[0]];

	}else if(data->keycode[0] <= 0x1d && data->modifier.capslock){
		return tblAsciiWithShift[data->keycode[0]];

	}else{
		return tblAscii[data->keycode[0]];
	}
}


/**** end of main.c ************************************************************/
