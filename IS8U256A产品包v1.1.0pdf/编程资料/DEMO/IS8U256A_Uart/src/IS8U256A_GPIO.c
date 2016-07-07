/*********************************************************************
* 		Copyright(C)2012北京华大信安科技有限公司
* 			All Rights Reserved	 
*
* 文件名称：	IS8U256A_GPIO.c
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
/*Private macro-----------------------------------------------------*/
/*Private variables-------------------------------------------------*/
/*Private function prototypes---------------------------------------*/
/*Private functions-------------------------------------------------*/

/********************************************************************
 * Function Name	:GPIOInit
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void GPIOInit(void)
{
	/*使能GPIO模块*/
	PCON1 |= 0x08;

	/*GPIO20--GPIO1全部选择GPIO通信*/
	COMCON = 0x0;

	/*配置GPIO8--GPIO1为上拉模式*/
	GPIOPR = 0xFF;

	/*配置GPIO16--GPIO9为上拉模式*/
	GPIOPR1 = 0xFF;

	/*配置GPIO20--GPIO17为上拉模式*/
	GPIOPR2 = 0xF5;
}

/*********************************************************************
 * Function Name	:GPIOSetInput
 * Description		:
 * Argument		:
 * Return		:
**********************************************************************/
void GPIOSetInput(unsigned long const gpx)
{
	unsigned long index=~gpx;

	/*遍历GPIO8--GPIO0是否有需设为输入模式*/
	GPIOCTRL &= (unsigned char)((index>>0)&0xFF);

	/*遍历GPIO16--GPIO9是否有需设为输入模式*/
	GPIOCTRL1 &= (unsigned char)((index>>8)&0xFF);

	/*遍历GPIO20--GPIO17是否有需设为输入模式*/
	GPIOCTRL2 &= (unsigned char)((index>>16)&0xFF);
}

/*********************************************************************
 * Function Name	:GPIOSetOutput
 * Description		:
 * Argument		:
 * Return		:
**********************************************************************/
void GPIOSetOutput(unsigned long const gpx)
{
	unsigned long index=gpx;

	/*遍历GPIO8--GPIO0是否有需设为输入模式*/
	GPIOCTRL |= (unsigned char)((index>>0)&0xFF);

	/*遍历GPIO16--GPIO9是否有需设为输入模式*/
	GPIOCTRL1 |= (unsigned char)((index>>8)&0xFF);

	/*遍历GPIO20--GPIO17是否有需设为输入模式*/
	GPIOCTRL2 |= (unsigned char)((index>>16)&0xFF);
}

/*********************************************************************
 * Function Name	:GPIOReset
 * Description		:
 * Argument		:
 * Return		:
**********************************************************************/
void GPIOReset(unsigned long const gpx)
{
	unsigned long index=~gpx;

	/*遍历GPIO8--GPIO0是否有需复位管脚*/
	GPIODATA &= (unsigned char)((index>>0)&0xFF);

	/*遍历GPIO16--GPIO9是否有需复位管脚*/
	GPIODATA1 &= (unsigned char)((index>>8)&0xFF);

	/*遍历GPIO20--GPIO17是否有需复位管脚*/
	GPIODATA2 &= (unsigned char)((index>>16)&0xFF);
}

/*********************************************************************
 * Function Name	:GPIOSet
 * Description		:
 * Argument		:
 * Return		:
**********************************************************************/
void GPIOSet(unsigned long const gpx)
{
	unsigned long index=gpx;

	/*遍历GPIO8--GPIO0是否有需置位管脚*/
	GPIODATA |= (unsigned char)((index>>0)&0xFF);

	/*遍历GPIO16--GPIO9是否有需置位管脚*/
	GPIODATA1 |= (unsigned char)((index>>8)&0xFF);

	/*遍历GPIO20--GPIO17是否有需置位管脚*/
	GPIODATA2 |= (unsigned char)((index>>16)&0xFF);
}

/***************************End of File*******************************/
