#include "display.h"
#include "graphic.h"

extern unsigned int __attribute__((far)) VRAM[VRAM_SIZE];  // グラフィックVRAM
extern volatile unsigned int *VPtr, *MPtr; // グラフィックVRAM関連ポインタ

/******************************************
*  全画面固定データセット
*　　 16ビット横のパターンで全体を設定する
******************************************/
void VClear(int patn)
{
    int i;

    MPtr = VRAM;				// VRAMポインタリセット
    for(i=0; i<VRAM_SIZE; i++) {
        *MPtr++ = patn;			// 固定パターン設定

    }
}

/*****************************
* （Ｘ、Ｙ）点描画関数
******************************/
void PSet(unsigned x, unsigned y)
{
    // 座標範囲内であれば点描画
    if((x < H_RES) && (y < V_RES))
    // ワード単位でビット位置計算　そこに１をセットする
    VRAM[y*H_RES/16+x/16] |= (0x8000>>(x&15));

}

/****************************
*  直線描画関数
****************************/
#define	abs(a)	(((a)>0) ? (a) : -(a))
void Line(int x0, int y0, int x1, int y1)
{
    int steep, t;
    int deltax, deltay, error;
    int x, y;
    int ystep;
    // 差分の大きいほうを求める
    steep = (abs(y1 - y0) > abs(x1 - x0));
    // ｘ、ｙの入れ替え
    if(steep){
        t = x0; x0 = y0; y0 = t;
        t = x1; x1 = y1; y1 = t;
    }
    if(x0 > x1) {
        t = x0; x0 = x1; x1 = t;
        t = y0; y0 = y1; y1 = t;
    }
    deltax = x1 - x0; // 傾き計算
    deltay = abs(y1 - y0);
    error = 0;
    y = y0;
    // 傾きでステップの正負を切り替え
    if(y0 < y1) ystep = 1; else ystep = -1;
    // 直線を点で描画
    for(x=x0; x<x1; x++) {
        if(steep) PSet(y,x); else PSet(x,y);
        error += deltay;
        if((error << 1) >= deltax) {
            y += ystep;
            error -= deltax;
        }
    }
}
