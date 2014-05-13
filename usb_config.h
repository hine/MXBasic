/*==================================================================================

	usb_config.h

    2013/4/15 S.Suwa    http://www.suwa-koubou.jp

	update:
        2013/11/13    support multiple HID devices
        2014/01/13    support multiple USB HUBs (support cascade Hub)
===================================================================================*/

#ifndef	__USB_CONFIG_H
#define	__USB_CONFIG_H

#include "Compiler.h"

#define USB_SUPPORT_HOST
#define USB_PING_PONG_MODE  USB_PING_PONG__FULL_PING_PONG

#define NUM_TPL_ENTRIES getNumTPLs()	// getNumTPLs() function was defined in usb_config.c. 

#define USB_SUPPORT_INTERRUPT_TRANSFERS	// HUB HID
#define USB_SUPPORT_BULK_TRANSFERS      // MSD, FinePix
// #define USB_SUPPORT_ISOCHRONOUS_TRANSFERS    // UVC webcam device use isochoronous transfer.

#define USB_ENABLE_TRANSFER_EVENT
//#define USB_ENABLE_ISOC_TRANSFER_EVENT 	// EVENT TRANSFER too slowly, I don't use transfer event.



#define USB_NUM_CONTROL_NAKS 1000 //  20
#define USB_NUM_INTERRUPT_NAKS 5 // 3
#define USB_NUM_BULK_NAKS 20000

#define USB_INITIAL_VBUS_CURRENT (100/2)
#define USB_INSERT_TIME (250+1)
#define USB_HOST_APP_EVENT_HANDLER        USB_ApplicationEventHandler // in Application main.c
#define USB_HOST_APP_DATA_EVENT_HANDLER   USB_ApplicationDataEventHandler // in Application main.c

// I willn't use data event handler routine.
#ifdef USB_HOST_APP_DATA_EVENT_HANDLER
    #undef USB_HOST_APP_DATA_EVENT_HANDLER
#endif

// Support multiple Hub, number of down stream ports     2014/01/13 S.Suwa
#define	USB_HUB_NUMBER_OF_DOWN_STREAM_PORTS      12    // Using three hubs, Each hubs has four ports. Total twelve ports.

// Host HID Client Driver Configuration
//#define USB_MAX_HID_DEVICES 1
#define USB_MAX_HID_DEVICES  USB_HUB_NUMBER_OF_DOWN_STREAM_PORTS

//#define HID_MAX_DATA_FIELD_SIZE 8
#define HID_MAX_DATA_FIELD_SIZE 16    // need 16bit

//#define APPL_COLLECT_PARSED_DATA USB_HID_DataCollectionHandler

// Host MSD Client Driver Configuration
#define USB_MAX_MASS_STORAGE_DEVICES             1

extern	void	USBHostHIDTasks(void);

#define USBTasks()                  \
    {                               \
        USBHostTasks();             \
        USBHostHIDTasks();          \
    }

#define USBInitialize(x)            \
    {                               \
        USBHostInit(x);             \
    }

// function prototype, get Numbers of TPL
BYTE getNumTPLs(void);


#endif	// __USB_CONFIG_H

/*** end of usb_config.h ************************************************************/
