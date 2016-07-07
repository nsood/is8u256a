/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_sm2_bsc.h
* Author:		PeiChao
* Version:		1.0.0.131121
* Date:			2013.11.21
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1.	kG 
*				2.	kP 
*				3.	SetModP 
*				4.	SetModN 
*				5.	CheckPoint 
*				6.	IS_MEMCPY_FROM_XRAM_TO_XRAM
*				7.	IS_MEMRCPY_FROM_XRAM_TO_XRAM 
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_SM2_BASIC_H__
#define	__IS_SM2_BASIC_H__

/* Parameter */
extern unsigned char code SM2_ECP_N[32];

/* Function */
extern void kG();

extern void kP();

extern void SetModP();

extern void SetModN();

extern unsigned char CheckPoint();

extern void IS_MEMCPY_FROM_XRAM_TO_XRAM(
	unsigned char xdata *dest,		// in, out
	unsigned char xdata *src,		// in
	unsigned char count				// in
);

extern void IS_MEMRCPY_FROM_XRAM_TO_XRAM(
	unsigned char xdata *dest,		// in, out
	unsigned char xdata *src,		// in
	unsigned char count				// in
);

#endif
