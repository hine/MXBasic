//
//
//		2012.6.26 S.Suwa     http://www.suwa-koubou.jp
//
//		update:
//          2013/11/13   Support multiple HID device 
/*********************************************************************************
                                                                                
Software License Agreement                                                      
                                                                                
Copyright � 2007-2008 Microchip Technology Inc. and its licensors.  All         
rights reserved.                                                                
                                                                                
Microchip licenses to you the right to: (1) install Software on a single        
computer and use the Software with Microchip 16-bit microcontrollers and        
16-bit digital signal controllers ("Microchip Product"); and (2) at your        
own discretion and risk, use, modify, copy and distribute the device            
driver files of the Software that are provided to you in Source Code;           
provided that such Device Drivers are only used with Microchip Products         
and that no open source or free software is incorporated into the Device        
Drivers without Microchip's prior written consent in each instance.             
                                                                                
You should refer to the license agreement accompanying this Software for        
additional information regarding your rights and obligations.                   
                                                                                
SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY         
KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY              
WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A          
PARTICULAR PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE             
LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY,               
CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY           
DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY         
INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR         
LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY,                 
SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY         
DEFENSE THEREOF), OR OTHER SIMILAR COSTS.                                       
                                                                                
*********************************************************************************/

// Created by the Microchip USBConfig Utility, Version 0.0.12.0, 3/28/2008, 8:58:18

#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
//#include "USB/usb.h"
//#include "USB/usb_host_generic.h"
#include "usb.h"

#include "usb_host_hid.h"


// *****************************************************************************
// Client Driver Function Pointer Table for the USB Embedded Host foundation
// *****************************************************************************

CLIENT_DRIVER_TABLE usbClientDrvTable[] =
{                                        
    {   // #0 HID(keyboard) driver
        USBHostHIDInitialize,
        USBHostHIDEventHandler,
#ifdef USB_HOST_APP_DATA_EVENT_HANDLER
	NULL,                                // Data Event routine
#endif
        0
    }, 

    {   // #1 HID(mouse) driver
        USBHostHIDInitialize,
        USBHostHIDEventHandler,
#ifdef USB_HOST_APP_DATA_EVENT_HANDLER
	NULL,                                // Data Event routine
#endif
        0
    }, 

    {   // #2 HID(joystick) driver
        USBHostHIDInitialize,
        USBHostHIDEventHandler,
#ifdef USB_HOST_APP_DATA_EVENT_HANDLER
	NULL,                                // Data Event routine
#endif
        0
    }, 


};

// *****************************************************************************
// USB Embedded Host Targeted Peripheral List (TPL)
// *****************************************************************************

USB_TPL usbTPL[] =
{
   // idVendor, idProduct, bConfiguration, index of ClientDriver, flags(HNP,Class,Config)
   // bClass, bSubClass, bProtocol, bConfiguration, index of ClientDriver, flags(HNP,Class,Config)
   // HID devices
     { INIT_CL_SC_P( 3ul,       1ul,    1ul ), 0, 0, {TPL_CLASS_DRV} }, // HID keyboard sub class=1, protocol=1
     { INIT_CL_SC_P( 3ul,       1ul,    2ul ), 0, 1, {TPL_CLASS_DRV} }, // HID mouse    sub class=1, protocol=2
     { INIT_CL_SC_P( 3ul,       0ul,    0ul ), 0, 2, {TPL_CLASS_DRV} }, // HID gamepad, joystick, etc.
};

// Numbers of TPL
BYTE getNumTPLs(void)
{
	return sizeof(usbTPL)/sizeof(usbTPL[0]);
}

