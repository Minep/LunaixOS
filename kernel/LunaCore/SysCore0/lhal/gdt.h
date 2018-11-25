/*******************************************************
//			LUNA HARDWARE ABSTRACT LAYER LIBRARY
//				For LUNAIX OPERATING SYSTEM
//					   CPR Lunaixsky
//			------------------------------------
//	This layer provide basic hardwaare access services
//
// GDT.H -------------------------
//		provide basic memory mapping and permission level
********************************************************/

// SIG: A brony who love Luna			DB 0x44AA
#ifndef _GDT_H_INCED
#define _GDT_H_INCED
#ifndef ARCH_X86
#error ">>>[FATAL] COULD NOT COMPLIED lhal.lunalib. THIS LIB REQUIRE X86 PLATEFORM"
#endif
#include <stdint.h>
#define MAX_DESCRIPTORS					3

/***	 全局描述符访问权限标识  	***/

//! set access bit
#define I86_GDT_DESC_ACCESS			0x0001			//00000001
#define I86_GDT_DESC_READWRITE			0x0002			//00000010
#define I86_GDT_DESC_EXPANSION			0x0004			//00000100
#define I86_GDT_DESC_EXEC_CODE			0x0008			//00001000
#define I86_GDT_DESC_CODEDATA			0x0010			//00010000
#define I86_GDT_DESC_DPL			0x0060			//01100000
#define I86_GDT_DESC_MEMORY			0x0080			//10000000

/**	全局描述符间隔标识	***/

#define I86_GDT_GRAND_LIMITHI_MASK		0x0f			//00001111
#define I86_GDT_GRAND_OS			0x10			//00010000
#define I86_GDT_GRAND_32BIT			0x40			//01000000
#define I86_GDT_GRAND_4K			0x80			//10000000

#ifdef _MSC_VER
#pragma pack (push,1) 
#endif

struct gdt_descriptor
{
	uint16_t		limit;
	//! bits 0-23 of base address
	uint16_t		baseLo;
	uint8_t			baseMid;
	//! descriptor access flags
	uint8_t			flags;
	uint8_t			grand;
	//! bits 24-32 of base address
	uint8_t			baseHi;
};
#ifdef _MSC_VER
#pragma pack (pop)
#endif

//! Setup a descriptor in the Global Descriptor Table
extern void LUNA_gdt_set_descriptor(uint32_t i, uint64_t base, uint64_t limit, uint8_t access, uint8_t grand);
//! returns descritor
extern gdt_descriptor* LUNA_i86_gdt_get_descriptor(int i);
//! initializes gdt
extern	int LUNA_i86_gdt_initialize();
#endif