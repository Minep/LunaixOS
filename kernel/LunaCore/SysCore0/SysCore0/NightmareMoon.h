#ifndef __NIGHTMARE_MOON_H_INC
#define __NIGHTMARE_MOON_H_INC

extern void _cdecl NM_divide_by_zero_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);
//单步执行
extern void _cdecl NM_single_step_trap(unsigned int cs,
	unsigned int eip, unsigned int eflags);

extern void _cdecl NM_nmi_trap(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//遇到断点
extern void _cdecl NM_breakpoint_trap(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//溢出
extern void _cdecl NM_overflow_trap(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//边界检查
extern void _cdecl NM_bounds_check_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//非法指令
extern void _cdecl NM_invalid_opcode_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//设备未就绪
extern void _cdecl NM_no_device_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//双重错误
extern void _cdecl NM_double_fault_abort(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//非法任务状态段
extern void _cdecl NM_invalid_tss_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//段未就绪
extern void _cdecl NM_no_segment_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//堆栈错误
extern void _cdecl NM_stack_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//一般保护错误
extern void _cdecl NM_general_protection_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//分页错误
extern void _cdecl NM_page_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//浮点单元错误
extern void _cdecl NM_fpu_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//依赖检查
extern void _cdecl NM_alignment_check_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//外设检查
extern void _cdecl NM_machine_check_abort(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//其它错误
extern void _cdecl NM_simd_fpu_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);
#endif