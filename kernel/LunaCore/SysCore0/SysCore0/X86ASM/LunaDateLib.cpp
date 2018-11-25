#include "LUA_DATE.h"
char year[] = { '0', '0' };
char month[] = { '0', '0' };
char day[] = { '0', '0' };
char hour[] = { '0', '0' };
char min[] = { '0', '0' };
char sec[] = { '0', '0' };
void LUA_GT_DATE()
{
	// initial
	/*__asm
	{
		mov eax,0
		mov year[0],0
		mov year[1], 0
		mov month[0], 0
		mov month[1], 0
		mov day[0], 0
		mov day[1], 0
		mov hour[0], 0
		mov hour[1], 0
		mov min[1], 0
		mov min[1], 0
		mov min[1], 0
	}*/
	__asm
	{
		mov al,9		//��ȡ��
		out 0x70,al
		in al,0x71
		mov ah,al
		mov cl,4
		shr ah,cl
		and al,00001111b
		add ah,0x30		//ʮλ��
		add al,0x30		//��λ��
		mov year[0],ah
		mov year[1],al
		mov eax,0

		mov al, 8		//��ȡ��
		out 0x70, al
		in al, 0x71
		mov ah, al
		mov cl, 4
		shr ah, cl
		and al, 00001111b
		add ah, 0x30		//ʮλ��
		add al, 0x30		//��λ��
		mov month[0], ah
		mov month[1], al
		mov eax, 0

		mov al, 7		//��ȡ��
		out 0x70, al
		in al, 0x71
		mov ah, al
		mov cl, 4
		shr ah, cl
		and al, 00001111b
		add ah, 0x30		//ʮλ��
		add al, 0x30		//��λ��
		mov day[0], ah
		mov day[1], al
		mov eax, 0

		mov al, 4		//��ȡʱ
		out 0x70, al
		in al, 0x71
		mov ah, al
		mov cl, 4
		shr ah, cl
		and al, 00001111b
		add ah, 0x30		//ʮλ��
		add al, 0x30		//��λ��
		mov hour[0], ah
		mov hour[1], al
		mov eax, 0

		mov al, 2		//��ȡ��
		out 0x70, al
		in al, 0x71
		mov ah, al
		mov cl, 4
		shr ah, cl
		and al, 00001111b
		add ah, 0x30		//ʮλ��
		add al, 0x30		//��λ��
		mov min[0], ah
		mov min[1], al
		mov eax, 0

		mov al, 0		//��ȡ��
		out 0x70, al
		in al, 0x71
		mov ah, al
		mov cl, 4
		shr ah, cl
		and al, 00001111b
		add ah, 0x30		//ʮλ��
		add al, 0x30		//��λ��
		mov sec[0], ah
		mov sec[1], al
		mov eax, 0
	}
}

char* LUNA_DATE_GET(unsigned int LUATYPE)
{
	switch (LUATYPE)
	{
	case LUNA_DATE_YEAR:
		return year;
	case LUNA_DATE_MONTH:
		return month;
	case LUNA_DATE_DAY:
		return day;
	case LUNA_DATE_HOUR:
		return hour;
	case LUNA_DATE_MINUTE:
		return min;
	case LUNA_DATE_SECOND:
		return sec;
	}
	return "";
}