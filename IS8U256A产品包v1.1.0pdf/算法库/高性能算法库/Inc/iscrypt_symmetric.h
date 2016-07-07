/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_symmetric.h
* Author:		PeiChao
* Version:		1.0.0.131112
* Date:			2013.11.12
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. 
*   			2. 
*   			3. 
*   			4. 
*
*   1. Date:			
*	   Version:			
*      Author:						
*      Modification:	
*   2. ......
\****************************************************************/
#ifndef	__IS_SYMMETRIC_H__
#define __IS_SYMMETRIC_H__

#include "iscrypt.h"

typedef struct Struct_BLOCKCIPHERPARAM
{
	/* The operation's type of current 
	   block cipher algorithm */
	unsigned char bOpMode;						//	in
	/* Key used to operate */
	unsigned char xdata *pbKey;					//	in
	/* Needed when use CBC/OFB/CFB */
	unsigned char xdata *pbIV;					//	in

	/* Input */
	unsigned char xdata *pbInput;				//	in
	/* The total number of block */
	unsigned char bTotalBlock;					//	in
	/* Output */
	unsigned char xdata *pbOutput;				//	out

	/* Reserve for future, may be used */
	unsigned char xdata *pbReserve;				//	unused

}BLOCKCIPHERPARAM, *PBLOCKCIPHERPARAM;


/* CHOICE OF THE ALGORITHM TYPE */
#define SYM_ECB				0x00
#define SYM_CBC				0x01
#define SYM_CFB				0x02
#define SYM_OFB				0x03
#define SYM_MAC				0x04
#define SYM_CTR				0x05

#define SYM_ENCRYPT			0x00
#define SYM_DECRYPT			0x08

#define SYM_AES128			0x10
#define SYM_AES192			0x20
#define SYM_AES256			0x40


/* THE BLOCK SIZE OF EVERY BLOCK CIPHER ALGORITHM */
#define DES_BLOCK_SIZE		0x08
#define TDES_BLOCK_SIZE		0x08

#define SM1_BLOCK_SIZE		0x10
#define SSF33_BLOCK_SIZE	0x10
#define SM4_BLOCK_SIZE		0x10

#define AES_BLOCK_SIZE		0x10

#endif
