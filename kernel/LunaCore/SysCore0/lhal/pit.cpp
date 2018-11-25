#include "idt.h"
#include "pit.h"
#include "pic.h"
#include <lhal.h>

#define		I86_PIT_REG_COUNTER0		0x40
#define		I86_PIT_REG_COUNTER1		0x41
#define		I86_PIT_REG_COUNTER2		0x42
#define		I86_PIT_REG_COMMAND			0x43

static volatile uint32_t _pit_ticks = 0;
static bool	_pit_bIsInit = false;

void _cdecl LUNA_IRQ_HANDLER();
void _cdecl LUNA_IRQ_HANDLER()
{
	_asm add esp,12
	_asm pushad
	_pit_ticks++;
	LUNA_interruptdone(0);
	_asm popad
	_asm iretd
}

uint32_t LUNA_INER_I86_PIT_STC(uint32_t i)
{
	uint32_t ret = _pit_ticks;
	_pit_ticks = i;
	return ret;
}

uint32_t LUNA_INER_I86_PIT_GTC()
{
	return _pit_ticks;
}

void LUNA_INER_I86_PIT_SCOMMAND(uint8_t cmd)
{
	LUNA_PortOUT(I86_PIT_REG_COMMAND, cmd);
}

void LUNA_INER_I86_PIT_SDATA(uint8_t dat, uint8_t counter)
{
	uint8_t p = (counter == I86_PIT_OCW_COUNTER_0) ? I86_PIT_REG_COUNTER0 :
		((counter == I86_PIT_OCW_COUNTER_1) ? I86_PIT_REG_COUNTER1 : I86_PIT_REG_COUNTER2);
	LUNA_PortOUT(p, (uint8_t)dat);
}

uint8_t LUNA_INER_I86_PIT_RDATA(uint16_t counter)
{
	uint8_t p = (counter == I86_PIT_OCW_COUNTER_0) ? I86_PIT_REG_COUNTER0 :
		((counter == I86_PIT_OCW_COUNTER_1) ? I86_PIT_REG_COUNTER1 : I86_PIT_REG_COUNTER2);
	return LUNA_PortIN(p);
}

void LUNA_INER_I86_PIT_SCOUNT(uint32_t freq, uint8_t counter, uint8_t mode)
{
	if (freq == 0)
		return;
	uint16_t divisor = uint16_t(1193181 / (uint16_t)freq);
	uint8_t ocw_ = 0;
	ocw_ = (ocw_&~I86_PIT_OCW_MASK_MODE) | mode;
	ocw_ = (ocw_&~I86_PIT_OCW_MASK_RL) | I86_PIT_OCW_RL_DATA;
	ocw_ = (ocw_&~I86_PIT_OCW_MASK_COUNTER) | counter;
	LUNA_INER_I86_PIT_SCOMMAND(ocw_);

	LUNA_INER_I86_PIT_SDATA(divisor & 0xff, 0);
	LUNA_INER_I86_PIT_SDATA((divisor >> 8) & 0xff, 0);

	_pit_ticks = 0;
}

void _cdecl LUNA_INER_I86_PIT_INITIALIZE()
{
	LUNA_set_INTvect(32, LUNA_IRQ_HANDLER);
	_pit_bIsInit = true;
}

bool _cdecl LUNA_I86_PIT_IS_INIT()
{
	return _pit_bIsInit;
}