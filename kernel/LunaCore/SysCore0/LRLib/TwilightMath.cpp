/****************************************
//		Luna   C++   Runtime    Library
//			  Mathematic support
//		   Moduel Twilight Sparkle
//		   Lunaix Operating System
//			   >CPR Lunaixsky<
******************************************/
#include "../Include/ts_math.h"
float TS_ABS(float num)
{
	if (num > 0)
	{
		return num;
	}
	return 0 - num;
}

float TS_FLOOR(float num)
{
	return 0;
}

float TS_ROUND(float num)
{
	return 0;
}

float TS_SIN(float x)
{
	float __rs;
	__asm
	{
		fld x
		fsin
		fstp __rs
	}
	return __rs;
}

float TS_COS(float x)
{
	float __rs;
	__asm
	{
		fld x
		fcos
		fstp __rs
	}
	return __rs;
}
/*
float TS_TAN(float x)
{
	if (x == 90.00 || x == 270.00)
	{
		return 0.00;
	}
	float __rs;
	__asm
	{
		fld x
		ftan
		fstp __rs
	}
	return __rs;
}
*/
float TS_TORAD(float deg)
{
	return deg*(PI / 180);
}

float TS_TODEG(float rad)
{
	return rad*(180 / PI);
}