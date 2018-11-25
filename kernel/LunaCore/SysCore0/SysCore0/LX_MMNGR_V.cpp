#include <string.h>
#include "LX_MMNGR.h"
#include "LX_MMNGR_V.h"

#define PTABLE_ADDR_SPACE_SIZE 0x400000
#define DTABLE_ADDR_SPACE_SIZE 0x100000000
#define PAGE_SIZE 4096

pdirectory*		_cur_directory = 0;
physical_addr	_cur_pdbr = 0;

inline pt_entry* vmngr_ptable_lkup_ent(ptable* p, virtual_addr vad)
{
	if (p)
	{
		return &p->m_entries[PAGE_TABLE_INDEX(vad)];
	}
	return 0;
}

inline pt_entry* vmngr_pdir_lkup_ent(pdirectory* p, virtual_addr vad)
{
	if (p)
	{
		return &p->m_entries[PAGE_TABLE_INDEX(vad)];
	}
	return 0;
}

inline bool LUNAIX_vmngr_swpdir(pdirectory* d)
{
	if (!d)
	{
		return false;
	}
	_cur_directory = d;
	LUNAIX_pmmngr_load_PDBR(_cur_pdbr);
	return true;
}

void LUNAIX_flush_tlb_ent(virtual_addr vad)
{
	_asm
	{
		cli
		invlpg vad
		sti
	}
}

pdirectory* LUNAIX_vmngr_gtdir()
{
	return _cur_directory;
}

bool LUNAIX_vmngr_alloc_page(pt_entry* e)
{
	void* p = LUNAIX_pmmngr_alloc_block();
	if (!p)
	{
		return false;
	}
	LX_PT_ENT_SET_FRAME(e, (physical_addr)p);
	LX_PT_ENT_ADD_ATTR(e, I86_PTE_PRESENT);
	return true;
}

void LUNAIX_vmngr_free_page(pt_entry* e)
{
	void* p = (void*)LX_PT_ENT_PFN(*e);
	if (p)
		LUNAIX_pmmngr_free_block(p);
	LX_PT_ENT_DEL_ATTR(e, I86_PTE_PRESENT);
}

void LUNAIX_vmngr_map_P(void* phy, void* v)
{
	pdirectory* pageDir = LUNAIX_vmngr_gtdir();
	pd_entry* e = &pageDir->m_entries[PAGE_DIRECTORY_INDEX((uint32_t)v)];
	if ((*e & I86_PTE_PRESENT) != I86_PTE_PRESENT)
	{
		ptable* table = (ptable*)LUNAIX_pmmngr_alloc_block();
		if (!table)
		{
			return;
		}
		memset(table, 0, sizeof(ptable));
		pd_entry* ent = &pageDir->m_entries[PAGE_DIRECTORY_INDEX((uint32_t)v)];
		LX_PD_ENT_ADD_ATTR(ent, I86_PDE_PRESENT);
		LX_PD_ENT_ADD_ATTR(ent, I86_PDE_WRITABLE);
		LX_PD_ENT_SET_FRAME(ent, (physical_addr)table);
	}
	ptable* t = (ptable*)PAGE_GET_PHYSICAL_ADDRESS(e);
	pt_entry* page = &t->m_entries[PAGE_TABLE_INDEX((uint32_t)v)];
	LX_PT_ENT_SET_FRAME(page, (physical_addr)phy);
	LX_PT_ENT_ADD_ATTR(page, I86_PTE_PRESENT);
}

void LUNAIX_vmngr_initialize() {

	//! allocate default page table
	ptable* table = (ptable*)LUNAIX_pmmngr_alloc_block();
	if (!table)
		return;

	ptable* table2 = (ptable*)LUNAIX_pmmngr_alloc_block();
	if (!table2)
		return;

	memset(table, 0, sizeof(ptable));

	for (int i = 0, frame = 0x0, virt = 0x00000000; i<1024; i++, frame += 4096, virt += 4096) {

		pt_entry page = 0;
		LX_PT_ENT_ADD_ATTR(&page, I86_PTE_PRESENT);
		LX_PD_ENT_SET_FRAME(&page, frame);

		table2->m_entries[PAGE_TABLE_INDEX(virt)] = page;
	}

	for (int i = 0, frame = 0x100000, virt = 0xc0000000; i<1024; i++, frame += 4096, virt += 4096) {
		pt_entry page = 0;
		LX_PT_ENT_ADD_ATTR(&page, I86_PTE_PRESENT);
		LX_PD_ENT_SET_FRAME(&page, frame);

		table->m_entries[PAGE_TABLE_INDEX(virt)] = page;
	}
	pdirectory*   dir = (pdirectory*)LUNAIX_pmmngr_alloc_blocks(3);
	if (!dir)
		return;
	memset(dir, 0, sizeof(pdirectory));

	pd_entry* entry = &dir->m_entries[PAGE_DIRECTORY_INDEX(0xc0000000)];
	LX_PD_ENT_ADD_ATTR(entry, I86_PDE_PRESENT);
	LX_PD_ENT_ADD_ATTR(entry, I86_PDE_WRITABLE);
	LX_PD_ENT_SET_FRAME(entry, (physical_addr)table);

	pd_entry* entry2 = &dir->m_entries[PAGE_DIRECTORY_INDEX(0x00000000)];
	LX_PD_ENT_ADD_ATTR(entry2, I86_PDE_PRESENT);
	LX_PD_ENT_ADD_ATTR(entry2, I86_PDE_WRITABLE);
	LX_PD_ENT_SET_FRAME(entry2, (physical_addr)table2);

	_cur_pdbr = (physical_addr)&dir->m_entries;

	//! switch to our page directory
	LUNAIX_vmngr_swpdir(dir);

	//! enable paging
	LUNAIX_pmmngr_paging_enable(true);
}