#include "LX_VMGR_PTE.h"

inline void LX_PT_ENT_ADD_ATTR(pt_entry* e, uint32_t attr)
{
	*e |= attr;
}

inline void LX_PT_ENT_DEL_ATTR(pt_entry* e, uint32_t attr)
{
	*e &= ~attr;
}

inline void LX_PT_ENT_SET_FRAME(pt_entry* e, physical_addr addr)
{
	*e = (*e & ~I86_PTE_FRAME) | addr;
}

inline bool LX_PT_ENT_IS_PRESENT(pt_entry e)
{
	return  e&I86_PTE_PRESENT;
}

inline bool LX_PT_ENT_IS_WRITEBLE(pt_entry e)
{
	return e & I86_PTE_WRITABLE;
}

inline physical_addr LX_PT_ENT_PFN(pt_entry e)
{
	return e & I86_PTE_FRAME;
}