#ifndef _LX_VMGR_PDE_H
#define _LX_VMGR_PDE_H
#include <stdint.h>
#include "LX_MMNGR.h"
//I86处理器钦定格式
enum PAGE_PDE_FLAGS {

	I86_PDE_PRESENT = 1,			//0000000000000000000000000000001
	I86_PDE_WRITABLE = 2,			//0000000000000000000000000000010
	I86_PDE_USER = 4,				//0000000000000000000000000000100
	I86_PDE_PWT = 8,				//0000000000000000000000000001000
	I86_PDE_PCD = 0x10,				//0000000000000000000000000010000
	I86_PDE_ACCESSED = 0x20,		//0000000000000000000000000100000
	I86_PDE_DIRTY = 0x40,			//0000000000000000000000001000000
	I86_PDE_4MB = 0x80,				//0000000000000000000000010000000
	I86_PDE_CPU_GLOBAL = 0x100,		//0000000000000000000000100000000
	I86_PDE_LV4_GLOBAL = 0x200,		//0000000000000000000001000000000
	I86_PDE_FRAME = 0x7FFFF000		//1111111111111111111000000000000
};

typedef uint32_t pd_entry;
extern void LX_PD_ENT_ADD_ATTR(pd_entry* e, uint32_t attr);
extern void LX_PD_ENT_DEL_ATTR(pd_entry* e, uint32_t attr);
extern void LX_PD_ENT_SET_FRAME(pd_entry*, physical_addr);
extern bool LX_PD_ENT_IS_PRESENT(pd_entry e);
extern bool LX_PD_ENT_IS_USER(pd_entry);
extern bool LX_PD_ENT_IS_4MB(pd_entry);
extern bool LX_ENT_IS_WRITEABLE(pd_entry e);
extern physical_addr LX_PD_ENT_PFN(pd_entry e);
extern void LX_ENABLE_GLOBAL(pd_entry e);
#endif