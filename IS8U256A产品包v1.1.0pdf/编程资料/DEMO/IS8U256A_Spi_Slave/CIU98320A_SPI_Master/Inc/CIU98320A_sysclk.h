/************************************************************/
/*				Copy Right (C) HED.Inc						*/
/*				All Right Reserved							*/
/*文件名称：CIU96S320A_sysclk.h								*/
/*作    者：												*/
/*当前版本：V1.0.0											*/
/*日    期：2012-08-26										*/
/*功能描述：	   											*/
/*		                                                    */
/*修改内容：初版做成										*/
/************************************************************/
#ifndef __CIU98320A_SYSCLK_H__
#define __CIU98320A_SYSCLK_H__

typedef struct SysClk
{
	UINT32 SysClkSrc;
	UINT32 SysClkDiv;
	UINT32 APBClkDiv;

	UINT32 PLLEnable;
	UINT32 PLLValue;
} SysClkInitType;

#ifndef __SYSCLK__

#define SYSCLKOSC32M			0x00000000
#define SYSCLKPLL48M			0x00000001
#define SYSCLKEXT7816CLK		0x00000003

#define SYSCLKDIV1				0x00000000
#define SYSCLKDIV2				0x00000010
#define SYSCLKDIV4				0x00000020
#define SYSCLKDIV8				0x00000030

#define APBCLKDIV1				0x00000000
#define APBCLKDIV2				0x00001000

#define RSACLKOSC32M			0x00000000
#define RSACLKPLLOUT			0x10000000

#define PLLENABLE				0x00000001
#define PLLDISABLE				0x00

#define PLLVALUE2				0x20
#define PLLVALUE3				0x30
#define PLLVALUE4				0x40

#endif

#ifndef SYSCLK_EXT
#define SYSCLK_EXT  extern
#else
#define SYSCLK_EXT
#endif

SYSCLK_EXT void SysClkInit(SysClkInitType *SysClkInit);

#endif
