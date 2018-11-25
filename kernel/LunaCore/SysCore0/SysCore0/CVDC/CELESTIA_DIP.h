/****************Celestia Display Header***************
**	    >Lunaix Operating System Display Function<
**			   >For Lunaix Kernel<
**				 >CPR Lunaixsky<
*/

#ifndef CELESTIA_DIP_H
#define CELESTIA_DIP_H
#include "../../Include/stdint.h"

#define VID_MEMORY	0xB8000
extern void CELE_pchar(unsigned char c);
extern unsigned CELE_SetColor(const unsigned c);
extern void CELE_GtXY(unsigned x, unsigned y);
extern void CELE_CLR(const unsigned c);
extern void CELE_pstr(char* str);
extern int CELE_printf(const char* str, ...);
extern int CELE_GtY();
extern void CELE_CLR_SPC(const unsigned c, int row);
extern void CELE_updateCur(int x, int y);
extern void CELE_CLR_DELAY(const unsigned c, int delay);
extern void CELE_getCurPos(int* x, int* y);
//extern uint16_t* GetVideoArea();

//Graphics
//extern void DrawRect(int x, int y, int w, int h, unsigned c);
#endif