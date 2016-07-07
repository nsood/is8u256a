/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*文件名称：CIU98320A_main.c
*作    者：李宪法
*版    本：V1.0.0
*日    期：2012.09.14
*功能描述：
*			1、main函数
*			2、完成SPI初始化配置，
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
#include <string.h>
#include "CIU98320A.h"
#include "CIU98320A_typesmacro.h"
#include "CIU98320A_sysclk.h"
#include "CIU98320A_i2c_master.h"
#include "CIU98320A_gpio.h"

#define BUFF_LENGTH				64
#define PAGE_LENGTH				64
#define CONTROL_BYTE_WRITE		0xAA
#define CONTROL_BYTE_READ		0xAB

unsigned char TxBuff_For_Test[BUFF_LENGTH]={0x0};
unsigned char RxBuff_For_Test[BUFF_LENGTH]={0x0};

void SysClkConfiguration(void)
{
	SysClkInitType SysClkInitStruct;
	
	SysClkInitStruct.SysClkSrc = SYSCLKOSC32M;
	SysClkInitStruct.SysClkDiv = SYSCLKDIV1;
	SysClkInitStruct.APBClkDiv = APBCLKDIV1;
	
	SysClkInitStruct.PLLEnable = PLLENABLE;
	SysClkInitStruct.PLLValue = PLLVALUE4;
	
	SysClkInit((SysClkInitType *)&SysClkInitStruct);
}

int main(void)
{
	UINT8 bytelen=0x0,i=0x0;

	SysClkConfiguration();

	GpioInit();				 

	SetGpioXIn(GPIO22);

	I2CCtrlInit(0xff,0xff);	

	while(1)
	{
		/*发送控制字节*/
		I2CGenerateStart(CONTROL_BYTE_WRITE);

		memset(TxBuff_For_Test,0xAA,sizeof TxBuff_For_Test);

		i=0x0;
		bytelen = 64;
		/*写数据*/
		while(bytelen)
		{
			I2CSendByte(TxBuff_For_Test[i]);

			i++;

			bytelen--;
		}

		/*Stop*/
		I2CGenerateStop();

		I2CGenerateStart(CONTROL_BYTE_READ);

		memset(RxBuff_For_Test,0x0,sizeof RxBuff_For_Test);
		i=0x0;
		bytelen = 63;
		while(bytelen)
		{
			RxBuff_For_Test[i] = I2CReceByteWithACK();

			i++;

			bytelen--;
		}

		RxBuff_For_Test[i] = I2CReceByteWithNAK();

		I2CGenerateStop();

		for(i=0;i<64;i++)
			if(0xBB!=RxBuff_For_Test[i])
				goto Error;
	}

Error:
	while(1);
}
