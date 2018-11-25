#include "ts_math.h"
bool equalZero(double number)
{
	if (number < 0.000001 && number > -0.000001)
		return true;
	else
		return false;
}

double _myPow(double base, int exp)
{
	if (exp == 0)
		return 1;
	if (exp == 1)
		return base;

	double result = _myPow(base, exp >> 1);
	result *= result;
	if (exp & 0x01)
		result *= base;

	return result;
}

double _myPow2(double base, int exp)
{
	if (exp == 0)
		return 1;

	double result = 1;
	while (exp)
	{
		if (exp & 0x01)
			result *= base;
		base *= base;
		exp = exp >> 1;
	}

	return result;
}

double TS_POW(double base, int exp)
{
	if (equalZero(base))
		return 0;
	if (exp == 0)
		return 1;

	bool flag = false;
	if (exp < 0)
	{
		flag = true;
		exp = -exp;
	}

	double result = _myPow2(base, exp);
	if (flag)
	{
		result = 1 / result;
	}

	return result;
}