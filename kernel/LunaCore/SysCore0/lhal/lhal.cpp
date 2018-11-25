#include <lhal.h>
#include "cpu.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
/*******************************************************
//			LUNA HARDWARE ABSTRACT LAYER LIBRARY
//				For LUNAIX OPERATING SYSTEM
//					   CPR Lunaixsky
//			------------------------------------
//	This layer provide basic hardwaare access services
//
// HAL.CPP -------------------------
//		The Global interface of HAL , IMPLIEMENT
********************************************************/
int _cdecl LHAL_initialize()
{
	LUNA_x86_cpu_initialize();
	LUNA_INER_I86_PIC_INITIALIZE(0x20,0x28);
	LUNA_INER_I86_PIT_INITIALIZE();
	LUNA_INER_I86_PIT_SCOUNT(100, I86_PIT_OCW_COUNTER_0, I86_PIT_OCW_MODE_SQUAREWAVEGEN);
	LUNA_ENABLE();
	return 0;
}

int _cdecl LHAL_shutdown()
{
	LUNA_x86_cpu_kill();
	return 0;
}

void _cdecl LUNA_geninterrupt(int n)
{
#ifdef _MSC_VER
	_asm {
		mov al, byte ptr [n]
			mov byte ptr [genint + 1], al
			jmp genint
		genint :
			int 0
	}
#endif
}

inline void	_cdecl  LUNA_interruptdone(unsigned int intid)
{
	if (intid > 16)
	{
		return;
	}
	if (intid >= 8)
		LUNA_INER_I86_PIC_SCOMMAND(I86_PIC_OCW2_MASK_EOI, 1);
	LUNA_INER_I86_PIC_SCOMMAND(I86_PIC_OCW2_MASK_EOI, 0);
}

void _cdecl  LUNA_mksound(unsigned freq)
{
	LUNA_PortOUT(0x61, 3 | unsigned char(freq << 2));
}

unsigned char _cdecl LUNA_PortIN(unsigned short ptid)
{
	_asm
	{
		mov		dx, word ptr [ptid]
		in		al, dx
		mov		byte ptr [ptid], al
	}
	return (unsigned char)ptid;
}

void _cdecl LUNA_PortOUT(unsigned short ptid, unsigned char val)
{
	_asm
	{
		mov al, byte ptr [val]
		mov dx, word ptr [ptid]
		out dx, al
	}
}

void _cdecl LUNA_ENABLE()
{
	_asm sti
}

void _cdecl LUNA_DISABLE()
{
	_asm cli
}

void _cdecl LUNA_set_INTvect(int intid, void (_cdecl far &v)())
{
	LUNA_i86_install_ir(intid, I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32, 0x8, v);
}

void (_cdecl far * _cdecl getvect(int intid))()
{
	idt_descriptor* desct = LUNA_i86_get_ir(intid);
	if (!desct)
		return 0;
	uint32_t adr = desct->baseLo | (desct->baseHi << 16);
	I86_IRQ_HANDLER irq = (I86_IRQ_HANDLER)adr;
	return irq;
}

int _cdecl LUNA_DBG_TICKCOUNT()
{
	return LUNA_INER_I86_PIT_GTC();
}

const char*	 _cdecl  LUNA_CPU_VENDER()
{
	return LUNA_x86_CPU_VENDER();
}