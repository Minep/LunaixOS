#ifndef _HAL_H
#define _HAL_H
/*******************************************************
//			LUNA HARDWARE ABSTRACT LAYER LIBRARY
//				For LUNAIX OPERATING SYSTEM
//					   CPR Lunaixsky
//			------------------------------------
//	This layer provide basic hardwaare access services
//
// HAL.H -------------------------
//		The Global interface of HAL
********************************************************/
#ifndef ARCH_X86
#pragma error "HAL not implimented for this platform"
#endif

//============================================================================
//    INTERFACE REQUIRED HEADERS
//============================================================================

#include <stdint.h>

#ifdef _MSC_VER
#define interrupt __declspec (naked)
#else
#define interrupt
#endif

#define far
#define near

//! initialize hardware abstraction layer
extern	int _cdecl	LHAL_initialize();

//! shutdown hardware abstraction layer
extern	int _cdecl	LHAL_shutdown ();

//! generates interrupt
extern	void _cdecl	LUNA_geninterrupt (int n);

//�жϵ�������¼� (intid �жϱ��)
extern void			 _cdecl  LUNA_interruptdone(unsigned int intid);
//���������� (freq Ƶ��)
extern void			 _cdecl  LUNA_mksound(unsigned freq);
//�˿ڶ�
extern unsigned char _cdecl  LUNA_PortIN(unsigned short ptid);
//�˿�д
extern void			 _cdecl  LUNA_PortOUT(unsigned short ptid, unsigned char val);
//��������Ӳ���ж�
extern void			 _cdecl  LUNA_ENABLE();
//�ر�����Ӳ���ж�
extern void			 _cdecl  LUNA_DISABLE();
//�����ж�����
extern void			 _cdecl  LUNA_set_INTvect(int intid, void (_cdecl far &v)());
//�ж������ص��¼�����������
extern void					 (_cdecl far * _cdecl getvect (int intid)) ();
//��ȡCPU����
extern const char*	 _cdecl  LUNA_CPU_VENDER();
//������
extern int			 _cdecl  LUNA_DBG_TICKCOUNT();

#endif
