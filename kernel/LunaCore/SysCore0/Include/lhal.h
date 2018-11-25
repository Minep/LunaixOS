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

//中断调用完成事件 (intid 中断编号)
extern void			 _cdecl  LUNA_interruptdone(unsigned int intid);
//扬声器发声 (freq 频率)
extern void			 _cdecl  LUNA_mksound(unsigned freq);
//端口读
extern unsigned char _cdecl  LUNA_PortIN(unsigned short ptid);
//端口写
extern void			 _cdecl  LUNA_PortOUT(unsigned short ptid, unsigned char val);
//开启所有硬件中断
extern void			 _cdecl  LUNA_ENABLE();
//关闭所有硬件中断
extern void			 _cdecl  LUNA_DISABLE();
//设置中断向量
extern void			 _cdecl  LUNA_set_INTvect(int intid, void (_cdecl far &v)());
//中断向量回调事件，返回向量
extern void					 (_cdecl far * _cdecl getvect (int intid)) ();
//获取CPU厂家
extern const char*	 _cdecl  LUNA_CPU_VENDER();
//测试用
extern int			 _cdecl  LUNA_DBG_TICKCOUNT();

#endif
