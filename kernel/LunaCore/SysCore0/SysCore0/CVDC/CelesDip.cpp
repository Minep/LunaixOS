/************** Celestia Display Core *****************
**	    >Lunaix Operating System Display Core<
**			   >For LunaixOS Kernel<
**				 >CPR Lunaixsky<
*******************************************************/
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include "../../Include/lhal.h"
#include "CELESTIA_DIP.h"
#include "CELESTIA_COLOR.h"
#include "../TwilightALG/TWI_STR.h"
#include "../LunaOS/os.h"
uint16_t *video = (uint16_t*)VID_MEMORY;
//void C_scroll();
// these vectors together act as a corner of a bounding rect
// This allows GotoXY() to reposition all the text that follows it
static unsigned int _xPos = 0, _yPos = 0;
static unsigned _startX = 0, _startY = 0;
// current color
static unsigned _color = 0;

#ifdef _MSC_VER
#pragma warning (disable:4244)
#endif

void CELE_getCurPos(int* x, int* y)
{
	*x = _xPos;
	*y = _yPos;
}

void CELE_updateCur(int x, int y)
{
	uint16_t curL = y * 80 + x;
	//This code still has compatible problem , I will fix it later.
#if 0
	LUNA_DISABLE();
	LUNA_PortOUT(0x3D4, 14);
	LUNA_PortOUT(0x3D5, curL >> 8);
	LUNA_PortOUT(0x3D4, 15);
	LUNA_PortOUT(0x3D5, curL);
	LUNA_ENABLE();
#endif
}

void CELE_pchar(unsigned char c) {

	if (c == 0)
		return;

	if (c == '\n' || c == '\r') {	/* start new line */
		_yPos ++;
		_xPos = 0;
		return;
	}

	if (_xPos > 79) {			/* start new line */
		_yPos ++;
		_xPos = 0;
		return;
	}
	if (_yPos >= 24)
	{
		
		CELE_CLR(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
		CELE_SetColor(C_WHITE_BLACK);
		CELE_GtXY(0, 0);
		CELE_printf("* LUNAIX Operating System - The Beauty of the night, Luna.                        ");
		CELE_GtXY(0, 1);
		CELE_SetColor(C_BULE_GREEN | C_OPT_HIGHLIGHT_FOREGROUND);
		//C_scroll();
		//CELE_GtXY(_xPos, 24);
	}
	unsigned short char_attr = _color << 8;
	video[_xPos + _yPos * 80] = char_attr | c;
	_xPos++;
	/* draw the character */
	/*unsigned char* p = (unsigned char*)VID_MEMORY + (_xPos++) * 2 + _yPos * 80;
	*p++ = c;
	*p = _color;*/
}


char tbuf[32];
char bchars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

void itoa(unsigned i, unsigned base, char* buf) {
	int pos = 0;
	int opos = 0;
	int top = 0;

	if (i == 0 || base > 16) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	while (i != 0) {
		tbuf[pos] = bchars[i % base];
		pos++;
		i /= base;
	}
	top = pos--;
	for (opos = 0; opos<top; pos--, opos++) {
		buf[opos] = tbuf[pos];
	}
	buf[opos] = 0;
}

void itoa_s(int i, unsigned base, char* buf) {
	if (base > 16) return;
	if (i < 0) {
		*buf++ = '-';
		i *= -1;
	}
	itoa(i, base, buf);
}

//============================================================================
//    CELESTIA DIP INTERFACE FUNCTIONS
//============================================================================

unsigned CELE_SetColor(const unsigned c) {

	unsigned t = _color;
	_color = c;
	return t;
}

void CELE_GtXY(unsigned x, unsigned y) {

	// reposition starting vectors for next text to follow
	// multiply by 2 do to the video modes 2byte per character layout
	_xPos = x;
	_yPos = y;
	CELE_updateCur(x, y);
}

int CELE_GtY()
{
	return _yPos / 2;
}

void CELE_CLR(const unsigned c) {
	for (int i = 0; i<80*25; i++) {
		video[i] = (c << 8) | 0x20;
	}
	_color = c;
}

void CELE_CLR_DELAY(const unsigned c, int delay)
{
	for (int i = 0; i<80 * 25; i++) {
		video[i] = (c << 8) | 0x20;
		sleep(delay);
	}
	_color = c;
}

void CELE_CLR_SPC(const unsigned c,int row) {
	for (int i = row * 80; i < 80 * (25 - row); i++) {
		video[i] = (c << 8) | 0x20;
	}
	_color = c;
}

void CELE_pstr(char* str) {

	if (!str)
		return;

	for (size_t i = 0; i<strlen(str); i++)
		CELE_pchar(str[i]);
}
int CELE_printf(const char* str, ...) {

	if (!str)
		return 0;

	va_list		args;
	va_start(args, str);

	for (size_t i = 0; i<strlen(str); i++) {

		switch (str[i]) {

		case '$':

			switch (str[i + 1]) {

				/*** characters ***/
			case 'c': {
				char c = va_arg(args, char);
				CELE_pchar(c);
				i++;		// go to next character
				break;
			}

			case 'z':{
				char* c = va_arg(args, char*);
				CELE_pstr(c);
				i++;
				break;
			}

				/*** address of ***/
			case 's': {
				int c = (int&)va_arg(args, char);
				char str[32];
				memset(str, 0, 32);
				itoa_s(c, 16, str);
				CELE_pstr(str);
				i++;		// go to next character
				break;
			}

				/*** integers ***/
			case 'i': {
				int c = va_arg(args, int);
				char str[32];
				memset(str, 0, 32);
				itoa_s(c, 10, str);
				CELE_pstr(str);
				i++;		// go to next character
				break;
			}

				/*** display in hex ***/
			case 'x': {
				int c = va_arg(args, int);
				char str[32];
				memset(str, 0, 32);
				itoa_s(c, 16, str);
				CELE_pstr(str);
				i++;		// go to next character
				break;
			}

			case 'b':
			{
				int c = va_arg(args, int);
				char str[32];
				memset(str, 0, 32);
				itoa_s(c, 2, str);
				CELE_pstr(str);
				i++;		// go to next character
				break;
			}
			case 'o':
			{
				int c = va_arg(args, int);
				char str[32];
				memset(str, 0, 32);
				itoa_s(c, 8, str);
				CELE_pstr(str);
				i++;		// go to next character
				break;
			}
			case 'f':
			{
				float f = va_arg(args, float);
				char str[32];
				memset(str, 0, 32);
				ts_ftoa(str, f, 3);
				CELE_pstr(str);
				i++;
				break;
			}
			default:
				va_end(args);
				return 1;
			}
			break;

		default:
			CELE_pchar(str[i]);
			break;
		}

	}

	va_end(args);
}


void C_scroll()
{
	//Y control
	for (int y = 1; y < 24; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			video[x + (y - 1) * 80] = video[x + y * 80];
		}
	}
	for (int x0 = 0; x0 < 80; x0++)
	{
		video[x0 + 25 * 80] = (_color << 8) | 0x20;
	}
}
/*
void DrawRect(int x, int y, int w, int h, unsigned c)
{
	for (int h0 = 0; h0 >= h; h0++)
	{
		for (int w0 = 0; w0 >= w; w0++)
		{
			video[(x + (y + h0) * 80) + w0] = c << 8 | 0x20;
		}
	}
}*/