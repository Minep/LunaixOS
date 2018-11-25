#include "os.h"
#include "../../Include/lhal.h"
#include "../CVDC/CELESTIA_DIP.h"
#include "../CVDC/CELESTIA_COLOR.h"
#include "../../Include/string.h"
#include "../X86ASM/LUA_DATE.h"
#include "../LX_MMNGR.h"



void sleep(int ms) {

	static int ticks = ms + LUNA_DBG_TICKCOUNT();
	while (ticks > LUNA_DBG_TICKCOUNT());
}

RAINBOWDASH_KEYCODE getch() {

	RAINBOWDASH_KEYCODE key = KEY_UNKNOWN;

	//! wait for a keypress
	while (key == KEY_UNKNOWN)
		key = RD_keyb_getLastKey();

	//! discard last keypress (we handled it) and return
	RD_keyb_DiscardLastKey();
	return key;
}


void gcmd(char* buf, int n)
{
	int y, x;
	RAINBOWDASH_KEYCODE key = KEY_UNKNOWN;
	bool	BufChar;
	CELE_printf("LUNAIX >");
	CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_getCurPos(&x, &y);
	CELE_GtXY(x + 1, y);
	//! get command string
	int i = 0;
	while (i < n) {
		CELE_getCurPos(&x, &y);
		//! grab next char
		key = getch();

		//! end of command if enter is pressed
		if (key == KEY_RETURN)
			break;

		//! backspace
		if (key == KEY_BACKSPACE) {

			//! dont buffer this char
			BufChar = false;

			if (i > 0) {

				//! go back one char
				CELE_getCurPos(&x, &y);
				if (x > 0)
				{
					CELE_GtXY(--x, y);
				}
				else {
					//! x is already 0, so go back one line
					y--;
					x = 80;
				}
				CELE_printf("  ");
				CELE_GtXY(x, y);
				i -= 1;
			}
			BufChar = true;
		}
		if (key == KEY_CAPSLOCK)
		{
			RD_keyb_setLED(RD_keyb_getNumLock(), RD_keyb_getCapsLock()?false:true, RD_keyb_getScrollLock());
		}
		
		//! only add the char if it is to be buffered
		if (BufChar) {

			//! convert key to an ascii char and put it in buffer
			char c = RD_keyb_ToASCII(key);
			if (c >=0x20 && c<=0x7e && key!=KEY_CAPSLOCK) { //insure its an ascii char
				CELE_pchar(c);
				CELE_updateCur(x > 79 ? x = 0 : ++x, (x > 79 && y < 25) ? ++y : y);
				buf[i++] = c;
			}
		}

		//! wait for next key. You may need to adjust this to suite your needs
		sleep(10);
	}
	CELE_getCurPos(&x, &y);
	CELE_GtXY(0, ++y);
	//! null terminate the string
	buf[i] = '\0';
	CELE_SetColor(C_BULE_GREEN | C_OPT_HIGHLIGHT_FOREGROUND);
}

int Procees(char* buf)
{
	if (strcmp(buf, "lx -ver")==0)
	{
		CELE_printf(" Lunaix Operating System\n");
		CELE_printf(" Developed and Maintaining by Lunaixsky  (2016)\n\n");
		CELE_printf(" Kernel Detail: -------\n");
		CELE_printf("    Kernel name   : Lunaix Core\n");
		CELE_printf("    Release Time  : still in develop\n");
		CELE_printf("    Kernel version: Build 20161229\n");
		CELE_printf(" VGA Support Core Detail: -------\n");
		CELE_printf("    Core name     : Celestia VGA Display Core  (CVDC)\n");
		CELE_printf("    Release Time  : still in develop\n");
		CELE_printf("    Resolution    : 80*25");
		CELE_printf("    Core version: Build 20161229\n");
	}
	else if (strcmp(buf, "lx") == 0)
	{
		CELE_printf(" ------------LUNAIX COMMANDLINE-----------\n");
		CELE_printf(" >The usage of command 'lx':\n");
		CELE_printf("    -ver  : the current version of Lunaix OS\n");
		CELE_printf("    -time : Get current computer date\n");
		CELE_printf("    -ram  : Installed memory size\n");
	}
	else if (strcmp(buf, "help") == 0 || strcmp(buf, "h") == 0)
	{
		CELE_printf(" ------------LUNAIX COMMANDLINE-----------\n");
		CELE_printf("    lx     : The detail of Lunaix OS\n");
		CELE_printf("    cls    : Clear the screen\n");
		CELE_printf("    shutd  : Shutdown Lunaix OS\n");
		CELE_printf("    dir    : Files in current directory\n");
	}
	else if (strcmp(buf, "cls") == 0)
	{
		CELE_CLR(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
		CELE_SetColor(C_WHITE_BLACK);
		CELE_GtXY(0, 0);
		CELE_printf("* LUNAIX Operating System - The Beauty of the night, Luna.                        ");
		CELE_GtXY(0, 1);
		CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	}
	else if (strcmp(buf, "lx -time") == 0)
	{
		LUA_GT_DATE();
		CELE_printf("  Current date :20$z-$z-$z $z:$z:$z\n",
			LUNA_DATE_GET(LUNA_DATE_YEAR),
			LUNA_DATE_GET(LUNA_DATE_MONTH),
			LUNA_DATE_GET(LUNA_DATE_DAY),
			LUNA_DATE_GET(LUNA_DATE_HOUR),
			LUNA_DATE_GET(LUNA_DATE_MINUTE),
			LUNA_DATE_GET(LUNA_DATE_SECOND));
	}
	else if (strcmp(buf, "shutd") == 0)
	{
		return 1;
	}
	else if (strcmp(buf, "dir") == 0)
	{
		CELE_printf("   +-LUNAIX \n");
		CELE_printf("    +---STG0.LUAIX\n");
		CELE_printf("    +---lhal.lxlib\n");
		CELE_printf("    +---RDkbrd.lxlib\n");
		CELE_printf("    +---celeDip.lxm\n");
		CELE_printf("    +---syscore0.luasys\n");
	}
	else if (strcmp(buf, "lx -ram") == 0)
	{
		uint32_t* p = (uint32_t*)0x3000;
		int a = 0- *p;
		CELE_printf("  Total RAM: $i MB\n", a / 1024 / 1024);
	}
	else
	{
		CELE_printf("   Invalid command!\n");
	}
	return 0;
}