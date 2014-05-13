/*=====================================================================

	config.h

	 Chip Configuration for PIC32MX220F032B

=====================================================================*/

// Peripheral Module Disable Configuration:
#pragma config PMDL1WAY = OFF	// Allow multiple reconfigurations  
//#pragma config PMDL1WAY = ON	// Allow only one reconfiguration  

// Peripheral Pin Select Configuration:
#pragma config IOL1WAY = OFF	// Allow multiple reconfigurations  
//#pragma config IOL1WAY = ON	// Allow only one reconfiguration  

// USB USID Selection:
//#pragma config FUSBIDIO = OFF	// Controlled by Port Function  
#pragma config FUSBIDIO = ON	// Controlled by the USB Module  

// USB VBUS ON Selection:
//#pragma config FVBUSONIO = OFF	// Controlled by Port Function  
#pragma config FVBUSONIO = ON	// Controlled by USB Module  

// PLL Input Divider:
//#pragma config FPLLIDIV = DIV_1	// 1x Divider  
#pragma config FPLLIDIV = DIV_2	// 2x Divider  
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
//#pragma config UPLLIDIV = DIV_3	// 3x Divider
//#pragma config UPLLIDIV = DIV_4	// 4x Divider  
//#pragma config UPLLIDIV = DIV_5	// 5x Divider  
//#pragma config UPLLIDIV = DIV_6	// 6x Divider
//#pragma config UPLLIDIV = DIV_10	// 10x Divider  
//#pragma config UPLLIDIV = DIV_12	// 12x Divider  

// USB PLL Enable:
#pragma config UPLLEN = ON	// Enabled  
//#pragma config UPLLEN = OFF	// Disabled and Bypassed  

// System PLL Output Clock Divider:
//#pragma config FPLLODIV = DIV_1	// PLL Divide by 1  
#pragma config FPLLODIV = DIV_2	// PLL Divide by 2  
//#pragma config FPLLODIV = DIV_4	// PLL Divide by 4  
//#pragma config FPLLODIV = DIV_8	// PLL Divide by 8  
//#pragma config FPLLODIV = DIV_16	// PLL Divide by 16  
//#pragma config FPLLODIV = DIV_32	// PLL Divide by 32  
//#pragma config FPLLODIV = DIV_64	// PLL Divide by 64  
//#pragma config FPLLODIV = DIV_256	// PLL Divide by 256  

// Oscillator Selection Bits:
//#pragma config FNOSC = FRC	// Fast RC Osc (FRC)  
#pragma config FNOSC = FRCPLL	// Fast RC Osc with PLL  
//#pragma config FNOSC = PRI	// Primary Osc (XT,HS,EC)  
//#pragma config FNOSC = PRIPLL	// Primary Osc w/PLL (XT+,HS+,EC+PLL)  
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
#pragma config POSCMOD = OFF	// Primary osc disabled  
//#pragma config POSCMOD = EC	// External clock mode  
//#pragma config POSCMOD = XT	// XT osc mode  
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

// Watchdog Timer Window Enable:
#pragma config WINDIS = OFF	// Watchdog Timer is in Non-Window Mode  
//#pragma config WINDIS = ON	// Watchdog Timer is in Window Mode  

// Watchdog Timer Enable:
#pragma config FWDTEN = OFF	// WDT Disabled (SWDTEN Bit Controls)  
//#pragma config FWDTEN = ON	// WDT Enabled  

// Watchdog Timer Window Size:
#pragma config FWDTWINSZ = WINSZ_75	// Window Size is 75%  
//#pragma config FWDTWINSZ = WINSZ_50	// Window Size is 50%  
//#pragma config FWDTWINSZ = WINSZ_37	// Window Size is 37.5%  
//#pragma config FWDTWINSZ = WISZ_25	// Window Size is 25%  

// Background Debugger Enable:
#pragma config DEBUG = OFF	// Debugger is Disabled  
//#pragma config DEBUG = ON	// Debugger is Enabled  

// JTAG Enable:
#pragma config JTAGEN = OFF	// JTAG Disabled
//#pragma config JTAGEN = ON	// JTAG Port Enabled  

// ICE/ICD Comm Channel Select:
#pragma config ICESEL = RESERVED	// Reserved  
//#pragma config ICESEL = ICS_PGx3	// Communicate on PGEC3/PGED3  
//#pragma config ICESEL = ICS_PGx2	// Communicate on PGEC2/PGED2  
//#pragma config ICESEL = ICS_PGx1	// Communicate on PGEC1/PGED1  

// Program Flash Write Protect:
#pragma config PWP = OFF	// Disable  
//#pragma config PWP = PWP32K	// First 32K  
//#pragma config PWP = PWP31K	// First 31K  
//#pragma config PWP = PWP30K	// First 30K  
//#pragma config PWP = PWP29K	// First 29K  
//#pragma config PWP = PWP28K	// First 28K  
//#pragma config PWP = PWP27K	// First 27K  
//#pragma config PWP = PWP26K	// First 26K  
//#pragma config PWP = PWP25K	// First 25K  
//#pragma config PWP = PWP24K	// First 24K  
//#pragma config PWP = PWP23K	// First 23K  
//#pragma config PWP = PWP22K	// First 22K  
//#pragma config PWP = PWP21K	// First 21K  
//#pragma config PWP = PWP20K	// First 20K  
//#pragma config PWP = PWP19K	// First 19K  
//#pragma config PWP = PWP18K	// First 18K  
//#pragma config PWP = PWP17K	// First 17K  
//#pragma config PWP = PWP16K	// First 16K  
//#pragma config PWP = PWP15K	// First 15K  
//#pragma config PWP = PWP14K	// First 14K  
//#pragma config PWP = PWP13K	// First 13K  
//#pragma config PWP = PWP12K	// First 12K  
//#pragma config PWP = PWP11K	// First 11K  
//#pragma config PWP = PWP10K	// First 10K  
//#pragma config PWP = PWP9K	// First 9K  
//#pragma config PWP = PWP8K	// First 8K  
//#pragma config PWP = PWP7K	// First 7K  
//#pragma config PWP = PWP6K	// First 6K  
//#pragma config PWP = PWP5K	// First 5K  
//#pragma config PWP = PWP4K	// First 4K  
//#pragma config PWP = PWP3K	// First 3K  
//#pragma config PWP = PWP2K	// First 2K  
//#pragma config PWP = PWP1K	// First 1K  

// Boot Flash Write Protect bit:
//#pragma config BWP = ON	// Protection Enabled  
#pragma config BWP = OFF	// Protection Disabled  

// Code Protect:
//#pragma config CP = ON	// Protection Enabled  
#pragma config CP = OFF	// Protection Disabled  


// end of p32mx220f_config.h
