#include "LX_MMNGR.h"
#include <string.h>

#define LX_PMMNGR_BLOCKS_PER_BYTE 8
#define LX_PMMNGR_BLOCK_SIZE 4096
#define LX_PMMNGR_BLOCK_ALIGN LX_PMMNGR_BLOCK_SIZE

static uint32_t _lx_mmngr_memory_size = 0;
static uint32_t _lx_mmngr_used_blocks = 0;
static uint32_t _lx_mmngr_max_blocks = 0;
static uint32_t* _lx_mmngr_memory_map = 0;

inline void lx_mmap_set(int bit);
inline void lx_mmap_unset(int bit);
inline bool lx_mmap_test(int bit);
int lx_mmap_first_free();
int lx_mmap_first_free_s(size_t size);

inline void lx_mmap_set(int bit)
{
	_lx_mmngr_memory_map[bit / 32] |= (1 << (bit % 32));
}

inline void lx_mmap_unset(int bit)
{
	_lx_mmngr_memory_map[bit / 32] &= ~(1 << (bit % 32));
}

inline bool lx_mmap_test(int bit)
{
	return _lx_mmngr_memory_map[bit / 32] & (1 << (bit % 32));
}

int lx_mmap_first_free()
{
	for (uint32_t ix = 0; ix < LUNAIX_pmmngr_get_block_count() / 32; ix++)
	{
		if (_lx_mmngr_memory_map[ix] != 0xffffffff)
		{
			for (int jx = 0; jx < 32; jx++)
			{
				int bit = 1 << jx;
				if (!(_lx_mmngr_memory_map[ix] & bit))
				{
					return ix * 4 * 8 + jx;
				}
			}
		}
	}
	return -1;
}

int lx_mmap_first_free_s(size_t size)
{
	if (size == 0)
		return -1;
	if (size == 1)
		return lx_mmap_first_free();
	for (uint32_t i = 0; i < LUNAIX_pmmngr_get_block_count() / 32; i++)
	{
		if (_lx_mmngr_memory_map[i] != 0xffffffff)
		{
			for (int j = 0; j < 32; j++)
			{
				int bit = 1 << j;
				if (!(_lx_mmngr_memory_map[i] & bit))
				{
					int sbit = i * 32;
					sbit += bit;
					uint32_t free = 0;
					for (uint32_t c = 0; c <= size; c++)
					{
						if (!lx_mmap_test(sbit + c))
						{
							free++;
						}
						if (free == size)
						{
							return i * 4 * 8 + j;
						}
					}
				}
			}
		}
	}
	return -1;
}

/************************************
//		Define for LUNAIX_PMMNGR
//
*************************************/

void LUNAIX_pmmngr_init(size_t ms, physical_addr btmap)
{
	_lx_mmngr_memory_size = ms;
	_lx_mmngr_memory_map = (uint32_t*)btmap;
	_lx_mmngr_max_blocks = (LUNAIX_pmmngr_get_memory_size() * 1024) / LX_PMMNGR_BLOCK_SIZE;
	_lx_mmngr_used_blocks = _lx_mmngr_used_blocks;
	memset(_lx_mmngr_memory_map, 0xf, LUNAIX_pmmngr_get_block_count());
}

void LUNAIX_pmmngr_init_region(physical_addr adbase, size_t s)
{
	int align = adbase;
	int blocks = s;
	for (; blocks >= 0; blocks--)
	{
		lx_mmap_unset(align++);
		_lx_mmngr_used_blocks--;
	}
	lx_mmap_set(0);
}

void LUNAIX_pmmngr_deinit_region(physical_addr adbase, size_t s)
{
	int align = adbase;
	int blocks = s;
	for (; blocks >= 0; blocks--)
	{
		lx_mmap_set(align++);
		_lx_mmngr_used_blocks++;
	}
}

void* LUNAIX_pmmngr_alloc_block()
{
	if (LUNAIX_pmmngr_get_free_block_count() <= 0)
	{
		return 0;
	}
	int frame = lx_mmap_first_free();
	if (frame == -1)
	{
		return 0;
	}
	lx_mmap_set(frame);
	physical_addr addr = frame*LX_PMMNGR_BLOCK_SIZE;
	_lx_mmngr_max_blocks++;
	return (void*)addr;
}

void LUNAIX_pmmngr_free_block(void* pt)
{
	physical_addr addr = (physical_addr)pt;
	int frame = addr / LX_PMMNGR_BLOCK_SIZE;
	lx_mmap_unset(frame);
	_lx_mmngr_used_blocks--;
}

void* LUNAIX_pmmngr_alloc_blocks(size_t s)
{
	if (LUNAIX_pmmngr_get_free_block_count() <= s)
	{
		return 0;
	}
	int frame = lx_mmap_first_free_s(s);
	if (frame == -1)
	{
		return 0;
	}
	for (uint32_t i = 0; i < s; i++)
	{
		lx_mmap_set(frame + i);
	}
	physical_addr addr = frame + LX_PMMNGR_BLOCK_SIZE;
	_lx_mmngr_used_blocks += s;
	return (void*)addr;
}

void LUNAIX_pmmngr_free_blocks(void* pt, size_t s)
{
	physical_addr addr = (physical_addr)pt;
	int frame = addr / LX_PMMNGR_BLOCK_SIZE;
	for (uint32_t i = 0; i < s; i++)
	{
		lx_mmap_unset(frame + i);
	}
	_lx_mmngr_used_blocks -= s;
}

size_t LUNAIX_pmmngr_get_memory_size()
{
	return _lx_mmngr_memory_size;
}

uint32_t LUNAIX_pmmngr_get_use_block_count()
{
	return _lx_mmngr_used_blocks;
}

uint32_t LUNAIX_pmmngr_get_block_count()
{
	return _lx_mmngr_max_blocks;
}

uint32_t LUNAIX_pmmngr_get_free_block_count()
{
	return _lx_mmngr_max_blocks - _lx_mmngr_used_blocks;
}

uint32_t LUNAIX_pmmngr_get_block_size()
{
	return LX_PMMNGR_BLOCK_SIZE;
}

void LUNAIX_pmmngr_paging_enable(bool b)
{
	_asm
	{
		mov eax,cr0
		cmp[b],1
		je enb
		jmp dis
	enb:
		or eax, 0x80000000
		mov cr0,eax
		jmp dn
	dis:
		and eax, 0x7FFFFFFF
		mov cr0,eax
	dn:
	}
}

bool LUNAIX_pmmngr_is_paging()
{
	uint32_t rl = 0;
	_asm
	{
		mov eax,cr0
		mov [rl], eax
	}
	return (rl & 0x80000000) ? false : true;
}
void LUNAIX_pmmngr_load_PDBR(physical_addr addr) 
{
	_asm {
		mov	eax, [addr]
			mov	cr3, eax		// PDBR is cr3 register in i86
	}
}

physical_addr LUNAIX_pmmngr_get_PDBR() 
{
	_asm {
		mov	eax, cr3
			ret
	}
}
