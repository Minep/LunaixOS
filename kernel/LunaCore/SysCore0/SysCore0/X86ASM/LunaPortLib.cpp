#include "LUA_PORTLib.h"
/*
int PORT_IN(int PORT)
{
	int res;
	_asm
	{
		mov ebx,PORT
		in al,ebx
		mov res,al
	}
	return res;
}
void PORT_OUT(int PORT, int _DAT)
{
	_asm
	{
		mov ebx,_DAT
		mov eax,PORT
		out eax,ebx
	}
}
*/