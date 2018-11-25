#include "LX_VMGR_PDE.h"
inline void LX_PD_ENT_ADD_ATTR(pd_entry* e, uint32_t attr)
{
	*e |= attr;
}

inline void LX_PD_ENT_DEL_ATTR(pd_entry* e, uint32_t attr)
{
	*e &= ~attr;
}

inline void LX_PD_ENT_SET_FRAME(pd_entry* e, physical_addr a)
{
	*e = (*e & ~I86_PDE_FRAME) | a;
}

inline bool LX_PD_ENT_IS_PRESENT(pd_entry e)
{
	return e&I86_PDE_PRESENT;
}

inline bool LX_PD_ENT_IS_USER(pd_entry e)
{
	return e & I86_PDE_USER;
}

inline bool LX_PD_ENT_IS_4MB(pd_entry e)
{
	return e & I86_PDE_4MB;
}

inline bool LX_ENT_IS_WRITEABLE(pd_entry e)
{
	return e & I86_PDE_WRITABLE;
}

inline physical_addr LX_PD_ENT_PFN(pd_entry e)
{
	return e & I86_PDE_FRAME;
}

void LX_ENABLE_GLOBAL(pd_entry e)
{
	//Unimplement yet..
}