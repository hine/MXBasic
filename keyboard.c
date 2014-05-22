#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "usb.h"
#include "usb_host_hid.h"
#include "usb_host_hid_parser.h"
#include "usb_host_hid_device.h"
#include "keyboard.h"


/*------------------------------------------------------------------------------
	definition
------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
	function prototype
------------------------------------------------------------------------------*/

BYTE    toAscii(USB_KEYBOARD_DATA *data);


/*------------------------------------------------------------------------------
	global variable
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
