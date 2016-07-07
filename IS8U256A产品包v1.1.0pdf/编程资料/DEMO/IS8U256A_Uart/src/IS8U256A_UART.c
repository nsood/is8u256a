/*********************************************************************
* 		Copyright(C)2012北京华大信安科技有限公司
* 			All Rights Reserved	 
*
* 文件名称：	XA1302_UART.c
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

/*Private typedef---------------------------------------------------*/
/*Private define----------------------------------------------------*/
#define UART_CLK			48000000

/*Private macro-----------------------------------------------------*/
/*Private variables-------------------------------------------------*/
/*Private function prototypes---------------------------------------*/
/*Private functions-------------------------------------------------*/

/********************************************************************
 * Function Name	:GCD
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
static unsigned long GCD(unsigned long X1 , unsigned long X2)
{
	unsigned long max=0x0;
	unsigned long min=0x0;
	unsigned long X,Y,R;

	max = (X1>X2)?X1:X2;
	min = (X1>X2)?X2:X1;
	X = max;
	Y = min;

	while(0x0!=Y)
	{
		R = X%Y;
		X = Y;
		Y = R;
	}

	return X;
}

/********************************************************************
 * Function Name	:UARTSetBaudRate
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
static void UARTSetBaudRate(unsigned long baudrate)
{
	unsigned long gcd;
	unsigned long baud_freq,baud_limit;

	gcd = GCD(UART_CLK,16*baudrate);
	baud_freq = (16*baudrate)/gcd;
	baud_limit = (UART_CLK/gcd)-baud_freq;

	BAUD_FREQ = (unsigned char)(baud_freq&0xFF);
	BAUD_FREQ = (unsigned char)((baud_freq>>8)&0xFF);
	BAUD_LIMIT = (unsigned char)(baud_limit&0xFF);
	BAUD_LIMIT = (unsigned char)((baud_limit>>8)&0xFF);
}

/********************************************************************
 * Function Name	:UARTInit
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void UARTInit(void)
{
	/*使能PLL*/
	PLLCON |= 0x01;

	/*等待PLL稳定*/
	while(0x0==(PLLCON&0x02));

	/*使能GPIO模块*/
	PCON1 |= 0x08;

	/*GP11/12复用为UART引脚*/
	COMCON |= 0x40;

	/*使能UART模块*/
	PCON2 |= 0x04;

	/*选择UART寄存器组*/
	COMSEL = 0x01;

	/*设置波特率：115200*/
	UARTSetBaudRate(9600);

	/*设置接收停止位：1bit*/
	UARTPR &= 0x3F;

	/*设置接收数据宽度：8bit*/
	UARTPR &= 0xCF;

	/*设置发送停止位：1bit  */
	UARTPR &= 0xF3;

	/*设置发送数据宽度：8bit */
	UARTPR &= 0xFC;

	/*使能接收偶校验*/
	UARTCON |= 0x10;

	/*使能发送偶校验*/
	UARTCON |= 0x04;

	/*使能UART中断模式*/
	UARTCON |= 0x01;

	/*使能UART中断*/
	IEH |= 0x20;

	/*使能总中断*/
	IEH |= 0x80;
}
/********************************************************************
 * Function Name	:UARTSendByte
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void UARTSendByte(unsigned char ch)
{
	/*等待上次发送结束*/
	while(0x01&UARTSR);

	/*写入发送寄存器，启动本次发送*/
	TX_DATA = ch;

}

/********************************************************************
 * Function Name	:UARTHandler
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
//void UARTHandler(void) interrupt 13
//{
//	unsigned char regtmp;
//
//	/*关闭总中断*/
//	IEH &= 0x7F;	
//
//	/*处理接收中断*/
//	if(UARTSTATUS&0x02)
//	{
//		/*清除接收中断标志*/
//		UARTSTATUS &= 0xFD;
//
//		/*没有接收错误*/
//		if(!(UARTSTATUS&0x38))
//		{
//			/****************************************
//			 * 
//			 * 增加用户代码，
//			 * 建议在此保存接收的数据，判断接收是否完
//			 * 成，并置位相关标志，不对数据做具体处理
//			 *
//			*****************************************/
//		}
//		/*数据接收错误*/
//		else
//		{
//			/******************
//			 * 
//			 * 增加错误处理代码
//			 *
//			*******************/
//		}
//	}
//
//	/*处理发送中断*/
//	if(UARTSTATUS&0x04)
//	{
//		/*清除发送中断标志*/
//		UARTSTATUS &= 0xFB;
//
//		/************************************
//		 * 
//		 * 增加用户代码，
//		 * 建议在此只清除标志位，不做其他处理
//		 *
//		*************************************/
//	}
//
//	/*恢复总中断*/
//	IEH |= 0x80;
//}

/************************end of file*********************************/
