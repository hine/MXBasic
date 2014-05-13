/*=====================================================================

	config.h

	 Chip Configuration for PIC32MX695F512H

=====================================================================*/

// SRS Select:
#pragma config FSRSSEL = PRIORITY_0	// SRS Priority 0
// 	this set means , All interrupt priorities are assigned to a shadow register set
//#pragma config FSRSSEL = PRIORITY_1	// SRS Priority 1  
//#pragma config FSRSSEL = PRIORITY_2	// SRS Priority 2  
//#pragma config FSRSSEL = PRIORITY_3	// SRS Priority 3  
//#pragma config FSRSSEL = PRIORITY_4	// SRS Priority 4  
//#pragma config FSRSSEL = PRIORITY_5	// SRS Priority 5  
//#pragma config FSRSSEL = PRIORITY_6	// SRS Priority 6  
//#pragma config FSRSSEL = PRIORITY_7	// SRS Priority 7  

//Ethernet RMII/MII Enable:
#pragma config FMIIEN = OFF	// RMII Enabled  
//#pragma config FMIIEN = ON	// MII Enabled  

// Ethernet I/O Pin Select:
#pragma config FETHIO = OFF	// Alternate Ethernet I/O  
//#pragma config FETHIO = ON	// Default Ethernet I/O  

// USB USID Selection:
//#pragma config FUSBIDIO = OFF	// Controlled by Port Function  
#pragma config FUSBIDIO = ON	// Controlled by the USB Module  

// USB VBUS ON Selection:
//#pragma config FVBUSONIO = OFF	// Controlled by Port Function  
#pragma config FVBUSONIO = ON	// Controlled by USB Module  

// PLL Input Divider:
//#pragma config FPLLIDIV = DIV_1	// 1x Divider  
#pragma config FPLLIDIV = DIV_2	// 2x Divider  
//    using 8MHz XT
//#pragma config FPLLIDIV = DIV_3	// 3x Divider  
//#pragma config FPLLIDIV = DIV_4	// 4x Divider  
//#pragma config FPLLIDIV = DIV_5	// 5x Divider  
//#pragma config FPLLIDIV = DIV_6	// 6x Divider  
//#pragma config FPLLIDIV = DIV_10	// 10x Divider  
//#pragma config FPLLIDIV = DIV_12	// 12x Divider  

// PLL Multiplier:
//#pragma config FPLLMUL = MUL_15	// 15x Multiplier  
//#pragma config FPLLMUL = MUL_16	// 16x Multiplier  
//#pragma config FPLLMUL = MUL_17	// 17x Multiplier  
//#pragma config FPLLMUL = MUL_18	// 18x Multiplier  
//#pragma config FPLLMUL = MUL_19	// 19x Multiplier  
#pragma config FPLLMUL = MUL_20	// 20x Multiplier  
//#pragma config FPLLMUL = MUL_21	// 21x Multiplier  
//#pragma config FPLLMUL = MUL_24	// 24x Multiplier  

// USB PLL Input Divider:
//#pragma config UPLLIDIV = DIV_1	// 1x Divider  
#pragma config UPLLIDIV = DIV_2	// 2x Divider  
//    using 8MHz XT
//#pragma config UPLLIDIV = DIV_3	// 3x Divider
//#pragma config UPLLIDIV = DIV_4	// 4x Divider  
//#pragma config UPLLIDIV = DIV_5	// 5x Divider  
//#pragma config UPLLIDIV = DIV_6	// 6x Divider
//#pragma config UPLLIDIV = DIV_10	// 10x Divider  
//#pragma config UPLLIDIV = DIV_12	// 12x Divider  

// USB PLL Enable:
#pragma config UPLLEN = ON		// Enabled  
//#pragma config UPLLEN = OFF	// Disabled and Bypassed  

// System PLL Output Clock Divider:
#pragma config FPLLODIV = DIV_1	// PLL Divide by 1  
//#pragma config FPLLODIV = DIV_2	// PLL Divide by 2  
//#pragma config FPLLODIV = DIV_4	// PLL Divide by 4  
//#pragma config FPLLODIV = DIV_8	// PLL Divide by 8  
//#pragma config FPLLODIV = DIV_16	// PLL Divide by 16  
//#pragma config FPLLODIV = DIV_32	// PLL Divide by 32  
//#pragma config FPLLODIV = DIV_64	// PLL Divide by 64  
//#pragma config FPLLODIV = DIV_256	// PLL Divide by 256  

// Oscillator Selection Bits:
//#pragma config FNOSC = FRC	// Fast RC Osc (FRC)  
//#pragma config FNOSC = FRCPLL	// Fast RC Osc with PLL  
//#pragma config FNOSC = PRI	// Primary Osc (XT,HS,EC)  
#pragma config FNOSC = PRIPLL	// Primary Osc w/PLL (XT+,HS+,EC+PLL)  
//#pragma config FNOSC = SOSC	// Low Power Secondary Osc (SOSC)  
//#pragma config FNOSC = LPRC	// Low Power RC Osc (LPRC)  
//#pragma config FNOSC = FRCDIV16	// Fast RC Osc w/Div-by-16 (FRC/16)  
//#pragma config FNOSC = FRCDIV	// Fast RC Osc w/Div-by-N (FRCDIV)  

// Secondary Oscillator Enable:
#pragma config FSOSCEN = OFF	// Disabled  
//#pragma config FSOSCEN = ON	// Enabled  

// Internal/External Switch Over:
#pragma config IESO = OFF	// Disabled  
//#pragma config IESO = ON	// Enabled  

// Primary Oscillator Configuration:
//#pragma config POSCMOD = OFF	// Primary osc disabled  
//#pragma config POSCMOD = EC	// External clock mode  
#pragma config POSCMOD = XT	// XT osc mode  
//#pragma config POSCMOD = HS	// HS osc mode  

// CLKO Output Signal Active on the OSCO Pin:
#pragma config OSCIOFNC = OFF	// Disabled  
//#pragma config OSCIOFNC = ON	// Enabled  

// Peripheral Clock Divisor:
#pragma config FPBDIV = DIV_1	// Pb_Clk is Sys_Clk/1  
//#pragma config FPBDIV = DIV_2	// Pb_Clk is Sys_Clk/2  
//#pragma config FPBDIV = DIV_4	// Pb_Clk is Sys_Clk/4  
//#pragma config FPBDIV = DIV_8	// Pb_Clk is Sys_Clk/8  

// Clock Switching and Monitor Selection:
#pragma config FCKSM = CSDCMD	// Clock Switch Disable, FSCM Disabled  
//#pragma config FCKSM = CSECME	// Clock Switch Enable, FSCM Enabled  
//#pragma config FCKSM = CSECMD	// Clock Switch Enable, FSCM Disabled  

// Watchdog Timer Postscaler:
#pragma config WDTPS = PS1	// 1:1  
//#pragma config WDTPS = PS2	// 1:2  
//#pragma config WDTPS = PS4	// 1:4  
//#pragma config WDTPS = PS8	// 1:8  
//#pragma config WDTPS = PS16	// 1:16  
//#pragma config WDTPS = PS32	// 1:32  
//#pragma config WDTPS = PS64	// 1:64  
//#pragma config WDTPS = PS128	// 1:128  
//#pragma config WDTPS = PS256	// 1:256  
//#pragma config WDTPS = PS512	// 1:512  
//#pragma config WDTPS = PS1024	// 1:1024  
//#pragma config WDTPS = PS2048	// 1:2048  
//#pragma config WDTPS = PS4096	// 1:4096  
//#pragma config WDTPS = PS8192	// 1:8192  
//#pragma config WDTPS = PS16384	// 1:16384  
//#pragma config WDTPS = PS32768	// 1:32768  
//#pragma config WDTPS = PS65536	// 1:65536  
//#pragma config WDTPS = PS131072	// 1:131072  
//#pragma config WDTPS = PS262144	// 1:262144  
//#pragma config WDTPS = PS524288	// 1:524288  
//#pragma config WDTPS = PS1048576	// 1:1048576  

// Watchdog Timer Enable:
#pragma config FWDTEN = OFF	// WDT Disabled (SWDTEN Bit Controls)  
//#pragma config FWDTEN = ON	// WDT Enabled  

// Background Debugger Enable:
#pragma config DEBUG = OFF	// Debugger is Disabled  
//#pragma config DEBUG = ON	// Debugger is Enabled  

//ICE/ICD Comm Channel Select:
#pragma config ICESEL = ICS_PGx1	// ICE EMUC1/EMUD1 pins shared with PGC1/PGD1  
//#pragma config ICESEL = ICS_PGx2	// ICE EMUC2/EMUD2 pins shared with PGC2/PGD2  

// Program Flash Write Protect:
#pragma config PWP = OFF	// Disable  
//#pragma config PWP = PWP512K	// First 512K  
//#pragma config PWP = PWP508K	// First 508K  
//#pragma config PWP = PWP504K	// First 504K  
//#pragma config PWP = PWP500K	// First 500K  
//#pragma config PWP = PWP496K	// First 496K  
//#pragma config PWP = PWP492K	// First 492K  
//#pragma config PWP = PWP488K	// First 488K  
//#pragma config PWP = PWP484K	// First 484K  
//#pragma config PWP = PWP480K	// First 480K  
//#pragma config PWP = PWP476K	// First 476K  
//	...
//#pragma config PWP = PWP44K	// First 44K  
//#pragma config PWP = PWP40K	// First 40K  
//#pragma config PWP = PWP36K	// First 36K  
//#pragma config PWP = PWP32K	// First 32K  
//#pragma config PWP = PWP28K	// First 28K  
//#pragma config PWP = PWP24K	// First 24K  
//#pragma config PWP = PWP20K	// First 20K  
//#pragma config PWP = PWP16K	// First 16K  
//#pragma config PWP = PWP12K	// First 12K  
//#pragma config PWP = PWP8K	// First 8K  
//#pragma config PWP = PWP4K	// First 4K  

// Boot Flash Write Protect bit:
//#pragma config BWP = ON	// Protection Enabled  
#pragma config BWP = OFF	// Protection Disabled  

// Code Protect:
//#pragma config CP = ON	// Protection Enabled  
#pragma config CP = OFF	// Protection Disabled  


// end of p32mx695f_config.h
