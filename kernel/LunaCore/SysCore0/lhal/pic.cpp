#include <lhal.h>
#include "pic.h"

//! ÖÐ¶Ï´¦ÀíÆ÷1ºÅ¶Ë¿Ú
#define I86_PIC1_REG_COMMAND	0x20
#define I86_PIC1_REG_STATUS		0x20
#define I86_PIC1_REG_DATA		0x21
#define I86_PIC1_REG_IMR		0x21

//! ÖÐ¶Ï´¦ÀíÆ÷2ºÅ¶Ë¿Ú
#define I86_PIC2_REG_COMMAND	0xA0
#define I86_PIC2_REG_STATUS		0xA0
#define I86_PIC2_REG_DATA		0xA1
#define I86_PIC2_REG_IMR		0xA1

//¿ØÖÆÃüÁîÑÚÂë
#define I86_PIC_ICW1_MASK_IC4			0x1			//00000001
#define I86_PIC_ICW1_MASK_SNGL			0x2			//00000010
#define I86_PIC_ICW1_MASK_ADI			0x4			//00000100
#define I86_PIC_ICW1_MASK_LTIM			0x8			//00001000
#define I86_PIC_ICW1_MASK_INIT			0x10		//00010000
#define I86_PIC_ICW4_MASK_UPM			0x1			//00000001
#define I86_PIC_ICW4_MASK_AEOI			0x2			//00000010
#define I86_PIC_ICW4_MASK_MS			0x4			//00000100
#define I86_PIC_ICW4_MASK_BUF			0x8			//00001000
#define I86_PIC_ICW4_MASK_SFNM			0x10		//00010000

//-----------------------------------------------
//	Ò»ºÅÃüÁî¿ØÖÆ×Ö½Ú
//-----------------------------------------------

#define I86_PIC_ICW1_IC4_EXPECT				1			//1
#define I86_PIC_ICW1_IC4_NO					0			//0
#define I86_PIC_ICW1_SNGL_YES				2			//10
#define I86_PIC_ICW1_SNGL_NO				0			//00
#define I86_PIC_ICW1_ADI_CALLINTERVAL4		4			//100
#define I86_PIC_ICW1_ADI_CALLINTERVAL8		0			//000
#define I86_PIC_ICW1_LTIM_LEVELTRIGGERED	8			//1000
#define I86_PIC_ICW1_LTIM_EDGETRIGGERED		0			//0000
#define I86_PIC_ICW1_INIT_YES				0x10		//10000
#define I86_PIC_ICW1_INIT_NO				0			//00000

//-----------------------------------------------
//	ËÄºÅÃüÁî¿ØÖÆ×Ö½Ú
//-----------------------------------------------

#define I86_PIC_ICW4_UPM_86MODE			1			//1
#define I86_PIC_ICW4_UPM_MCSMODE		0			//0
#define I86_PIC_ICW4_AEOI_AUTOEOI		2			//10
#define I86_PIC_ICW4_AEOI_NOAUTOEOI		0			//0
#define I86_PIC_ICW4_MS_BUFFERMASTER	4			//100
#define I86_PIC_ICW4_MS_BUFFERSLAVE		0			//0
#define I86_PIC_ICW4_BUF_MODEYES		8			//1000
#define I86_PIC_ICW4_BUF_MODENO			0			//0
#define I86_PIC_ICW4_SFNM_NESTEDMODE	0x10		//10000
#define I86_PIC_ICW4_SFNM_NOTNESTED		0			//a binary 2 (futurama joke hehe ;)

inline void LUNA_INER_I86_PIC_SCOMMAND(uint8_t cmd, uint8_t picID)
{
	if (picID > 1)
		return;
	uint8_t reg = (picID == 1) ? I86_PIC2_REG_COMMAND : I86_PIC1_REG_COMMAND;
	LUNA_PortOUT(reg, cmd);
}

inline void LUNA_INER_I86_PIC_SDATA(uint8_t dat, uint8_t picID)
{
	if (picID > 1)
		return;
	uint8_t reg = (picID == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;
	LUNA_PortOUT(reg, dat);
}

inline uint8_t LUNA_INER_I86_PIC_RDATA(uint8_t picID)
{
	if (picID > 1)
		return 0;
	uint8_t reg = (picID == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;
	return LUNA_PortIN(reg);
}

void LUNA_INER_I86_PIC_INITIALIZE(uint8_t b0, uint8_t b1)
{
	uint8_t icw = 0;
	LUNA_DISABLE();
	icw = (icw & ~I86_PIC_ICW1_MASK_INIT) | I86_PIC_ICW1_INIT_YES;
	icw = (icw & ~I86_PIC_ICW1_MASK_IC4) | I86_PIC_ICW1_IC4_EXPECT;

	LUNA_INER_I86_PIC_SCOMMAND(icw, 0);
	LUNA_INER_I86_PIC_SCOMMAND(icw, 1);

	LUNA_INER_I86_PIC_SDATA(b0, 0);
	LUNA_INER_I86_PIC_SDATA(b1, 1);

	LUNA_INER_I86_PIC_SDATA(0x04, 0);
	LUNA_INER_I86_PIC_SDATA(0x02, 1);

	icw = (icw & ~I86_PIC_ICW4_MASK_UPM) | I86_PIC_ICW4_UPM_86MODE;

	LUNA_INER_I86_PIC_SDATA(icw, 0);
	LUNA_INER_I86_PIC_SDATA(icw, 1);
}