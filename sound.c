#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "sound.h"

unsigned short sounddata[]={27363,25828,24378,23010,21718,20499,19349,18263,17238,16270,15357,14495,
    13681,12914,12189,11505,10859,10249,9674,9131,8619,8135,7678,7247,6840};
unsigned int soundcount;
volatile int soundon;

void sound_init()
{
    //T3CON = 0x0030; // prescale 1:8
    T3CON = 0x8050;	// prescale 1:32
    TMR3 = 0;
    PR3 = 0;
    IEC0CLR = _IEC0_T3IE_MASK; // disable interrupt
    IFS0CLR = _IFS0_T3IF_MASK; // flag clear
    IPC3bits.T3IP = 2;         // priority 2
    TRISBbits.TRISB9 = 0;      // RB9 as sound out

    soundcount = 0;
    soundon = 0;
}

void sound_start(short data, int length)
{
    PR3 = data;
    soundcount = length; //msec
    soundon = 1;
    putstr("sound on(");putdec(data);putstr(")\r\n");
    IFS0CLR = _IFS0_T3IF_MASK;
    IEC0SET = _IEC0_T3IE_MASK; // enable interrupt
}

void sound_stop()
{
    soundon = 0;
    putstr("sound off\r\n");
    IFS0CLR = _IFS0_T3IF_MASK;
    IEC0CLR = _IEC0_T3IE_MASK; // disable interrupt
    LATBCLR=0x0200;  // RB9 to low
}