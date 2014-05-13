#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "timer.h"
#include "display.h"
#include "graphic.h"
#include "character.h"
#include "font8.h"

// video state
#define SV_PREEQ    0       // pre sync
#define SV_SYNC     1       // sync
#define SV_POSTEQ   2       // post sync
#define	SV_LINE     3       // video out

#define V_NTSC      262     // horizontal lines/frame 
#define V_SYNC      13       // vertical sync
#define V_BLANK     (V_NTSC - V_RES - V_SYNC)
#define V_PREEQ     V_BLANK / 2         // upper blanking(include presync)
#define V_POSTEQ    V_BLANK - V_PREEQ   // lower blanking(include postsync)
#define H_NTSC      2542    // 63.55usec Tcy 2542
                            // 40,000/15.734=2542.3-1=2541
                            // 40,000/2542=15.73564 (spec 15,734KHz)
                            // 25nsec*2542=63.55usec (spec 63.56usec)
#define H_SYNC      188     // 4.7usec Tcy 188 
                            // 4.7/(1/40M)=188 
#define H_BACK      114     // 4.7usec for dot clock 6.666MHz
                            // 毎フレームの計算遅延を加味して調整

/*------------------------------------------------------------------------------
	function prototype
------------------------------------------------------------------------------*/

void display_init(void);


/*------------------------------------------------------------------------------
	global variable
------------------------------------------------------------------------------*/

unsigned int __attribute__((far)) VRAM[VRAM_SIZE];  // グラフィックVRAM
volatile unsigned int *VPtr, *MPtr; // グラフィックVRAM関連ポインタ
unsigned int CRAM[CRAM_SIZE];       // キャラクターRAM
volatile unsigned int Curx, Cury;   // CRAM関連ポインタ(カーソル位置)

volatile unsigned int  VCount, VState, DotCount, VLine;
static unsigned char VS[4] = {SV_SYNC, SV_POSTEQ, SV_LINE, SV_PREEQ};
static unsigned char VC[4] = {V_SYNC, V_POSTEQ, V_RES, V_PREEQ};

// ハードウェアピン定義
#define SYNC	LATDbits.LATD9  //　sync out
#define VIDEO	LATDbits.LATD3  // video out


/*==============================================================================
    display_init()
===============================================================================*/

void display_init(void)
{

    // sync signal output port
    TRISDbits.TRISD9 = 0;       // NTSC sync
    LATDbits.LATD9 = 1;         // output level High

    // video signal output port
    TRISDbits.TRISD3 = 0;       // video out(SDO3)
    LATDbits.LATD3 = 0;         // output level low

    // set Timer2
    T2CON = 0x0010;             // prescale 1:2 40MHz, timer stop
    TMR2 = 0;
    PR2 = H_NTSC-1;
    IEC0SET = _IEC0_T2IE_MASK;  // enable interrupt
    IFS0CLR = _IFS0_T2IF_MASK;  // flag clear
    IPC2bits.T2IP = 6;          //　priority 6

    // set OC1 interrupt
    IEC0SET = _IEC0_OC1IE_MASK; // enable interrupt
    IFS0CLR = _IFS0_OC1IF_MASK; // flag clear
    IPC1bits.OC1IP = 5;         //　priority 5

    // set OC2 interrupt
    IEC0SET = _IEC0_OC2IE_MASK; // enable interrupt
    IFS0CLR = _IFS0_OC2IF_MASK; // flag clear
    IPC2bits.OC2IP = 5;         //　priority 5

    // set SPI3
    SPI3CON=0x00010834;         // SPI3 disable,32bit,master, not use SDI,
    SPI3BRG=5;                  // 6.666MHz
    //SPI3BRG=4;                  // 8MHz
    IEC0CLR = _IEC0_SPI3TXIE_MASK;  // disable TX interrupt
    IFS0CLR = _IFS0_SPI3TXIF_MASK;  // flag clear
    IPC6bits.SPI3IP = 5;        //　priority 5
    SPI3STATbits.SPIROV=0;      // clear ovf bit
    SPI3CONbits.ON = 1;             // enable SPI3

    // set video variable
    VState = SV_PREEQ;          // initialize state
    VCount = V_PREEQ;           // vertical counter preset
    VLine = 0;                  // VRAMの処理ラインを最初に
    VClear(0);                  // グラフィックVRAMクリア
    VPtr = VRAM;                // グラフィックVRAMポインタ初期値
    CClear();                   // キャラクターRAMクリア
    Curx = Cury = 0;

    // go NTSC
    T2CONbits.TON = 1;
}

/*----------------------------------------------------------------------
	Timer2 interrupt
----------------------------------------------------------------------*/

void __attribute__ (( interrupt(ipl6), vector(_TIMER_2_VECTOR) )) _T2Interrupt(void)
{
    SYNC = 0;				// 水平同期出力(RD9)

    // 垂直同期ステートにより分岐
    switch(VState){
        case SV_PREEQ:          // ブランキング上側の区間
            OC1R = H_SYNC-1;    // 同期パルス幅4.7usec
            OC1CON = 0x8001;    // タイマ2選択ワンショット　L->H
            break;
        case SV_SYNC:           // 垂直同期期間中
            OC1R = H_NTSC-H_SYNC-1; // 切れ込みパルス
            OC1CON = 0x8001;
            break;
        case SV_POSTEQ:         // ブランキング下側の区間
            OC1R = H_SYNC-1;    // 同期パルス幅4.7usec
            OC1CON = 0x8001;    // タイマ2選択ワンショット　L->H
            break;
        case SV_LINE:           // 映像表示区間
            OC1R = H_SYNC-1;    // 同期パルス幅4.7usec
            OC1CON = 0x8001;    // タイマ2選択ワンショット　L->H
            OC2R = H_SYNC + H_BACK; // 映像開始までの遅延
            OC2CON = 0x8001;    // タイマ2選択ワンショット　L->H
            break;
    }

    //// 垂直同期カウンタ更新
    VCount--;                   // 垂直同期カウンタ更新
    if(VCount == 0){            // ステート終了か？
        // 表示フレーム終了か？
        if(VState == SV_POSTEQ){
            VLine = 0;          // VRAM処理ラインを最初に再セット
            VPtr = VRAM;        // フレームの最初に再セット
            // Line = 0;
        }
        VCount = VC[VState];    // ラインカウンタ更新
        VState = VS[VState];    // ステート更新
    }
    IFS0CLR = _IFS0_T2IF_MASK;  // T2割り込みフラグクリア
}


/*----------------------------------------------------------------------
	OC1 interrupt
----------------------------------------------------------------------*/

void __attribute__ (( interrupt(ipl5), vector(_OUTPUT_COMPARE_1_VECTOR) )) _OC1Interrupt(void)
{
    SYNC = 1;                   // 同期パルスリセット
    IFS0CLR = _IFS0_OC1IF_MASK; // OC1割り込みフラグクリア
}


/*----------------------------------------------------------------------
	OC2 interrupt
----------------------------------------------------------------------*/

void __attribute__ (( interrupt(ipl5), vector(_OUTPUT_COMPARE_2_VECTOR) )) _OC2Interrupt(void)
{
    DotCount = 0;
    IEC0SET = _IEC0_SPI3TXIE_MASK;  // SPI送信割り込みを許可
    IFS0CLR = _IFS0_OC2IF_MASK;     // OC2割り込みフラグクリア
}


/*----------------------------------------------------------------------
	SPI3 TX interrupt
----------------------------------------------------------------------*/

void __attribute__ (( interrupt(ipl5), vector(_SPI_3_VECTOR) )) _SPI3TXInterrupt(void)
{
    unsigned long data;
    unsigned int cx, cy;
    const unsigned char *pf;
    if(DotCount < H_RES/32){
        // VRAMから呼び出し
        data = *VPtr++<<16;
        data |= *VPtr++;
        // CRAMから呼び出し
        cx = DotCount*4;
        cy = VLine/8;
        data |= Font8[((CRAM[cy*H_RES/8+cx])<<3)+(VLine&7)]<<24;
        data |= Font8[((CRAM[cy*H_RES/8+cx+1])<<3)+(VLine&7)]<<16;
        data |= Font8[((CRAM[cy*H_RES/8+cx+2])<<3)+(VLine&7)]<<8;
        data |= Font8[((CRAM[cy*H_RES/8+cx+3])<<3)+(VLine&7)];
        // カーソル処理
        data |= (0xff*CursorBlink*(Cury == cy)*(Curx>=cx)*(Curx<=cx+3))<<((3-(Curx&3))*8);
	SPI3BUF = data; // 出力実行
        DotCount++;
    // ドットカウンタ更新
    }else{
        SPI3BUF = 0x00000000;   // SDO3の出力ピンを確実にLowにするために
        SPI3BUF = 0x00000000;   // zero を強制出力する。
        VLine++;
        IEC0CLR = _IEC0_SPI3TXIE_MASK;  // SPI送信割り込みを禁止
    }

    IFS0CLR = _IFS0_SPI3TXIF_MASK;	// 割り込みフラグクリア
}
