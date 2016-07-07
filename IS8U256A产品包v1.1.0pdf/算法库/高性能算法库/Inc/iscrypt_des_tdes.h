/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_des_tdes.h
* Author:		PeiChao
* Version:		1.0.0.131112
* Date:			2013.11.12
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. DESCrypt
*   			2. TDESCrypt
*
* History:		
*   1. Date:			2013.08.12
*	   Version:			2.0.2.0
*      Author:			LiuJingjing			
*      Modification:	Delete some Macro definitions
*   2. ......
\****************************************************************/
#ifndef	__IS_DES_TDES_H__
#define __IS_DES_TDES_H__

#include "iscrypt_symmetric.h"

/* External Function Definition */
unsigned char DESCrypt(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);

unsigned char TDESCrypt(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);

#endif
