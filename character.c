#include <stdio.h>
#include <string.h>
#include "display.h"
#include "graphic.h"


/*------------------------------------------------------------------------------
	definition
------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
	function prototype
------------------------------------------------------------------------------*/

void CClear(void);
void CClearLine (int cy);
void putch(int a);
void crammove(int num);
void putstr(const unsigned char *s);
void puthex(int a);
void putdec(int a);
void putcrlf(void);


/*------------------------------------------------------------------------------
	global variable
------------------------------------------------------------------------------*/

extern unsigned int CRAM[CRAM_SIZE];       // キャラクターRAM
extern volatile unsigned int Curx, Cury;   // CRAM関連ポインタ(カーソル位置)



/***********************************
*  キャラクターRAMをクリア
***********************************/
void CClear(void)
{
    int i;
    for (i=0; i<CRAM_SIZE; i++) {
        CRAM[i] = 0;    // NULLコードをセット
    }
}

/***********************************
*  1行クリアする
***********************************/
void CClearLine (int cy)
{
    int i;
    for (i=0; i<(H_RES/8); i++) {
        CRAM[cy*(H_RES/8)+i] = 0;   // NULLコードをセット
    }
}

/***********************************
*  文字の表示ロジック
***********************************/
void putch(int a)
{
    unsigned int i, *p;
    const unsigned char *pf;
    /// 文字コードの範囲チェック(文字コードの範囲を限定している場合)
    // ページの折り返しチェック
    if (Curx >= H_RES/8) { // 右端折り返し
        Curx = 0;
        Cury++;
        CClearLine(Cury);
    }
    if (Cury >= V_RES/8) { // 下端折り返し
        //Cury = 0;
        crammove(H_RES/8);
        Cury--;
        CClearLine(Cury);
    }
    if (a == 8) {
        if (Curx > 0) {
            Curx--;
            CRAM[Cury*H_RES/8+Curx] = 0;
        }
        return;
    }
    if (a == 10) {
        Cury++;
        if (Cury >= V_RES/8) { // 下端折り返し
            //Cury = 0;
            crammove(H_RES/8);
            Cury--;
        }
        CClearLine(Cury);
        return;
    }
    if (a == 13){
        Curx=0;
        return;
    }
    CRAM[Cury*H_RES/8+Curx] = a;
    Curx++; // カーソル位置更新
}

void crammove(int num)
{
    unsigned int i;
    for (i=0;i<CRAM_SIZE-num;i++) {
        CRAM[i] = CRAM[i+num];
    }
    return;
}

/******************************
*   文字列描画関数
******************************/
void putstr(const unsigned char *s)
{
    while (*s)
        putch(*s++);
}

void puthex(int a)
{
    char str[7];
    sprintf(str, "%x", a);
    putstr(str);
}

void putdec(int a)
{
    char str[7];
    sprintf(str, "%d", a);
    putstr(str);
}

void putcrlf(void)
{
    putstr("\r\n");
}
