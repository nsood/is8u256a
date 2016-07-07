/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_des_tdes_sec.h
* Author:			PeiChao
* Version:			1.0.0.0
* Date:				2013.12.27
* Description:
* 	
* Others:		
* 
* Function List:
*				1.	DESCryptSCA
*				2.	TDESCryptSCA
*				3.	DESCryptSEC
*				4.	TDESCryptSEC
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_ISCRYPT_DES_SEC_H__
#define __IS_ISCRYPT_DES_SEC_H__

#include "iscrypt.h"
#include "iscrypt_symmetric.h"

#define D_LOW_LEVEL_S		0
#define D_MEDIUM_LEVEL_S	2
#define D_HIGH_LEVEL_S		4

/* External Function Definition */
unsigned char DESCryptSCA(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);

unsigned char TDESCryptSCA(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);

unsigned char DESCryptSEC(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);

unsigned char TDESCryptSEC(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);

#endif
