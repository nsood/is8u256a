/*********************************************************************
* 		Copyright(C)2012北京华大信安科技有限公司
* 			All Rights Reserved	 
*
* 文件名称：	EEPROM_24LC128.h
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

/* Define to prevent recursive inclusion ---------------------------*/
#ifndef __EEPROM_24LC128_H__
#define __EEPROM_24LC128_H__

/*Includes----------------------------------------------------------*/
/*Exported typedef--------------------------------------------------*/
/*Exported define---------------------------------------------------*/
#ifndef EEPROM_EXTERN
#define EEPROM_EXTERN			extern
#endif

/*Exported macro----------------------------------------------------*/
/*Exported functions------------------------------------------------*/
EEPROM_EXTERN unsigned char EEPROM_ByteRead(unsigned int address);
EEPROM_EXTERN void EEPROM_ByteWrite(
										unsigned int address,\
										unsigned char ch);
EEPROM_EXTERN void EEPROM_PageWrite(
										unsigned int address,\
										unsigned char *const pbuff);

EEPROM_EXTERN void EEPROM_DataRead(
										unsigned int address,			  \
										unsigned char *const pRxBuff,\
										unsigned int bytelen);

#endif

/************************end of file*********************************/

