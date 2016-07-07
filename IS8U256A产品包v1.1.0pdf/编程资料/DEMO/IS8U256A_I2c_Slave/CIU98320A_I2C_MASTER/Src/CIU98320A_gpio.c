/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*文件名称：CIU98320A_gpio.c
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

/***************************************************\
*函数名称：GpioInit
*函数功能：完成GPIO初始化
*输入参数：无
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void GpioInit(void)
{
	UINT32 regtmp=0x0;

	regtmp = u32READ(SYS_CLK_EN);
	regtmp |= (1<<19);
	u32WRITE(SYS_CLK_EN,regtmp);
}

/***************************************************\
*函数名称：SetGpioXOut
*函数功能：设置相应的GPIO引脚为输出
*输入参数：UINT32 GPIOX
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void SetGpioXOut(UINT32 GPIOX)
{
	UINT32 regtmp=0x0;

	regtmp = u32READ(GPIO_DIR);
	regtmp |= GPIOX;
	u32WRITE(GPIO_DIR,regtmp);

}

/***************************************************\
*函数名称：SetGpioXIn
*函数功能：设置相应的GPIO引脚为输入
*输入参数：UINT32 GPIOX
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void SetGpioXIn(UINT32 GPIOX)
{
	UINT32 regtmp=0x0;

	regtmp = u32READ(GPIO_DIR);
	regtmp &= ~GPIOX;
	u32WRITE(GPIO_DIR,regtmp);
}

/***************************************************\
*函数名称：SetGpioXHigh
*函数功能：设置相应的GPIO引脚为高电平
*输入参数：UINT32 GPIOX
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void SetGpioXHigh(UINT32 GPIOX)
{
	UINT32 regtmp=0x0;

	regtmp = u32READ(GPIO_DATA);
	regtmp |= GPIOX;
	u32WRITE(GPIO_DATA,regtmp);
}

/***************************************************\
*函数名称：SetGpioXLow
*函数功能：设置相应的GPIO引脚为低电平
*输入参数：UINT32 GPIOX
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void SetGpioXLow(UINT32 GPIOX)
{
	UINT32 regtmp=0x0;

	regtmp = u32READ(GPIO_DATA);
	regtmp &= ~GPIOX;
	u32WRITE(GPIO_DATA,regtmp);
}
