#ifndef _LUNAIX_OS_H_INC
#define _LUNAIX_OS_H_INC
#include "../../LUNAIX_kbDriver/LUNAIX_KeyBoard.h"

extern void sleep(int ms);
extern RAINBOWDASH_KEYCODE getch();
extern void gcmd(char* buf, int n);
extern int Procees(char* buf);
#endif