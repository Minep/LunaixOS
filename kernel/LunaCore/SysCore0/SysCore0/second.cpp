#include <lhal.h>
#include "CVDC\CELESTIA_DIP.h"
#include "CVDC\CELESTIA_COLOR.h"
#include "LunaOS\os.h"
#include <string.h>


int _cdecl smain()
{
	CELE_CLR(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_SetColor(C_WHITE_BLACK);
	CELE_GtXY(0, 0);
	CELE_printf("* LUNAIX Operating System - The Beauty of the night, Luna.                        ");
	CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_GtXY(0, 1);
	CELE_printf(" LUNAIX OS      V1.0        \n");
	CELE_printf("     Copyright (c) 2016 Lunaixsky\n");
	CELE_printf("     For my favourite charactor in My Little Pony , Luna.\n");
	CELE_printf("     Computer CPU: $z", LUNA_CPU_VENDER());
	CELE_printf("\n\n\n");
	CELE_SetColor(C_BULE_GREEN | C_OPT_HIGHLIGHT_FOREGROUND);
	//CELE_printf("LUNAIX >");
	//CELE_printf("Sin(30)=$f", TS_SIN(TS_TORAD(30.00)));
	//LUNA_mksound(233);
	while (1)
	{
		char c[100];
		gcmd(c, 98);
		if (Procees(c) == 1)
		{
			break;
		}
	}
	CELE_CLR_DELAY(C_BLACK_GREEN,300);
	CELE_GtXY(0, 0);
	CELE_printf("You can power off your computer safely;");
	return 0;
}