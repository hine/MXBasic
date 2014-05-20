/*******************************************************************************

	usb_host_hid_device.c

	multiple HID device support

	mouse, keybord, joystick 

    2013/11/22    Suwa   http://www.suwa-koubou.jp

*******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
//#include "uart2.h"
#include "character.h"
#include "usb_config.h"
#include "usb.h"
#include "usb_host_hid_parser.h"
#include "usb_host_hid.h"
#include "usb_host_hid_device.h"

//#define	DEBUG_MODE


// *** structures **************************************************************
typedef enum _APP_STATE
{
    DEVICE_NOT_CONNECTED = 0,
    DEVICE_CONNECTED,        /* Device Enumerated  - Report Descriptor Parsed */
    READY_TO_TX_RX_REPORT,
    GET_INPUT_REPORT,        /* perform operation on received report */
    INPUT_REPORT_PENDING,
    SEND_OUTPUT_REPORT,      /* Not needed in case of mouse */
    OUTPUT_REPORT_PENDING,
    ERROR_REPORTED 
} APP_STATE;


typedef struct _HID_REPORT_BUFFER	// mouse, keyboard, joystick etc.
{
    WORD  Report_ID;
    WORD  ReportSize;
    BYTE* ReportData;
    WORD  ReportPollRate;
}   HID_REPORT_BUFFER;


typedef struct _HID_LED_REPORT_BUFFER // keyboard only
{
    BYTE  NUM_LOCK      : 1;
    BYTE  CAPS_LOCK     : 1;
    BYTE  SCROLL_LOCK   : 1;
    BYTE  UNUSED        : 5;
}   HID_LED_REPORT_BUFFER;


// *** Macros ******************************************************************
// item of report descripter
#define MINIMUM_POLL_INTERVAL           (0x0A)        // Minimum Polling rate for HID reports is 10ms
#define USAGE_PAGE_GEN_DESKTOP          (0x01)
#define USAGE_PAGE_BUTTONS              (0x09)
#define USAGE_PAGE_LEDS                 (0x08)
#define USAGE_PAGE_KEY_CODES            (0x07)
#define USAGE_MIN_MODIFIER_KEY          (0xE0)
#define USAGE_MAX_MODIFIER_KEY          (0xE7)
#define USAGE_MIN_NORMAL_KEY            (0x00)
#define USAGE_MAX_NORMAL_KEY            (0xFF)
#define HID_CAPS_LOCK_VAL               (0x39)
#define HID_NUM_LOCK_VAL                (0x53)

// Usage ID of Generic Desktop Page(0x01)
#define USAGE_POINTER                   (0x01)
#define USAGE_MOUSE                     (0x02)
#define USAGE_JOYSTICK                  (0x04)
#define USAGE_GAMEPAD                   (0x05)
#define	USAGE_KEYBOARD                  (0x06)
#define USAGE_KEYPAD                    (0x07)
#define USAGE_MULTI_AXIS                (0x08)
#define USAGE_TABLET                    (0x09)

#define MAX_DEVICES                     (USB_MAX_HID_DEVICES+2)   // deviceAddress= HUB PortNumber +1
#define MAX_ERROR_COUNTER               (10)

#ifndef USB_MALLOC
    #define USB_MALLOC(size) malloc(size)
#endif

#ifndef USB_FREE
    #define USB_FREE(ptr) free(ptr)
#endif

#ifndef USB_FREE_AND_CLEAR
    #define USB_FREE_AND_CLEAR(ptr) {USB_FREE(ptr); ptr = NULL;}
#endif


// *** Global Function Prototypes **********************************************
int keyboard_read(int num, USB_KEYBOARD_DATA *data);
BOOL USB_HIDDeviceEventHandler(BYTE address, USB_EVENT event, void *data, DWORD size);

// *** Private Function Prototypes *******************************************************
static int  searchDevice(BYTE device, int num);
static BOOL hid_device_read(BYTE deviceAddress, void *data);
static void setHIDDeviceType(BYTE deviceAddress, BYTE *rptDescriptor);

static void App_ProcessInputReport(BYTE deviceAddress, void *data);
static void App_KeyboardInputReport(BYTE deviceAddress, USB_KEYBOARD_DATA *data);

static void App_PrepareOutputReport(BYTE deviceAddress);

static BOOL USB_HID_DataCollectionHandler(BYTE deviceAddress);
static BOOL USB_HID_KEYBOARD_DataCollectionHandler(BYTE deviceAddress);


// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************

// HID device name
static char *deviceName[HID_MAX_DEVICETYPE] = {
    "unknown", "mouse", "joystick",
    "gamepad", "keyboard", "keypad",
};

// number of connecting device
static int numOfDevice[HID_MAX_DEVICETYPE];

// *** each device ******************* 
static APP_STATE             App_State[MAX_DEVICES]; // Initial value is DEVICE_NOT_CONNECTED.
static BYTE                  deviceType[MAX_DEVICES]; // Initial value is HID_UNKNOWN	
static HID_REPORT_BUFFER     Appl_raw_report_buffer[MAX_DEVICES];
static BYTE                  ErrorDriver[MAX_DEVICES];
static BYTE                  ErrorCounter[MAX_DEVICES];
static BYTE                  NumOfBytesRcvd[MAX_DEVICES];
static BOOL                  ReportBufferUpdated[MAX_DEVICES];

// *** keyboards *************** 
static HID_DATA_DETAILS      Appl_ModifierKeysDetails[MAX_DEVICES];
static HID_DATA_DETAILS      Appl_NormalKeysDetails[MAX_DEVICES];
static HID_DATA_DETAILS      Appl_LED_Indicator[MAX_DEVICES];
static HID_USER_DATA_SIZE    Appl_BufferModifierKeys[8];
static HID_USER_DATA_SIZE    Appl_BufferNormalKeys[6];
static HID_LED_REPORT_BUFFER Appl_led_report_buffer[MAX_DEVICES];
static BOOL                  LED_Key_Pressed[MAX_DEVICES];
static BYTE                  CAPS_Lock_Pressed[MAX_DEVICES];
static BYTE                  NUM_Lock_Pressed[MAX_DEVICES];


// *****************************************************************************
// *****************************************************************************
// Section: Application Callable Functions
// *****************************************************************************
// *****************************************************************************

/*==============================================================================
	int getHIDnumOfDevice(BYTE devicetype)
==============================================================================*/

int getHIDnumOfDevice(BYTE devicetype)
{
	if(devicetype >= HID_MAX_DEVICETYPE) return 0;
	return numOfDevice[devicetype];
}


/*==============================================================================
	int devicename_read(int num, USB_DEVICENAME_DATA *data)

	first argumnet 'num' is number of connecting mouse 
	return code = 1  read complete
                = 0  not ready, read pending
                =-1  device not connected
==============================================================================*/

int keyboard_read(int num, USB_KEYBOARD_DATA *data)
{
	int adr;

	memset(data, 0, sizeof(USB_KEYBOARD_DATA));
	if((adr = searchDevice(HID_KEYBOARD, num)) != -1){
		if(hid_device_read(adr, data)) return 1;
		else return 0;
	}else{
		return -1;
	}
}


// *****************************************************************************
// *****************************************************************************
// Section: HID Device Event Handler
// *****************************************************************************
// *****************************************************************************

BOOL USB_HIDDeviceEventHandler ( BYTE address, USB_EVENT event, void *data, DWORD size )
{

    // Handle specific events.
    switch (event){

        case EVENT_HID_ATTACH:
            putstr("\r\n"); putstr(deviceName[deviceType[address]]); putstr(" attached.\r\n");
            //putstr(" device address="); putdec(address); putstr("\r\n");

            // update numOfDevice
            numOfDevice[deviceType[address]]++;
            break;

        case EVENT_HID_DETACH:
            putstr("\r\n"); putstr(deviceName[deviceType[address]]); putstr(" detached.\r\n");
            //putstr(" device address="); putdec(address); putstr("\r\n\r\n");

            // update numOfDevice
            numOfDevice[deviceType[address]]--;
            if(Appl_raw_report_buffer[address].ReportData){
                USB_FREE_AND_CLEAR(Appl_raw_report_buffer[address].ReportData);
            }
            deviceType[address] = HID_UNKNOWN;
            break;

        case EVENT_HID_READ_DONE:
        case EVENT_HID_WRITE_DONE:
        case EVENT_HID_BAD_REPORT_DESCRIPTOR:
            break;

        case EVENT_HID_RPT_DESC_PARSED:
#ifdef DEBUG_MODE
            //UART2PrintString( "\r\nHID: device report descriptor parsed\r\n" );
            putstr( "\r\nHID: device report descriptor parsed\r\n" );
#endif
            setHIDDeviceType(address, (BYTE *)data);
            return USB_HID_DataCollectionHandler(address);

        default:
            break;
    }

    return TRUE;

} // USB_HIDDeviceEventHandler


// *****************************************************************************
// *****************************************************************************
// Section: Private Functions
// *****************************************************************************
// *****************************************************************************

/*==============================================================================
	searchDevice(BYTE device, int num)
==============================================================================*/

static int searchDevice(BYTE device, int num)
{
    int i;

    // search device
    for(i = 0; i < MAX_DEVICES; i++){
        if(deviceType[i] == device){
            if(--num == 0){
                return i;	// return value is deviceAddress.
            }
        }
    }
    return -1;
}


/*==============================================================================
	hid_device_read() 

	result code TRUE   read complete
                FALSE  do not complete, unready or read pending

	void *data
          case keyboard  USB_KEYBOARD_DATA *data
==============================================================================*/

static BOOL hid_device_read(BYTE deviceAddress, void *data)
{
    // call usb host layer
    USBTasks();

    // Was device detached?
    // Or, was report descriptor parsed with error.?
    if(!USBHostHIDDeviceDetect(deviceAddress)){
        App_State[deviceAddress] = DEVICE_NOT_CONNECTED;
    }

    switch(App_State[deviceAddress]){
        case DEVICE_NOT_CONNECTED:
            USBTasks();
            /* True if report descriptor is parsed with no error */
            if(USBHostHIDDeviceDetect(deviceAddress)){
                App_State[deviceAddress] = DEVICE_CONNECTED;
            }
            break;

        case DEVICE_CONNECTED:
            App_State[deviceAddress] = READY_TO_TX_RX_REPORT;
            break;

        case READY_TO_TX_RX_REPORT:
            if(USBHostHIDDeviceDetect(deviceAddress)){
                App_State[deviceAddress] = GET_INPUT_REPORT;
            }else{
                App_State[deviceAddress] = DEVICE_NOT_CONNECTED;
            }
            break;

        case GET_INPUT_REPORT:
            if(!USBHostHIDRead(deviceAddress, Appl_raw_report_buffer[deviceAddress].Report_ID,0,
                    Appl_raw_report_buffer[deviceAddress].ReportSize, Appl_raw_report_buffer[deviceAddress].ReportData)){
                App_State[deviceAddress] = INPUT_REPORT_PENDING;
            }
            break;

        case INPUT_REPORT_PENDING:
            if(USBHostHIDTransferIsComplete(deviceAddress, &ErrorDriver[deviceAddress],&NumOfBytesRcvd[deviceAddress])){
                if(ErrorDriver[deviceAddress] ||(NumOfBytesRcvd[deviceAddress] != Appl_raw_report_buffer[deviceAddress].ReportSize )){
                    ErrorCounter[deviceAddress]++ ;
                    if(MAX_ERROR_COUNTER <= ErrorDriver[deviceAddress]){
                        App_State[deviceAddress] = ERROR_REPORTED;
                    }else{
                        App_State[deviceAddress] = READY_TO_TX_RX_REPORT;
                    }
                }else{
                    ErrorCounter[deviceAddress] = 0;
                    ReportBufferUpdated[deviceAddress] = TRUE;
                    App_State[deviceAddress] = READY_TO_TX_RX_REPORT;

                    App_ProcessInputReport(deviceAddress, data);
                    App_PrepareOutputReport(deviceAddress);
                    return TRUE;
                }
            }
            break;

        case SEND_OUTPUT_REPORT: /* Will be done while implementing Keyboard */
            if(!USBHostHIDWrite(deviceAddress, Appl_LED_Indicator[deviceAddress].reportID, Appl_LED_Indicator[deviceAddress].interfaceNum, Appl_LED_Indicator[deviceAddress].reportLength,
                    (BYTE*)&Appl_led_report_buffer[deviceAddress])){
                App_State[deviceAddress] = OUTPUT_REPORT_PENDING;
            }
            break;

        case OUTPUT_REPORT_PENDING:
            if(USBHostHIDTransferIsComplete(deviceAddress, &ErrorDriver[deviceAddress],&NumOfBytesRcvd[deviceAddress])){
                if(ErrorDriver[deviceAddress]){
                    ErrorCounter[deviceAddress]++ ;
                    if(MAX_ERROR_COUNTER <= ErrorDriver[deviceAddress]){
                        App_State[deviceAddress] = ERROR_REPORTED;
                    }
                }else{
                    ErrorCounter[deviceAddress] = 0;
                    App_State[deviceAddress] = READY_TO_TX_RX_REPORT;
                }
            }
            break;

        case ERROR_REPORTED:	// forever error loop
            break;

        default:
            break;
    }

    // ReportData isn't ready!
    return FALSE;
}


/*------------------------------------------------------------------------------
    void App_ProcessInputReport()
------------------------------------------------------------------------------*/

static void App_ProcessInputReport(BYTE deviceAddress, void *data)
{
    switch(deviceType[deviceAddress]){
	case HID_KEYBOARD:
		App_KeyboardInputReport(deviceAddress, (USB_KEYBOARD_DATA *)data);
		break;
    }
}

static void App_KeyboardInputReport(BYTE deviceAddress, USB_KEYBOARD_DATA *data)
{
    int i;
    /* process input report received from device */
    USBHostHID_ApiImportData(Appl_raw_report_buffer[deviceAddress].ReportData, Appl_raw_report_buffer[deviceAddress].ReportSize
            ,Appl_BufferModifierKeys, &Appl_ModifierKeysDetails[deviceAddress]);
    USBHostHID_ApiImportData(Appl_raw_report_buffer[deviceAddress].ReportData, Appl_raw_report_buffer[deviceAddress].ReportSize
            ,Appl_BufferNormalKeys, &Appl_NormalKeysDetails[deviceAddress]);

#ifdef DEBUG_MODE
    int i;
    putstr( "HID: Raw Report \r\n");
    putstr("ReportSize="); putdec(Appl_raw_report_buffer[deviceAddress].ReportSize);putstr("\r\n");
    for(i=0;i<(Appl_raw_report_buffer[deviceAddress].ReportSize);i++){
        puthex( Appl_raw_report_buffer[deviceAddress].ReportData[i]);
    }
    putstr("\r\n");
#endif

    // modifier
    *((BYTE *)&(data->modifier)) = Appl_raw_report_buffer[deviceAddress].ReportData[0];
    // keycode
    memcpy(data->keycode, &(Appl_raw_report_buffer[deviceAddress].ReportData[2]), 3);

    // check CapsLock NumericLock
    for(i=2;i<(Appl_raw_report_buffer[deviceAddress].ReportSize);i++){
        if(Appl_raw_report_buffer[deviceAddress].ReportData[i] != 0){
            if(Appl_raw_report_buffer[deviceAddress].ReportData[i] == HID_CAPS_LOCK_VAL){
                CAPS_Lock_Pressed[deviceAddress] = !CAPS_Lock_Pressed[deviceAddress];
                LED_Key_Pressed[deviceAddress] = TRUE;
                Appl_led_report_buffer[deviceAddress].CAPS_LOCK = CAPS_Lock_Pressed[deviceAddress];
            }else if(Appl_raw_report_buffer[deviceAddress].ReportData[i] == HID_NUM_LOCK_VAL){
                NUM_Lock_Pressed[deviceAddress] = !NUM_Lock_Pressed[deviceAddress];
                LED_Key_Pressed[deviceAddress] = TRUE;
                Appl_led_report_buffer[deviceAddress].NUM_LOCK = NUM_Lock_Pressed[deviceAddress];
            }
        }
    }

    if(CAPS_Lock_Pressed[deviceAddress]) data->modifier.capslock=1;
    else  data->modifier.capslock=0;

    if(NUM_Lock_Pressed[deviceAddress])  data->modifier.numlock=1;
    else  data->modifier.numlock=0;

    // clear receive buffer
    for(i=0;i<Appl_raw_report_buffer[deviceAddress].ReportSize;i++){
        Appl_raw_report_buffer[deviceAddress].ReportData[i] = 0;
    }

}


/*------------------------------------------------------------------------------
    void App_PrepareOutputReport()
	    Now, only support for keyboard
------------------------------------------------------------------------------*/

static void App_PrepareOutputReport(BYTE deviceAddress)
{
    switch(deviceType[deviceAddress]){
        case HID_KEYBOARD:
            if(ReportBufferUpdated[deviceAddress] == TRUE){
                ReportBufferUpdated[deviceAddress] = FALSE;
                if(LED_Key_Pressed[deviceAddress]){
                    App_State[deviceAddress] = SEND_OUTPUT_REPORT;
                    LED_Key_Pressed[deviceAddress] = FALSE;
                }
            }
            break;
    }
}


/*------------------------------------------------------------------------------
	setHIDDeviceType(BYTE deviceAddress);
------------------------------------------------------------------------------*/

static void setHIDDeviceType(BYTE deviceAddress, BYTE *rptDescriptor)
{
    static BYTE typeTable[] = {
        HID_UNKNOWN,	// 0
        HID_UNKNOWN,    // 1 USAGE_POINTER
        HID_MOUSE,      // 2 USAGE_MOUSE
        HID_UNKNOWN,    // 3
        HID_JOYSTICK,   // 4 USAGE_JOYSTICK
        HID_GAMEPAD,    // 5 USAGE_GAMEPAD
        HID_KEYBOARD,	// 6 USAGE_KEYBOARD
        HID_KEYPAD,     // 7 USAGE_KEYPAD
    };
    BYTE usagePage;
    BYTE usageId;

    usagePage = rptDescriptor[1];
    usageId = rptDescriptor[3];

    // already set
    if(deviceType[deviceAddress]!=HID_UNKNOWN) return;

    if( usagePage == USAGE_PAGE_GEN_DESKTOP &&
            (usageId >= USAGE_MOUSE && usageId <= USAGE_KEYPAD) ){
        deviceType[deviceAddress] = typeTable[usageId];
    }else{
        deviceType[deviceAddress] = HID_UNKNOWN;
    }
}


/*------------------------------------------------------------------------------
	USB_HID_DataCollectionHandler()

	macro in usb_config.h
	#define APPL_COLLECT_PARSED_DATA USB_HID_DataCollectionHandler

	This function was called in USB_ApplicationEventHandler function.
------------------------------------------------------------------------------*/

static BOOL USB_HID_DataCollectionHandler(BYTE deviceAddress)
{
    switch(deviceType[deviceAddress]){
        case HID_KEYBOARD:
#ifdef DEBUG_MODE
            putstr("Keyboard DataCollection.\r\n");
#endif
            return USB_HID_KEYBOARD_DataCollectionHandler(deviceAddress);

        default: // other
#ifdef DEBUG_MODE
            putstr("Unsupported device.\r\n");
#endif
            return FALSE;
    }
}


static BOOL USB_HID_KEYBOARD_DataCollectionHandler(BYTE deviceAddress)
{
    BYTE                     NumOfReportItem;
    BYTE                     i;
    USB_HID_ITEM_LIST       *pitemListPtrs;
    USB_HID_DEVICE_RPT_INFO *pDeviceRptinfo;
    HID_REPORTITEM          *reportItem;
    HID_USAGEITEM           *hidUsageItem;
    BYTE                     usageIndex;
    BYTE                     reportIndex;
    BOOL                     foundLEDIndicator = FALSE;
    BOOL                     foundModifierKey = FALSE;
    BOOL                     foundNormalKey = FALSE;
    BOOL                     status;

    pDeviceRptinfo = USBHostHID_GetCurrentReportInfo(); // Get current Report Info pointer
    pitemListPtrs = USBHostHID_GetItemListPointers();   // Get pointer to list of item pointers

    foundLEDIndicator = foundModifierKey = foundNormalKey = FALSE;
    status = FALSE;
    reportIndex = 0;
    NumOfReportItem = pDeviceRptinfo->reportItems;

    for(i=0;i<NumOfReportItem;i++){
        reportItem = &pitemListPtrs->reportItemList[i];
        if((reportItem->reportType==hidReportInput) && (reportItem->dataModes == HIDData_Variable)&&
                (reportItem->globals.usagePage==USAGE_PAGE_KEY_CODES)){
            usageIndex = reportItem->firstUsageItem;
            hidUsageItem = &pitemListPtrs->usageItemList[usageIndex];
            if((hidUsageItem->usageMinimum == USAGE_MIN_MODIFIER_KEY)
                    &&(hidUsageItem->usageMaximum == USAGE_MAX_MODIFIER_KEY)){ //else application cannot suuport

                reportIndex = reportItem->globals.reportIndex;
                Appl_ModifierKeysDetails[deviceAddress].reportLength = (pitemListPtrs->reportList[reportIndex].inputBits + 7)/8;
                Appl_ModifierKeysDetails[deviceAddress].reportID = (BYTE)reportItem->globals.reportID;
                Appl_ModifierKeysDetails[deviceAddress].bitOffset = (BYTE)reportItem->startBit;
                Appl_ModifierKeysDetails[deviceAddress].bitLength = (BYTE)reportItem->globals.reportsize;
                Appl_ModifierKeysDetails[deviceAddress].count=(BYTE)reportItem->globals.reportCount;
                Appl_ModifierKeysDetails[deviceAddress].interfaceNum= USBHostHID_ApiGetCurrentInterfaceNum();
                foundModifierKey = TRUE;
            }
        }else if((reportItem->reportType==hidReportInput) && (reportItem->dataModes == HIDData_Array)&&
                (reportItem->globals.usagePage==USAGE_PAGE_KEY_CODES)){
            usageIndex = reportItem->firstUsageItem;
            hidUsageItem = &pitemListPtrs->usageItemList[usageIndex];

            if((hidUsageItem->usageMinimum == USAGE_MIN_NORMAL_KEY)
                    &&(hidUsageItem->usageMaximum <= USAGE_MAX_NORMAL_KEY)){ //else application cannot suuport
                reportIndex = reportItem->globals.reportIndex;
                Appl_NormalKeysDetails[deviceAddress].reportLength = (pitemListPtrs->reportList[reportIndex].inputBits + 7)/8;
                Appl_NormalKeysDetails[deviceAddress].reportID = (BYTE)reportItem->globals.reportID;
                Appl_NormalKeysDetails[deviceAddress].bitOffset = (BYTE)reportItem->startBit;
                Appl_NormalKeysDetails[deviceAddress].bitLength = (BYTE)reportItem->globals.reportsize;
                Appl_NormalKeysDetails[deviceAddress].count=(BYTE)reportItem->globals.reportCount;
                Appl_NormalKeysDetails[deviceAddress].interfaceNum= USBHostHID_ApiGetCurrentInterfaceNum();
                foundNormalKey = TRUE;
            }
        }else if((reportItem->reportType==hidReportOutput) &&
                (reportItem->globals.usagePage==USAGE_PAGE_LEDS)){
            usageIndex = reportItem->firstUsageItem;
            hidUsageItem = &pitemListPtrs->usageItemList[usageIndex];

            reportIndex = reportItem->globals.reportIndex;
            Appl_LED_Indicator[deviceAddress].reportLength = (pitemListPtrs->reportList[reportIndex].outputBits + 7)/8;
            Appl_LED_Indicator[deviceAddress].reportID = (BYTE)reportItem->globals.reportID;
            Appl_LED_Indicator[deviceAddress].bitOffset = (BYTE)reportItem->startBit;
            Appl_LED_Indicator[deviceAddress].bitLength = (BYTE)reportItem->globals.reportsize;
            Appl_LED_Indicator[deviceAddress].count=(BYTE)reportItem->globals.reportCount;
            Appl_LED_Indicator[deviceAddress].interfaceNum= USBHostHID_ApiGetCurrentInterfaceNum();
            foundLEDIndicator = TRUE;
        }
    }

    if(pDeviceRptinfo->reports == 1){
        Appl_raw_report_buffer[deviceAddress].Report_ID = 0;
        Appl_raw_report_buffer[deviceAddress].ReportSize = (pitemListPtrs->reportList[reportIndex].inputBits + 7)/8;
        Appl_raw_report_buffer[deviceAddress].ReportData = (BYTE*)USB_MALLOC(Appl_raw_report_buffer[deviceAddress].ReportSize);
        Appl_raw_report_buffer[deviceAddress].ReportPollRate = pDeviceRptinfo->reportPollingRate;
        if((foundNormalKey == TRUE)&&(foundModifierKey == TRUE)) status = TRUE;
    }

    return(status);
}
/*** end of usb_host_hid_device.c **********************************************************************/


