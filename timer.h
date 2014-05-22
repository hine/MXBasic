/***********************************************************************
	timer module
***********************************************************************/

#ifndef _TIMER_H
#define	_TIMER_H

#include "GenericTypeDefs.h"

#define	lock_timer()	IEC0CLR=_IEC0_T1IE_MASK
#define unlock_timer()	IEC0SET=_IEC0_T1IE_MASK
#define	clear_timer()	IFS0CLR=_IFS0_T1IF_MASK

// in timer.c
void	timer_init(void);
void    delay_ms(int t);

extern	volatile DWORD AplTimer;      // in timer.c
extern	volatile DWORD RefreshTime;   // in timer.c
//extern  void     disk_timerproc (void);	  // in diskio.c
//extern  void     key_scan(void);		  // in key.c
extern	volatile int CursorBlink;	  // in rtc.c
extern	volatile int KeyPolling;  // control USB keybord read interval 
//extern	volatile unsigned short ClockCount; // 1sec interval countdown timer
//extern	volatile int tempo_strobe;	// 100Hz music tempo

#endif
