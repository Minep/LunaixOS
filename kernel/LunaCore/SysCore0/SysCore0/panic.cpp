#include <lhal.h>
#include <stdarg.h>
#include "CVDC/CELESTIA_DIP.h"
#include "CVDC/CELESTIA_COLOR.h"
#include "X86ASM\LUA_DATE.h"

void _cdecl Nightmare_Moon_Exception(const char* nm_fmt, ...)
{
	LUNA_DISABLE();
	char* LUNAIX_WARNING = "****THE NIGHTMARE MOON COMES DOWN FROM THE MOON!\n\n";
	char* LUNAIX_WARNING_BODY = "[LUNA'S INFO] Lunaix OS has encountered a problem that cause an exception.\n\
    And it has released Nightmare Moon from the moon! \n\
    Celestia are going to vanquish her by using THE ELEMENTS OF HARMONY!\n\
    The computer may be reboot. Any unsave work will lost.\n\n\
    We are sorry about this.\n\
    Luna ensure that she will perfect the kernel and Celestia will help to do \nthis.\n\n";
	char* LUNAIX_WARNING_END = "[LUNAIX ERROR] System has been halted at $z:$z:$z cause of $z";
	CELE_CLR(C_BLACK_RED | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_SetColor(0xc);
	CELE_GtXY(0, 0);
	CELE_pstr(LUNAIX_WARNING);
	CELE_SetColor(C_BLACK_GREEN | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_pstr(LUNAIX_WARNING_BODY);
	LUA_GT_DATE();
	CELE_SetColor(C_BLACK_RED | C_OPT_HIGHLIGHT_BACKGROUND);
	CELE_printf(LUNAIX_WARNING_END, LUNA_DATE_GET(LUNA_DATE_HOUR), LUNA_DATE_GET(LUNA_DATE_MINUTE), LUNA_DATE_GET(LUNA_DATE_SECOND), nm_fmt);
	for (;;);
}