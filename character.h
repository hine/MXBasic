/* 
 * File:   character.h
 * Author: hine
 *
 * Created on 2014/04/29, 11:52
 */

#ifndef _CHARACTER_H
#define	_CHARACTER_H
extern void CClear(void);
extern void CClearLine (int cy);
extern void putch(int a);
extern void putstr(const unsigned char *s);
extern void puthex(int a);
extern void putdec(int a);
extern void putcrlf(void);

#endif	/* _CHARACTER_H */

