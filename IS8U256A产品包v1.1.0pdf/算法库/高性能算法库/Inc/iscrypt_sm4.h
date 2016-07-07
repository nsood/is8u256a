/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_sm4.h
* Author:		PeiChao
* Version:		1.0.0.131112
* Date:			2013.11.12
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. SM4Crypt
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_SM4_H__
#define __IS_SM4_H__

#include "iscrypt_symmetric.h"


/* External Function Definition */
unsigned char SM4Crypt(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);

#endif
