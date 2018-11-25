#ifndef LX_MMNGR_VIRT_H
#define LX_MMNGR_VIRT_H
#include <stdint.h>
#include "LX_VMGR_PDE.h"
#include "LX_VMGR_PTE.h"

typedef uint32_t virtual_addr;
#define PAGE_PER_TABLE 1024
#define PAGE_PER_DIR 1024
#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3ff)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3ff)
#define PAGE_GET_PHYSICAL_ADDRESS(x) (*x & ~0xfff)

struct ptable {
	pt_entry m_entries[PAGE_PER_TABLE];
};

//! page directory
struct pdirectory {
	pd_entry m_entries[PAGE_PER_DIR];
};

extern void LUNAIX_MmMapPage(void* phys, void* v);
extern void LUNAIX_vmngr_initialize();
extern bool LUNAIX_vmngr_alloc_page(pt_entry*);
extern void LUNAIX_vmngr_free_page(pt_entry* e);
extern bool LUNAIX_vmngr_swpdir(pdirectory*);
extern pdirectory* LUNAIX_vmngr_gtdir();
extern void LUNAIX_flush_tlb_ent(virtual_addr vad);
extern void LUNAIX_ptable_clr(ptable* p);
extern uint32_t LUNAIX_vmngr_ptable_VTI(virtual_addr vad);
extern pt_entry* LUNAIX_vmngr_ptable_lkup_ent(ptable* p, virtual_addr vad);
extern uint32_t LUNAIX_pdir_VTI(virtual_addr vad);
extern void LUNAIX_vmngr_pdir_clr(pdirectory* dir);
extern pt_entry* LUNAIX_vmngr_pdir_lkup_ent(pdirectory* p, virtual_addr vad);
#endif