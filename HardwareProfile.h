// HardwareProfile.h

#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_

// ******************* CPU Speed defintions ************************************
//  This section is required by some of the peripheral libraries and software
//  libraries in order to know what the speed of the processor is to properly
//  configure the hardware modules to run at the proper speeds
// *****************************************************************************

#if defined (__C30__)	// PIC24FJ64GB002/PIC24FJ256GB106/PIC24FJ256DA206
    // Various clock values
    #define GetSystemClock()            32000000UL
    #define GetPeripheralClock()        (GetSystemClock())
    #define GetInstructionClock()       (GetSystemClock() / 2)

#elif defined( __PIC32MX__)
	#define USE_USB_PLL
    //#define USB_A0_SILICON_WORK_AROUND
	#if defined (__32MX220F032B__)
		#define	RUN_AT_40MHz
	#elif defined (__32MX695F512H__)

    	#define RUN_AT_80MHZ
    	#define USE_SBDBT32         // use SBDBT32 micom-board, change UART2 to UART1
	#else
		#error "Not found PIC32 processor"
	#endif

    // Various clock values
    #if defined(RUN_AT_24MHZ)
        #define GetSystemClock()            24000000UL
        #define GetPeripheralClock()        24000000UL
        #define GetInstructionClock()       24000000UL 
    #elif defined(RUN_AT_40MHZ)
        #define GetSystemClock()            40000000UL
        #define GetPeripheralClock()        40000000UL
        #define GetInstructionClock()       40000000UL 
    #elif defined(RUN_AT_48MHZ)
        #define GetSystemClock()            48000000UL
        #define GetPeripheralClock()        48000000UL
        #define GetInstructionClock()       48000000UL 
    #elif defined(RUN_AT_60MHZ)    
        #define GetSystemClock()            60000000UL
        #define GetPeripheralClock()        60000000UL  // Will be divided down
        #define GetInstructionClock()       60000000UL 
    #elif defined(RUN_AT_80MHZ)    
        #define GetSystemClock()            80000000UL
        #define GetPeripheralClock()        80000000UL  // Will be divided down
        #define GetInstructionClock()       80000000UL 
    #else
        #error "Undefined PIC32 clock speeds"
    #endif        
#else
        #error "Undefined processor family"
#endif

// ******************* MDD File System Required Definitions ********************
// Select your MDD File System interface type
// This library currently only supports a single physical interface layer
// In this example we are going to use the USB so we only need the USB definition
// *****************************************************************************
#define USE_USB_INTERFACE               // USB host MSD library


// ******************* Debugging interface hardware settings *******************
//  This section is not required by any of the libraries.  This is a
//  demo specific implmentation to assist in debugging.  
// *****************************************************************************
// Define the baud rate constants
//#define BAUDRATE2       57600 //19200
#define BAUDRATE2       115200 //19200
#define BRG_DIV2        4 //16
#define BRGH2           1 //0

#define DEMO_TIMEOUT_LIMIT  0xF000

#if defined(__PIC24F__) || defined(__PIC24H__)
    #include <p24fxxxx.h>
    //#include <uart2.h>
#elif defined(__PIC32MX__)
    #include <p32xxxx.h>
    #include <plib.h>
    //#include <uart2.h>
#else
	#error "Undefined processor family"
#endif

// #include "uart2.h"

#endif  // _HARDWAREPROFILE_H_
