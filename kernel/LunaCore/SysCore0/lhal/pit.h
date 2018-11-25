#ifndef __PIT_H_INC
#define __PIT_H_INC
#include <stdint.h>


#define		I86_PIT_OCW_MASK_BINCOUNT		1		//00000001
#define		I86_PIT_OCW_MASK_MODE			0xE		//00001110
#define		I86_PIT_OCW_MASK_RL				0x30	//00110000
#define		I86_PIT_OCW_MASK_COUNTER		0xC0	//11000000

#define		I86_PIT_OCW_BINCOUNT_BINARY		0		//0
#define		I86_PIT_OCW_BINCOUNT_BCD		1		//1

#define		I86_PIT_OCW_MODE_TERMINALCOUNT	0		//0000
#define		I86_PIT_OCW_MODE_ONESHOT		0x2		//0010
#define		I86_PIT_OCW_MODE_RATEGEN		0x4		//0100
#define		I86_PIT_OCW_MODE_SQUAREWAVEGEN	0x6		//0110
#define		I86_PIT_OCW_MODE_SOFTWARETRIG	0x8		//1000
#define		I86_PIT_OCW_MODE_HARDWARETRIG	0xA		//1010

#define		I86_PIT_OCW_RL_LATCH			0			//000000
#define		I86_PIT_OCW_RL_LSBONLY			0x10		//010000
#define		I86_PIT_OCW_RL_MSBONLY			0x20		//100000
#define		I86_PIT_OCW_RL_DATA				0x30		//110000

#define		I86_PIT_OCW_COUNTER_0			0		//00000000
#define		I86_PIT_OCW_COUNTER_1			0x40	//01000000
#define		I86_PIT_OCW_COUNTER_2			0x80	//10000000

extern void LUNA_INER_I86_PIT_SCOMMAND(uint8_t cmd);
extern void LUNA_INER_I86_PIT_SDATA(uint8_t dat, uint8_t counter);
extern uint8_t LUNA_INER_I86_PIT_RDATA(uint16_t counter);
extern uint32_t LUNA_INER_I86_PIT_STC(uint32_t i);
extern uint32_t LUNA_INER_I86_PIT_GTC();
extern void LUNA_INER_I86_PIT_SCOUNT(uint32_t freq, uint8_t counter, uint8_t mode);
extern void _cdecl LUNA_INER_I86_PIT_INITIALIZE();
extern bool _cdecl LUNA_I86_PIT_IS_INIT();
#endif