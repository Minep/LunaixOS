/*#######################################
*				Kernel Entry
*			Copyright Lunaixsky
########################################*/
#include <bootinfo.h>
extern int _cdecl main(multiboot_info* mb);
extern void _cdecl InitializeConstructors();
extern void _cdecl Exit();

void _cdecl KEntry(multiboot_info* mb)
{
#ifdef ARCH_X86
	_asm
	{
		cli						// clear interrupts--Do not enable them yet
		mov ax, 10h				// offset 0x10 in gdt for data selector, remember?
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		mov ss, ax				// Set up base stack
		mov esp, 0x90000
		mov ebp, esp			// store current stack pointer
		push ebp
	}
#endif
	InitializeConstructors();
	main(mb);
	Exit();
#ifdef ARCH_X86
	_asm cli
#endif
	for (;;);
}