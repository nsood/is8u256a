/*********************************************************************
* 		Copyright(C)2012北京华大信安科技有限公司
* 			All Rights Reserved	 
*
* 文件名称：	IS8U256A_SpiSlave.h
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
#ifndef __IS8U256A_SPISLAVE_H__
#define __IS8U256A_SPISLAVE_H_

/*Includes----------------------------------------------------------*/
/*Exported typedef--------------------------------------------------*/
/*Exported define---------------------------------------------------*/
#ifndef SPISLAVE_EXTERN
#define SPISLAVE_EXTERN			extern
#endif

SPISLAVE_EXTERN void SpiSlaveInit(void);

SPISLAVE_EXTERN void SpiTransmitData(
					unsigned char xdata *ptxbuff,\
					unsigned char xdata *prxbuff,\
					unsigned char bytelen);

/*Exported macro----------------------------------------------------*/
/*Exported functions------------------------------------------------*/

#endif

/************************end of file*********************************/


