/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_sm1.h
* Author:		PeiChao
* Version:		1.0.0.131112
* Date:			2013.11.12
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. SM1Crypt
*
* History:		
*   1. Date:			
*	   Version:			
*      Author:						
*      Modification:		
*   2. ......
\****************************************************************/
#ifndef	__IS_SM1_H__
#define __IS_SM1_H__

#include "iscrypt_symmetric.h"

/* External Function Definition */
unsigned char SM1Crypt(
	BLOCKCIPHERPARAM xdata *pBlockCipherParam		//	in,out
);

#endif
