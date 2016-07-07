/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_sm1_sec.h
* Author:			PeiChao
* Version:			1.0.0.0
* Date:				2014.3.24
* Description:
* 	
* Others:		
* 
* Function List:
*				1.	SM1CryptSCA
*				2.	SM1CryptSEC
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_ISCRYPT_SM1_SEC_H__
#define __IS_ISCRYPT_SM1_SEC_H__

#include "iscrypt.h"
#include "iscrypt_symmetric.h"

#ifndef D_LOW_LEVEL_S

#define D_LOW_LEVEL_S		0
#define D_MEDIUM_LEVEL_S	2
#define D_HIGH_LEVEL_S		4

#endif


/* External Function Definition */
unsigned char SM1CryptSCA(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);

unsigned char SM1CryptSEC(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);


#endif
