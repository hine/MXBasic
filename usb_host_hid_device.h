/**************************************************

    File: usb_host_hid_device.h

	 2013/11/17 S.Suwa http://www.suwa-koubou.jp

**************************************************/

#ifndef	_USB_HOST_HID_DEVICE_H
#define	_USB_HOST_HID_DEVICE_H

#include "GenericTypeDefs.h"

typedef struct {
	struct {
	BYTE	left:  1;
	BYTE	right: 1;
	BYTE	wheel: 1;
	BYTE    unuse: 5;
	} button;
	short	x_axis;	// Some mouse reports 12bits value of axis.
	short	y_axis;
	short	wheel;
} USB_MOUSE_DATA;


typedef struct {
	struct {
	BYTE    left_ctrl:   1;
	BYTE    left_shift:  1;
	BYTE    left_alt:    1;
	BYTE    numlock:     1;
	BYTE    right_ctrl:  1;
	BYTE    right_shift: 1;
	BYTE    right_alt:   1;
	BYTE    capslock:    1;
 	} modifier;
	BYTE    keycode[3];		// Three keys pressed same time. 
} USB_KEYBOARD_DATA;


typedef struct {
	struct {
	BYTE   btn1:    1;
	BYTE   btn2:    1;
	BYTE   btn3:    1;
	BYTE   btn4:    1;
	BYTE   btn5:    1;
	BYTE   btn6:    1;
	BYTE   btn7:    1;
	BYTE   btn8:    1;
	BYTE   btn9:    1;
	BYTE   btn10:   1;
	BYTE   btn11:   1;
	BYTE   btn12:   1;
	BYTE   unuse:   4;
	} button;
	short x_axis;
	short y_axis;
    short z_axis;
	short rz_axis;
	short hatswitch;   // position 1 to 8, 0 to 7  
} USB_JOYSTICK_DATA;

// HID Device Type
#define HID_UNKNOWN                     0  // unknown device
#define HID_MOUSE                       1
#define HID_JOYSTICK                    2
#define HID_GAMEPAD                     3  // not feature
#define HID_KEYBOARD                    4
#define HID_KEYPAD                      5  // not feature

#define HID_MAX_DEVICETYPE              (HID_KEYPAD+1)

// usb_host_hid_device.c
extern int getHIDnumOfDevice(BYTE devicetype);
extern int mouse_read(int num, USB_MOUSE_DATA *data);
extern int keyboard_read(int num, USB_KEYBOARD_DATA *data);
extern int joystick_read(int num, USB_JOYSTICK_DATA *data);


#endif // _USB_HOST_HID_DEVICE_H

/*** end of usb_host_hid_device.h **************************/
