#ifndef LUNAIX_MMNGR_H
#define LUNAIX_MMNGR_H
#include <stdint.h>

//! physical address
typedef	uint32_t physical_addr;
//��ʼ�������ڴ������
extern	void LUNAIX_pmmngr_init(size_t ms, physical_addr btmap);
//���������ڴ�����
extern	void LUNAIX_pmmngr_init_region(physical_addr, size_t);
//��������ʹ�õ��ڴ�����
extern	void LUNAIX_pmmngr_deinit_region(physical_addr adbase, size_t);
//���䵥����
extern	void* LUNAIX_pmmngr_alloc_block();
//�ͷ�����
extern	void LUNAIX_pmmngr_free_block(void*);
//�����ڴ�����
extern	void* LUNAIX_pmmngr_alloc_blocks(size_t);
//�ͷ����� ����
extern	void LUNAIX_pmmngr_free_blocks(void*, size_t);
//��ȡ��������������ڴ�����
extern	size_t LUNAIX_pmmngr_get_memory_size();
//����ʹ�õ��ڴ�����
extern	uint32_t LUNAIX_pmmngr_get_use_block_count();
//�����ڴ�
extern	uint32_t LUNAIX_pmmngr_get_free_block_count();
//�ڴ���������
extern	uint32_t LUNAIX_pmmngr_get_block_count();
//���������С���ֽڣ�
extern uint32_t LUNAIX_pmmngr_get_block_size();
//����������ڴ��ҳ
extern	void LUNAIX_pmmngr_paging_enable(bool);
//�Ƿ��ѷ�ҳ��
extern	bool LUNAIX_pmmngr_is_paging();
//! loads the page directory base register (PDBR)
extern	void LUNAIX_pmmngr_load_PDBR(physical_addr);
//! get PDBR physical address
extern	physical_addr LUNAIX_pmmngr_get_PDBR();
#endif