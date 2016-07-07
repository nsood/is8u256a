/*********************************************************************
* 		Copyright(C)2012北京华大信安科技有限公司
* 			All Rights Reserved	 
*
* 文件名称：	IS8U256A_SPISlave.c
* 作    者：	李宪法
* 版    本：	V1.0.0
* 日	期：	2013-11
* 功能描述：	
* 功能列表：	
*
* 历史记录：
* 1.  日期：	
*	  版本：
*	  作者：
* 修改内容：
*
*********************************************************************/

/*Includes----------------------------------------------------------*/
#include "..\inc\IS8U256X.h"
#include "..\inc\IS8U256A_GPIO.h"

/*Private typedef---------------------------------------------------*/
/*Private define----------------------------------------------------*/
	/***********************************************
	 *根据具体情况，加载具体的指示信号
	 * **********************************************/
#define	TRANSMIT_RDY_FLAG		GPIO_PIN_20
#define TransmitRdySet()		GPIOSet(TRANSMIT_RDY_FLAG)
#define TransmitRdyReset()		GPIOReset(TRANSMIT_RDY_FLAG)

/*Private macro-----------------------------------------------------*/
/*Private variables-------------------------------------------------*/
/*Private function prototypes---------------------------------------*/
/*Private functions-------------------------------------------------*/

/********************************************************************
 * Function Name	:SpiSlaveInit
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void SpiSlaveInit(void)
{
	/*使能SPI模块*/
	PCON1 |= 0x10;

	/*GP7/8/9/10复用为SPI引脚*/
	COMCON |= 0x02;

	/*选择SPI寄存器组*/
	COMSEL = 0x0;

	/*SPI模式：单线模式*/
	SPIMODE &= 0xFC; 

	SPIMODE &= 0xDF;

	/*SPI模式：从模式*/
	SPICFG &= 0xFE;

	/*传输数据宽度为：8bit*/
	SPICFG |= 0x70;

	/*传输数据顺序为：MSB*/
	SPICFG |= 0x08;

	/*使能发送接收功能*/
	SPICON |= 0xC0;

	/*使能SPI控制器*/
	SPICON |= 0x01;
}

/********************************************************************
 * Function Name	:SpiTransmitData
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void SpiTransmitData(
			unsigned char xdata * ptxbuff,	\
			unsigned char xdata * prxbuff,	\
			unsigned char bytelen			\
			)
{
	unsigned char xdata regtmp;
	unsigned char xdata*ptxtmp=ptxbuff;
	unsigned char xdata*prxtmp=prxbuff;
	
	while(bytelen)
	{
		if((void *)0!=ptxbuff)
		{
			/*写入传送数据*/
			SPIDATA = *(ptxtmp++);
		}
		else
		{
			SPIDATA = 0x0;
		}

		/*设置RDY标志:低有效*/
		TransmitRdySet();

		/*清除RDY标志*/
		TransmitRdyReset();

		/*等待传送完成*/
		while(0x0==(0x04&SPISTATUS));

		regtmp = SPIDATA;

		if((void *)0!=prxbuff)
		{
			/*读回传送结果*/
			*(prxtmp++) = regtmp;
		}

		bytelen--;

	}

}

/***************************End of File*******************************/

