/*************************************************
*			Kernel setup for Lunaix
*			  Copyright Lunaixsky
*
**************************************************/

// Include My Celestia Display Core :)
#include <lhal.h>
#include <LUNAIX_KeyBoard.h>
#include <bootinfo.h>
#include "CVDC\CELESTIA_DIP.h"
#include "CVDC\CELESTIA_COLOR.h"
#include "NightmareMoon.h"
#include "LX_MMNGR.h"
#include "LX_MMNGR_V.h"
#include "LunaOS\os.h"

extern int _cdecl smain();
void MEMORY_PROCESS(multiboot_info* mbi);

struct memory_region {

	uint32_t	startLo;
	uint32_t	startHi;
	uint32_t	sizeLo;
	uint32_t	sizeHi;
	uint32_t	type;
	uint32_t	acpi_3_0;
};

char* LX_strMemoryTypes[] = {

		{ "Available" },			//memory_region.type==0
		{ "Reserved" },			//memory_region.type==1
		{ "ACPI Reclaim" },		//memory_region.type==2
		{ "ACPI NVS Memory" }		//memory_region.type==3
};

uint32_t k_size = 0;
int _cdecl main(multiboot_info* mb)
{
	_asm mov word ptr[k_size], dx
	CELE_CLR(C_BULE_WHITE);
	CELE_GtXY(0, 0);
	CELE_SetColor(C_WHITE_BLACK);
	CELE_printf("* LUNAIX Operating System - Loading System.....                                 ");
	CELE_GtXY(0, 8);
	CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_printf("==================================================================");
	CELE_GtXY(6, 9);
	CELE_printf("#      #   #  #####   ###   ###   #   #      ####    ####\n");
	CELE_printf("#      #   #  #   #  #   #   #     # #      #    #  #    \n");
	CELE_printf("#      #   #  #   #  #   #   #     ##       #    #   ### \n");
	CELE_printf("#      #   #  #   #  #####   #    #  #      #    #      #\n");
	CELE_printf("#####  #####  #   #  #   #  ###  #    #      ####   #### ");
	CELE_GtXY(7, 14);
	CELE_printf("==================================================================\n");
	CELE_GtXY(10, 18);
	CELE_printf("Loading Luna C++ Runtime Library .....");
	CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_GtXY(0, 24);
	CELE_printf(" Loading LRTLib.lunalib ......                                                   ");
	CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_GtXY(10, 18);
	CELE_printf("     Perpearing LunaHALib.....        ");
	CELE_SetColor(C_WHITE_BLACK);
	CELE_GtXY(0, 24);
	CELE_printf(" Loading LHALib.lunalib ......                                                   ");
	/******************************
	//Luna Hardware Abstract Layer
	//		初始化硬件抽象层
	*******************************/
	LHAL_initialize();
	LUNA_ENABLE();
	CELE_SetColor(C_BULE_WHITE);
	CELE_GtXY(10, 18);
	CELE_printf("     Installing Interrupts.....        ");
	CELE_SetColor(C_WHITE_BLACK);
	CELE_GtXY(0, 24);
	CELE_printf(" Initializing Interrupts ......                                                  ");
	
	//*********初始化32位下的中断向量***********
	LUNA_set_INTvect(0, (void(__cdecl &)(void))NM_divide_by_zero_fault);
	LUNA_set_INTvect(1, (void(__cdecl &)(void))NM_single_step_trap);
	LUNA_set_INTvect(2, (void(__cdecl &)(void))NM_nmi_trap);
	LUNA_set_INTvect(3, (void(__cdecl &)(void))NM_breakpoint_trap);
	LUNA_set_INTvect(4, (void(__cdecl &)(void))NM_overflow_trap);
	LUNA_set_INTvect(5, (void(__cdecl &)(void))NM_bounds_check_fault);
	LUNA_set_INTvect(6, (void(__cdecl &)(void))NM_invalid_opcode_fault);
	LUNA_set_INTvect(7, (void(__cdecl &)(void))NM_no_device_fault);
	LUNA_set_INTvect(8, (void(__cdecl &)(void))NM_double_fault_abort);
	LUNA_set_INTvect(10, (void(__cdecl &)(void))NM_invalid_tss_fault);
	LUNA_set_INTvect(11, (void(__cdecl &)(void))NM_no_segment_fault);
	LUNA_set_INTvect(12, (void(__cdecl &)(void))NM_stack_fault);
	LUNA_set_INTvect(13, (void(__cdecl &)(void))NM_general_protection_fault);
	LUNA_set_INTvect(14, (void(__cdecl &)(void))NM_page_fault);
	LUNA_set_INTvect(16, (void(__cdecl &)(void))NM_fpu_fault);
	LUNA_set_INTvect(17, (void(__cdecl &)(void))NM_alignment_check_fault);
	LUNA_set_INTvect(18, (void(__cdecl &)(void))NM_machine_check_abort);
	LUNA_set_INTvect(19, (void(__cdecl &)(void))NM_simd_fpu_fault);
	MEMORY_PROCESS(mb);
	//LUNA_geninterrupt(0x5);
	RD_keyb_Initialize(33);
	smain();
	//smain();
	/************DUMPED*************/

	//LUNA_geninterrupt(0x5); //模拟中断
	//LUNA_CPU_VENDER();
	/*LUA_GT_DATE();
	CELE_GtXY(0, 22);
	CELE_printf("20%z %z.%z  %z:%z:%z",
		LUNA_DATE_GET(LUNA_DATE_YEAR), 
		LUNA_DATE_GET(LUNA_DATE_MONTH), 
		LUNA_DATE_GET(LUNA_DATE_DAY),
		LUNA_DATE_GET(LUNA_DATE_HOUR),
		LUNA_DATE_GET(LUNA_DATE_MINUTE),
		LUNA_DATE_GET(LUNA_DATE_SECOND));*/
	return 0;
}

void MEMORY_PROCESS(multiboot_info* mbi)
{
	CELE_CLR(C_BULE_WHITE);
	CELE_GtXY(0, 0);
	CELE_SetColor(C_WHITE_BLACK);
	CELE_printf("* LUNAIX Operating System - Initializing Memory....                             ");
	CELE_GtXY(0, 1);
	CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_printf("#      #   #  #####   ###   ###   #  #  |\n");
	CELE_printf("#      #   #  #   #  #   #   #     #    |\n");
	CELE_printf("#      #   #  #   #  #####   #    # #   |\n");
	CELE_printf("#####  #####  #   #  #   #  ###  #   #  |\n");
	CELE_printf("----------------------------------------+\n");
	uint32_t memS = 1024 + mbi->m_memoryLo + mbi->m_memoryHi * 64;
	LUNAIX_pmmngr_init(memS, 0x100000 + k_size);
	CELE_SetColor(C_BULE_GREEN | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_printf("[LUNA'S INFO] ");
	CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_printf("Initialized $i MB Memory (Physical Memory) Successed.\n", memS);
	uint32_t* memInfo = (uint32_t*)0x3000;
	*memInfo = memS;
	memory_region* r = (memory_region*)0x1000;
	for (int i = 0; i < 15; ++i)
	{
		if (r[i].type > 4)
			break;
		if (i > 0 && r[i].startLo == 0)
		{
			break;
		}
		CELE_SetColor(C_BULE_GREEN | C_OPT_HIGHLIGHT_FOREGROUND);
		CELE_printf("[LUNA'S INFO] ");
		CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
		CELE_printf("Memory Region <$i> start at 0x$x$x with size 0x$x$x ($z).\n",
			i,
			r[i].startHi,
			r[i].startLo,
			r[i].sizeHi,r[i].sizeLo,
			LX_strMemoryTypes[r[i].type-1]);
		if (CELE_GtY() >= 23)
		{
			CELE_CLR_SPC(C_BULE_WHITE, 7);
			CELE_GtXY(0, 7);
		}
		if (r[i].type == 1)
		{
			LUNAIX_pmmngr_init_region(r[i].startLo, r[i].sizeLo);
		}
	}
	CELE_SetColor(C_BULE_PINK | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_printf("[LUNA'S STATUS] ");
	CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_printf("Unregistering memory region at 0x100000\n");
	LUNAIX_pmmngr_deinit_region(0x100000, k_size);
	/*
	CELE_SetColor(C_BULE_GREEN | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_printf("[LUNA'S INFO] ");
	CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_printf("All regions initialize completely! Allocated $i blocks\n",LUNAIX_pmmngr_get_block_count());

	CELE_SetColor(C_BULE_GREEN | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_printf("[LUNA'S INFO] ");
	CELE_SetColor(C_BULE_WHITE | C_OPT_HIGHLIGHT_FOREGROUND);
	CELE_printf("Allocating 4 blocks for LUNAIX at 0x$x\n", (uint32_t*)LUNAIX_pmmngr_alloc_blocks(4));

	*/
	//LUNAIX_vmngr_initialize();
}