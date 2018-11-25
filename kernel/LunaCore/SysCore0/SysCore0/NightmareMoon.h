#ifndef __NIGHTMARE_MOON_H_INC
#define __NIGHTMARE_MOON_H_INC

extern void _cdecl NM_divide_by_zero_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);
//����ִ��
extern void _cdecl NM_single_step_trap(unsigned int cs,
	unsigned int eip, unsigned int eflags);

extern void _cdecl NM_nmi_trap(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//�����ϵ�
extern void _cdecl NM_breakpoint_trap(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//���
extern void _cdecl NM_overflow_trap(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//�߽���
extern void _cdecl NM_bounds_check_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//�Ƿ�ָ��
extern void _cdecl NM_invalid_opcode_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//�豸δ����
extern void _cdecl NM_no_device_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//˫�ش���
extern void _cdecl NM_double_fault_abort(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//�Ƿ�����״̬��
extern void _cdecl NM_invalid_tss_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//��δ����
extern void _cdecl NM_no_segment_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//��ջ����
extern void _cdecl NM_stack_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//һ�㱣������
extern void _cdecl NM_general_protection_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//��ҳ����
extern void _cdecl NM_page_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//���㵥Ԫ����
extern void _cdecl NM_fpu_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//�������
extern void _cdecl NM_alignment_check_fault(unsigned int cs, unsigned int err,
	unsigned int eip, unsigned int eflags);

//������
extern void _cdecl NM_machine_check_abort(unsigned int cs,
	unsigned int eip, unsigned int eflags);

//��������
extern void _cdecl NM_simd_fpu_fault(unsigned int cs,
	unsigned int eip, unsigned int eflags);
#endif