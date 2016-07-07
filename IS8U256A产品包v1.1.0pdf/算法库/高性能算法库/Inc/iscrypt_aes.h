/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:		iscrypt_aes.h
* Author:        	PeiChao
* Version:			1.0.0.131112        
* Date:				2013.11.12
* Description:		
* 					
*
* Others:         
*					
* Function List:  
*   				1. AESCrypt
*					2. 
*
* History:
*
*   1. Date:
*      Author:
*      Modification:
*
\****************************************************************/
#ifndef __IS_AES_H__
#define __IS_AES_H__

#include "iscrypt_symmetric.h"

/* External Function Definition */
unsigned char AESCrypt(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);

#endif