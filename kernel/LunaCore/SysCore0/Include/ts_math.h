/****************************************
//		Luna   C++   Runtime    Library
//			  Mathematic support
//		   Moduel Twilight Sparkle
//		   Lunaix Operating System
//			   >CPR Lunaixsky<
******************************************/

#ifndef _TWILIGHT_MATH_INC
#define _TWILIGHT_MATH_INC

/*************************************
 *	Mathematical Constant Declaretion*
 *************************************/
//��Ȼ���� e
#define E  2.7182818
//Բ���� pi
#define PI 3.1415926
//�ƽ�ָ�� psi
#define PSI 0.618034
//���õ³��� B'L
#define BdL 1.08366
/*******End of Constant Define********/

/*************************************
*	Mathematical Function Declaretion*
*************************************/
extern float TS_ABS(float num);
extern float TS_FLOOR(float num);
extern float TS_ROUND(float num);
extern float TS_SIN(float x);
extern float TS_COS(float x);
//extern float TS_TAN(float x);
extern float TS_TORAD(float deg);
extern float TS_TODEG(float rad);
extern double TS_POW(double base, int exp);
#endif