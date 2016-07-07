/*********************************************************************
* 		Copyright(C)2012北京华大信安科技有限公司
* 			All Rights Reserved	 
*
* 文件名称：	EEPROM_24LC128.c
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
#include <string.h>
#include "CIU98320A_i2c_master.h"

/*Private typedef---------------------------------------------------*/
/*Private define----------------------------------------------------*/
/*Private macro-----------------------------------------------------*/
#define I2C_CONTROL_READ		0xA1
#define I2C_CONTROL_WRITE		0xA0

/*Private variables-------------------------------------------------*/
unsigned char I2CBuff[3]={0x0};
unsigned char *pI2CBuff=(void *)0;

/*Private function prototypes---------------------------------------*/
/*Private functions-------------------------------------------------*/

/********************************************************************
 * Function Name	:EEPROM_ByteWrite
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void EEPROM_ByteWrite(unsigned int address,unsigned char ch)
{
	unsigned char lentmp=0x02,i=0x0;

	I2CBuff[0] = (unsigned char)((address>>8)&0xFF);
	I2CBuff[1] = (unsigned char)((address>>0)&0xFF);
	I2CBuff[2] = ch;

	I2CGenerateStart(I2C_CONTROL_WRITE);

	while(lentmp)
	{
		I2CSendByte(I2CBuff[i]);

		lentmp--;

		i++;
	}

	I2CSendByte(ch);

	I2CGenerateStop();
}

/********************************************************************
 * Function Name	:EEPROM_PageWrite
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void EEPROM_PageWrite(
						unsigned int address,\
						unsigned char * const pbuff)
{
	unsigned char lentmp=0,i=0x0;

	I2CBuff[0] = (unsigned char)((address>>8)&0xFF);
	I2CBuff[1] = (unsigned char)((address>>0)&0xFF);

	I2CGenerateStart(I2C_CONTROL_WRITE);

	lentmp = 0x02;
	while(lentmp)
	{
		I2CSendByte(I2CBuff[i]);

		lentmp--;

		i++;
	}

	lentmp = 64;
	i=0x0;
	while(lentmp)
	{
		I2CSendByte(*(pbuff+i));

		lentmp--;

		i++;
	}

	I2CGenerateStop();
}

/********************************************************************
 * Function Name	:EEPROM_ByteRead
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
unsigned char EEPROM_ByteRead(unsigned int address)
{
	unsigned char datatmp;
	unsigned char lentmp=0x02,i=0x0;

	I2CBuff[0] = (unsigned char)((address>>8)&0xFF);
	I2CBuff[1] = (unsigned char)((address>>0)&0xFF);

	I2CGenerateStart(I2C_CONTROL_WRITE);

	while(lentmp)
	{
		I2CSendByte(I2CBuff[i]);

		lentmp--;

		i++;
	}

	I2CGenerateReStart(I2C_CONTROL_READ);

	datatmp = I2CReceByteWithNAK();

	I2CGenerateStop();

	return datatmp;
}

/********************************************************************
 * Function Name	:EEPROM_DataRead
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void EEPROM_DataRead(
						unsigned int address,			  \
						unsigned char *const pRxBuff,\
						unsigned int bytelen)
{
	unsigned char lentmp,i=0x0;

	I2CBuff[0] = (unsigned char)((address>>8)&0xFF);
	I2CBuff[1] = (unsigned char)((address>>0)&0xFF);

	I2CGenerateStart(I2C_CONTROL_WRITE);

	lentmp=0x02;
	while(lentmp)
	{
		I2CSendByte(I2CBuff[i]);

		lentmp--;

		i++;
	}

	i=0x0;
	I2CGenerateReStart(I2C_CONTROL_READ);

	while(bytelen>1)
	{
		*(pRxBuff+i) = I2CReceByteWithACK();

		bytelen--;

		i++;
	}

	*(pRxBuff+i) = I2CReceByteWithNAK();

	I2CGenerateStop();

}
/************************end of file*********************************/
