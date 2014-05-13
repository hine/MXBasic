/***********************************
*  NTSC Library Header File
***********************************/

#ifndef	_VIDEO_H
#define	_VIDEO_H

/// 画像解像度定数指定
#define V_RES       216 // 27line*8dot vertical resolution
#define H_RES       320 // 40char*8dot horizontal resolution
#define VRAM_SIZE   V_RES*H_RES/16
#define CRAM_SIZE   (V_RES/8) * (H_RES/8)

extern void display_init(void);

#endif
