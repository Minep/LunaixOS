#ifndef LUNAIX_MMNGR_H
#define LUNAIX_MMNGR_H
#include <stdint.h>

//! physical address
typedef	uint32_t physical_addr;
//初始化物理内存管理器
extern	void LUNAIX_pmmngr_init(size_t ms, physical_addr btmap);
//开启可用内存区域
extern	void LUNAIX_pmmngr_init_region(physical_addr, size_t);
//禁用正在使用的内存区域
extern	void LUNAIX_pmmngr_deinit_region(physical_addr adbase, size_t);
//分配单区块
extern	void* LUNAIX_pmmngr_alloc_block();
//释放区块
extern	void LUNAIX_pmmngr_free_block(void*);
//分配内存区块
extern	void* LUNAIX_pmmngr_alloc_blocks(size_t);
//释放区块 所有
extern	void LUNAIX_pmmngr_free_blocks(void*, size_t);
//获取管理器所分配的内存数量
extern	size_t LUNAIX_pmmngr_get_memory_size();
//正在使用的内存数量
extern	uint32_t LUNAIX_pmmngr_get_use_block_count();
//空闲内存
extern	uint32_t LUNAIX_pmmngr_get_free_block_count();
//内存区块总数
extern	uint32_t LUNAIX_pmmngr_get_block_count();
//单个区块大小（字节）
extern uint32_t LUNAIX_pmmngr_get_block_size();
//启动或禁用内存分页
extern	void LUNAIX_pmmngr_paging_enable(bool);
//是否已分页？
extern	bool LUNAIX_pmmngr_is_paging();
//! loads the page directory base register (PDBR)
extern	void LUNAIX_pmmngr_load_PDBR(physical_addr);
//! get PDBR physical address
extern	physical_addr LUNAIX_pmmngr_get_PDBR();
#endif