#include "idt.h"
#include <string.h>
#include <lhal.h>
#include "../SysCore0/CVDC/CELESTIA_DIP.h"
#ifdef _MSC_VER
#pragma pack (push,1)
#endif

struct idtr{
	uint16_t lim;
	uint32_t base;
};

#ifdef _MSC_VER
#pragma pack(pop,1)
#endif

static struct idt_descriptor _idt[I86_MAX_INTERRUPTS];
static struct idtr _idtr;
static void LUNA_idt_install();
static void LUNA_i86_default_hander();

static void LUNA_idt_install()
{
#ifdef _MSC_VER
	_asm lidt [_idtr]
#endif
}

static void _cdecl LUNA_i86_default_hander()
{
	//添加中断处理方法
	/*CELE_CLR(0x18);
	CELE_GtXY(0, 0);
	CELE_SetColor(0x14);
	CELE_printf("[LUNAIX] AN INTERCEPT OCCURS , SYSTEM HALTED!");*/
	for (;;);
}

idt_descriptor* LUNA_i86_get_ir(uint32_t i)
{
	if (i > I86_MAX_INTERRUPTS)
	{
		return 0;
	}
	return &_idt[i];
}

int LUNA_i86_install_ir(uint32_t i, uint16_t flags, uint16_t sel, I86_IRQ_HANDLER irq)
{
	if (i > I86_MAX_INTERRUPTS)
		return 0;
	if (!irq)
		return 0;
	uint64_t uiB = (uint64_t)&(*irq);

	_idt[i].baseLo = uint16_t(uiB & 0xffff);
	_idt[i].baseHi = uint16_t((uiB >> 16) & 0xffff);
	_idt[i].reserved = 0;
	_idt[i].flags = uint8_t(flags);
	_idt[i].sel = sel;

	return 0;
}

int LUNA_i86_idt_initialize(uint16_t codeSel)
{
	_idtr.lim = sizeof(struct idt_descriptor) * I86_MAX_INTERRUPTS - 1;
	_idtr.base = (uint32_t)&_idt[0];

	memset((void*)&_idt[0], 0, sizeof(idt_descriptor) * I86_MAX_INTERRUPTS - 1);
	for (int i = 0; i < I86_MAX_INTERRUPTS; i++)
	{
		//注册一个中断
		LUNA_i86_install_ir(i, I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32, codeSel, (I86_IRQ_HANDLER)LUNA_i86_default_hander);
	}
	LUNA_idt_install();
	return 0;
}