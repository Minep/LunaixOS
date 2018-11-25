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
#ifndef _CPU_H_INCLUDED
# define _CPU_H_INCLUDED
#ifndef ARCH_X86
#error ">>>[FATAL] REQUIRE X86 CPU ARCH"
#endif

#include <stdint.h>
#include "regs.h"

extern int LUNA_x86_cpu_initialize();
extern void LUNA_x86_cpu_kill();
extern char* LUNA_x86_CPU_VENDER();
#endif
