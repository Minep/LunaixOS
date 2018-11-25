/*******************************************************
//			LUNA HARDWARE ABSTRACT LAYER LIBRARY
//				For LUNAIX OPERATING SYSTEM
//					   CPR Lunaixsky
//			------------------------------------
//	This layer provide basic hardwaare access services
//
// CPU.H -------------------------
//		provide basic interface of CPU
********************************************************/
#include "cpu.h"
#include "gdt.h"
#include "idt.h"

int LUNA_x86_cpu_initialize()
{
	//初始化全局描述符
	LUNA_i86_gdt_initialize();
	//初始化中断描述表
	LUNA_i86_idt_initialize(0x8);
	return 0;
}

void LUNA_x86_cpu_kill()
{
	//...
}

char* LUNA_x86_CPU_VENDER()
{
	static char vender[32] = { 0 };
#ifdef _MSC_VER
	_asm
	{
		mov eax,0
		cpuid
		mov dword ptr [vender],		ebx
		mov dword ptr [vender+4],	edx
		mov dword ptr [vender+8],	ecx
	}
#endif
	return vender;
}