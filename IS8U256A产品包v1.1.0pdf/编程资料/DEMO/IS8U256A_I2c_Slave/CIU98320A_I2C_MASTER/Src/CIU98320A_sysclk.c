/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*文件名称：CIU98320A_sysclk.c
*作    者：李宪法
*版    本：V1.0.0
*日    期：2012.09.14
*功能描述：
*函数列表：
*			1、
*			2、
*			3、
*历史记录：
*	1、 日期：
*		版本：
*		作者：
*	修改内容：
*	2、.....
\***************************************************/
#include "CIU98320A.h"
#include "CIU98320A_typesmacro.h"
#include "CIU98320A_sysclk.h"

void SysClkInit(SysClkInitType *SysClkInit)
{
	UINT32 regtmp=0x0;
	regtmp = u32READ(SYS_CLK_CFG);
	regtmp &= 0xFFFF0F00;
	regtmp |= SysClkInit->SysClkSrc | SysClkInit->SysClkDiv | 
			  SysClkInit->APBClkDiv ;
	u32WRITE(SYS_CLK_CFG,regtmp);
	regtmp = 0x0;

	regtmp = u32READ(SYS_CLK_PLLEN);
	regtmp &= 0x00;
	regtmp |= SysClkInit->PLLEnable;

	if(regtmp&0x01)
	{
		regtmp |= SysClkInit->PLLValue;
	}
	else
	{
		regtmp |= 0x40;
	}

	u32WRITE(SYS_CLK_PLLEN,regtmp);
}
