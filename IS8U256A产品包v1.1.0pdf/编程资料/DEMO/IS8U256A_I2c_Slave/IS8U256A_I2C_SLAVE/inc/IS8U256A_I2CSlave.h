/*********************************************************************
* 		Copyright(C)2012北京华大信安科技有限公司
* 			All Rights Reserved	 
*
* 文件名称：	IS8U256A_I2CSlave.h
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
#ifndef __IS8U256A_I2CSLAVE_H__
#define __IS8U256A_I2CSLAVE_H__

/*Includes----------------------------------------------------------*/
/*Exported typedef--------------------------------------------------*/
typedef enum{SLAVE_INPUT=0,SLAVE_OUTPUT = !SLAVE_INPUT}Direction_TypeDef;
/*Exported define---------------------------------------------------*/
#ifndef I2CSLAVE_EXTERN
#define I2CSLAVE_EXTERN			extern
#endif

I2CSLAVE_EXTERN void I2CSlaveInit(void);
I2CSLAVE_EXTERN void I2CSlaveSendByte(unsigned char ch);
I2CSLAVE_EXTERN unsigned char I2CSlaveReceByte();
I2CSLAVE_EXTERN unsigned char I2CSlavePrepareToTransmit(void);
I2CSLAVE_EXTERN void I2CSlaveRDYSet(void);
I2CSLAVE_EXTERN void I2CSlaveRDYClr(void);

/*Exported macro----------------------------------------------------*/
/*Exported functions------------------------------------------------*/

#endif

/************************end of file*********************************/


