#include "NightmareMoon.h"
#include <lhal.h>

extern void _cdecl Nightmare_Moon_Exception(const char* nm_fmt, ...);
#pragma warning (disable:4100)

void  _cdecl NM_divide_by_zero_fault(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Divide by 0");
	for (;;);
}

//! single step
void  _cdecl NM_single_step_trap(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Single step");
	for (;;);
}

//! non maskable  trap
void  _cdecl NM_nmi_trap(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("NMI trap");
	for (;;);
}

//! breakpoint hit
void  _cdecl NM_breakpoint_trap(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Breakpoint trap");
	for (;;);
}

//! overflow
void  _cdecl NM_overflow_trap(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Overflow trap");
	for (;;);
}

//! bounds check
void  _cdecl NM_bounds_check_fault(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Bounds check fault");
	for (;;);
}

//! invalid opcode / instruction
void  _cdecl NM_invalid_opcode_fault(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Invalid opcode");
	for (;;);
}

//! device not available
void  _cdecl NM_no_device_fault(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Device not found");
	for (;;);
}

//! double fault
void  _cdecl NM_double_fault_abort(unsigned int cs, unsigned int err, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Double fault");
	for (;;);
}

//! invalid Task State Segment (TSS)
void  _cdecl NM_invalid_tss_fault(unsigned int cs, unsigned int err, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Invalid TSS");
	for (;;);
}

//! segment not present
void  _cdecl NM_no_segment_fault(unsigned int cs, unsigned int err, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Invalid segment");
	for (;;);
}

//! stack fault
void  _cdecl NM_stack_fault(unsigned int cs, unsigned int err, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Stack fault");
	for (;;);
}

//! general protection fault
void  _cdecl NM_general_protection_fault(unsigned int cs, unsigned int err, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("General Protection Fault");
	for (;;);
}

//! page fault
void  _cdecl NM_page_fault(unsigned int cs, unsigned int err, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Page Fault");
	for (;;);
}

//! Floating Point Unit (FPU) error
void  _cdecl NM_fpu_fault(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("FPU Fault");
	for (;;);
}

//! alignment check
void  _cdecl NM_alignment_check_fault(unsigned int cs, unsigned int err, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Alignment Check");
	for (;;);
}

//! machine check
void  _cdecl NM_machine_check_abort(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("Machine Check");
	for (;;);
}

//! Floating Point Unit (FPU) Single Instruction Multiple Data (SIMD) error
void  _cdecl NM_simd_fpu_fault(unsigned int cs, unsigned int eip, unsigned int eflags) {

	//	intstart ();
	Nightmare_Moon_Exception("FPU SIMD fault");
	for (;;);
}