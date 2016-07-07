/*********************************************************************
* 		Copyright(C)2012北京华大信安科技有限公司
* 			All Rights Reserved	 
*
* 文件名称：	IS8U256A_I2CSlave.c
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
#include "..\inc\IS8U256A_I2CSlave.h"

/*Private typedef---------------------------------------------------*/
/*Private define----------------------------------------------------*/
/*Private macro-----------------------------------------------------*/
/*I2C-SLAVE设备的地址：0xAA*/
/*注意：该地址根据具体应用而不同*/
#define I2C_SLAVE_ADDRESS		0xAA

/*Private variables-------------------------------------------------*/
/*Private function prototypes---------------------------------------*/
/*Private functions-------------------------------------------------*/

/********************************************************************
 * Function Name	:I2CSlaveInit
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void I2CSlaveInit(void)
{
	/*使能I2C模块*/
	PCON2 |= 0x08; 

	/*使能GPIO模块*/
	PCON1 |= 0x08;

	/*GPIO13/14复用为I2C接口*/
	COMCON |= 0x80;

	/*选择I2C接口寄存器组*/
	COMSEL |= 0x03;

	/*配置I2C-Slave模式地址*/
	I2CADDR = I2C_SLAVE_ADDRESS&0xFE;
}

/********************************************************************
 * Function Name	:I2CSlavePrepareToTransmit
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
Direction_TypeDef I2CSlavePrepareToTransmit(void)
{
	while(1)
	{
		/*发送准备就绪信号*/
		I2CSlaveRDYSet();

		/*清除准备就绪信号*/
		I2CSlaveRDYClr();

		/*等待总线上I2C-Master设备发起Start/ReStart信号*/
		while(0x0==(0x20&I2CSTATUS));

		/*等待控制字节传输完成*/
		while(0x0==(0x80&I2CSTATUS));

		/*判断地址是否匹配*/
		if(0x0==(0x40&I2CSTATUS))
			continue;

		/*判断后续数据的传输方向*/
		if(0x0==(0x04&I2CSTATUS))
			return SLAVE_INPUT;
		else
			return SLAVE_OUTPUT;
	}

}

/********************************************************************
 * Function Name	:I2CSlaveSendByte
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void I2CSlaveSendByte(unsigned char ch)
{
	/*判断ACK信号*/
	if(0x0==(0x01&I2CSTATUS))
	{
		/*待发送数据写入寄存器*/
		I2CTDR = ch;
	
		/*设置可传输数据标志*/
		I2CCON &= 0xF7;

		/*清除传输完成标志*/
		I2CCON |= 0x01;

		/*发送准备就绪信号*/
		I2CSlaveRDYSet();

		/*清除准备就绪信号*/
		I2CSlaveRDYClr();

		/*等待传输完成*/
		while(0x0==(0x80&I2CSTATUS));
	}
}

/********************************************************************
 * Function Name	:I2CSlaveReceByte
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
unsigned char I2CSlaveReceByte(void)
{
	/*设置可传输数据标志*/
	I2CCON &= 0xF7;

	/*清除传输完成标志*/
	I2CCON |= 0x01;

	/*发送准备就绪信号*/
	I2CSlaveRDYSet();

	/*清除准备就绪信号*/
	I2CSlaveRDYClr();

	/*等待传输完成*/
	while(0x0==(0x80&I2CSTATUS));
	
	/*读取传输的数据*/
	return I2CRDR;
}

/********************************************************************
 * Function Name	:I2CSlaveRDYSet
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void I2CSlaveRDYSet(void)
{
	/*************************
	 *
	 *增加用户自己的标志处理代码
	 *
	 * ***********************/
	GPIOSet(GPIO_PIN_20);
	
}

/********************************************************************
 * Function Name	:I2CSlaveRDYClr
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void I2CSlaveRDYClr(void)
{
	/*************************
	 *
	 *增加用户自己的标志处理代码
	 *
	 * ***********************/
	GPIOReset(GPIO_PIN_20);

}
/************************end of file*********************************/
