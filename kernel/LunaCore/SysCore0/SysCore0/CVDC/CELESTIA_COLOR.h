/************** Celestia Display Core *****************
//	   >Celestia Display Core Color Constant Define<
//			 >Lunaix Operating System Kernel<
//					  >CPR Lunaixsky<
//
// CELESTIA_COLOR.h >>>>>>>>>>>>>>>>>>>>>>>>>
//		¡¤Define the constant of color used in 
//				CELE_SetColor(const unsigned c)
*******************************************************/

/*	  7 	6	 5	 4	  3    2    1	  0
 *	+----+----+----+----+----+----+----+----+
 *	|I   |R	  |	G  |B	|I	 |R	  | G  |  B |
 *	+----+----+----+----+----+----+----+----+
 *	\_____Background___/ \____Foreground____/
 *	
 *	I:Intensty
 *	RGB: Red , Green, Bule
 *
 ******Basic Formatting:
 *
 *	#define C_BULE_WHITE	+-Note----------------------------+	
 *    |		|	|	|		|*Prefix£ºC is represent Celestia |
 * C_define |	|	|		+---------------------------------+
 *		 Prefix	|	|
 *		 Background	|
 *				Foreground
*/
#ifndef CELESTIA_COLOR_CTN
#define CELESTIA_COLOR_CTN
//			NAME			VAL			i rgb	i rgb
//BLACK
#define C_BLACK_BULE		0x1			//0 000 0 001
#define C_BLACK_GREEN		0x2			//0 000 0 010
#define C_BLACK_CYAN		0x3			//0 000 0 011
#define C_BLACK_RED 		0x4			//0 000 0 100
#define C_BLACK_PINK		0x5			//0 000 0 101
#define C_BLACK_YELLOW		0x6			//0 000 0 110
#define C_BLACK_WHITE		0x7			//0 000 0 111

//BULE
#define C_BULE_BLACK		0x10		//0 001 0 000
#define C_BULE_GREEN		0x12		//0 001 0 010
#define C_BULE_CYAN			0x13		//0 001 0 011
#define C_BULE_RED 			0x14		//0 001 0 100
#define C_BULE_PINK			0x15		//0 001 0 101
#define C_BULE_YELLOW		0x16		//0 001 0 110
#define C_BULE_WHITE		0x17		//0 001 0 111

//GREEN
#define C_GREEN_BLACK		0x20		//0 010 0 000
#define C_GREEN_BULE		0x21		//0 010 0 001
#define C_GREEN_CYAN		0x23		//0 010 0 011
#define C_GREEN_RED 		0x24		//0 010 0 100
#define C_GREEN_PINK		0x25		//0 010 0 101
#define C_GREEN_YELLOW		0x26		//0 010 0 110
#define C_GREEN_WHITE		0x27		//0 010 0 111

//CYAN
#define C_CYAN_BLACK 		0x30		//0 011 0 000
#define C_CYAN_BULE			0x31		//0 011 0 001
#define C_CYAN_GREEN		0x32		//0 011 0 010
#define C_CYAN_RED			0x34		//0 011 0 100
#define C_CYAN_PINK			0x35		//0 011 0 101
#define C_CYAN_YELLOW		0x36		//0 011 0 110
#define C_CYAN_WHITE		0x37		//0 011 0 111

//RED
#define C_RED_BLACK 		0x40		//0 100 0 000
#define C_RED_BULE			0x41		//0 100 0 001
#define C_RED_GREEN			0x42		//0 100 0 010
#define C_RED_CYAN			0x43		//0 100 0 011
#define C_RED_PINK			0x45		//0 100 0 101
#define C_RED_YELLOW		0x46		//0 100 0 110
#define C_RED_WHITE			0x47		//0 100 0 111

//PINK
#define C_PINK_BLACK		0x50		//0 101 0 000
#define C_PINK_BULE			0x51		//0 101 0 001
#define C_PINK_GREEN		0x52		//0 101 0 010
#define C_PINK_CYAN			0x53		//0 101 0 011
#define C_PINK_RED 			0x54		//0 101 0 100
#define C_PINK_YELLOW		0x56		//0 101 0 110
#define C_PINK_WHITE		0x57		//0 101 0 111

//YELLOW
#define C_YELLOW_BLACK		0x60		//0 110 0 000
#define C_YELLOW_BULE		0x61		//0 110 0 001
#define C_YELLOW_GREEN		0x62		//0 110 0 010
#define C_YELLOW_CYAN		0x63		//0 110 0 011
#define C_YELLOW_RED 		0x64		//0 110 0 100
#define C_YELLOW_PINK		0x65		//0 110 0 101
#define C_YELLOW_WHITE		0x67		//0 110 0 111

//WHITE
#define C_WHITE_BLACK		0x70		//0 111 0 000
#define C_WHITE_BULE		0x71		//0 111 0 001
#define C_WHITE_GREEN		0x72		//0 111 0 010
#define C_WHITE_CYAN		0x73		//0 111 0 011
#define C_WHITE_RED 		0x74		//0 111 0 100
#define C_WHITE_PINK		0x76		//0 111 0 101
#define C_WHITE_YELLOW		0x77		//0 111 0 110

//Hightlight Zone
#define C_OPT_HIGHLIGHT_FOREGROUND 0x8	//0 000 1 000
#define C_OPT_HIGHLIGHT_BACKGROUND 0x80	//1 000 0 000
#endif
