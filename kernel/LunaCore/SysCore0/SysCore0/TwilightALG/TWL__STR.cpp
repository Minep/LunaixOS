#include "TWI_STR.h"
#include <stdarg.h>
#include "../../Include/string.h"
char* twi_combstr(const char* frame, ...)
{
	va_list args;
	va_start(args,frame);
	char _temp[512];
	memset(_temp, 0, sizeof(_temp));
	int x = 0;
	for (size_t st = 0; st < strlen(frame); st++)
	{
		switch (frame[st+x])
		{
		case '$':{
			switch (frame[st+1+x])
			{
			case 's':
			{
				char* c = va_arg(args, char*);
				for (size_t i = 0; i < strlen(c); i++)
				{
					_temp[st + i + x] = c[i];
				}
				x += strlen(c) - 1;
				st++;
			}
			default:
				va_end(args);
				return 0;
			}
			break;
		}
		default:
			_temp[st + x] = frame[st + x];
			break;
		}
	}
	va_end(args);
	return _temp;
}

int ts_atoi(const char *str)
{
	int value = 0;
	bool b_plus = true; //判断符号
	switch (*str) //过滤符号
	{
	case '+':
		str++;
		break;
	case '-':
		b_plus = false;
		str++;
		break;
	default:
		break;
	}
	while ('\0' != *str)
	{
		value = (value * 10) + (*str - '0');
		str++;
	}
	if (!b_plus)
		value = -value;
	return value;
}

int ts_ftoa(char *str, float num, int n)        //n是转换的精度，即是字符串'.'后有几位小数
{
	int     sumI;
	float   sumF;
	int     sign = 0;
	int     temp;
	int     count = 0;

	char *p;
	char *pp;

	if (str == 0) return -1;
	p = str;

	/*Is less than 0*/
	if (num < 0)
	{
		sign = 1;
		num = 0 - num;
	}

	sumI = (int)num;    //sumI is the part of int
	sumF = num - sumI;  //sumF is the part of float
	do
	{
		temp = sumI % 10;
		*(str++) = temp + '0';
	} while ((sumI = sumI / 10) != 0);
	if (sign == 1)
	{
		*(str++) = '-';
	}

	pp = str;

	pp--;
	while (p < pp)
	{
		*p = *p + *pp;
		*pp = *p - *pp;
		*p = *p - *pp;
		p++;
		pp--;
	}

	*(str++) = '.';     //point
	do
	{
		temp = (int)(sumF * 10);
		*(str++) = temp + '0';

		if ((++count) == n)
			break;

		sumF = sumF * 10 - temp;

	} while (!(sumF > -0.000001 && sumF < 0.000001));

	*str = '/0';
	return 0;
}