#include <string.h>
#include "gdt.h"

#ifdef _MSC_VER
#pragma pack (push,1)
#endif

struct gdtr
{
	uint16_t m_lim;
	uint32_t m_base;
};

#ifdef _MSC_VER
#pragma pack(pop,1)
#endif

static struct gdt_descriptor _gdt[MAX_DESCRIPTORS];
static struct gdtr _gdtr;

static void LUNA_gdt_install();
static void LUNA_gdt_install()
{
#ifdef _MSC_VER
	_asm lgdt[_gdtr]
#endif
}

void LUNA_gdt_set_descriptor(uint32_t i, uint64_t base, uint64_t limit, uint8_t access, uint8_t grand)
{
	if (i > MAX_DESCRIPTORS)
		return;
	memset((void*)&_gdt[i], 0, sizeof(gdt_descriptor));
	_gdt[i].baseLo = uint16_t(base & 0xffff);
	_gdt[i].baseMid = uint8_t((base >> 16) & 0xff);
	_gdt[i].baseHi = uint8_t((base >> 24) & 0xff);
	_gdt[i].limit = uint16_t(limit & 0xffff);
	_gdt[i].flags = access;
	_gdt[i].grand = uint8_t((limit >> 16) & 0x0f);
	_gdt[i].grand |= grand & 0xf0;
}
gdt_descriptor* LUNA_i86_gdt_get_descriptor(int i)
{
	if (i > MAX_DESCRIPTORS)
		return 0;
	return &_gdt[i];
}
//SETTING UP DESCRIPTOR
int LUNA_i86_gdt_initialize()
{
	_gdtr.m_lim = (sizeof(struct gdt_descriptor) * MAX_DESCRIPTORS) - 1;
	_gdtr.m_base = (uint32_t)&_gdt[0];

	//! set null descriptor
	LUNA_gdt_set_descriptor(0, 0, 0, 0, 0);

	//! set default code descriptor
	LUNA_gdt_set_descriptor(1, 0, 0xffffffff,
		I86_GDT_DESC_READWRITE | I86_GDT_DESC_EXEC_CODE | I86_GDT_DESC_CODEDATA | I86_GDT_DESC_MEMORY,
		I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);

	//! set default data descriptor
	LUNA_gdt_set_descriptor(2, 0, 0xffffffff,
		I86_GDT_DESC_READWRITE | I86_GDT_DESC_CODEDATA | I86_GDT_DESC_MEMORY,
		I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);

	//! install gdtr
	LUNA_gdt_install();

	return 0;
}