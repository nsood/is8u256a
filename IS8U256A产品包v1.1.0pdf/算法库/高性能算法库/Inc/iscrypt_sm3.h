/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_sm3.h
* Author:		PeiChao
* Version:		1.0.0.131112
* Date:			2013.11.12
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. SM3Init
*				2. SM3Update
*				3. SM3Final
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_SM3_H__
#define __IS_SM3_H__

#include "iscrypt.h"


#define SM3_BLOCK_SIZE		64
#define SM3_DIGEST_SIZE		32



/* VARIABLE */

/* External Function Definition */
//-----SM3-------------------------------//
void SM3Init();

void SM3Update(
	unsigned char xdata *pMessage		//	in
);

unsigned char SM3Final(
	unsigned char xdata *pbMessage,		//	in 
	unsigned char bLength,				//	in 
	unsigned char xdata *pbDigest		//	out
);

/* Application Function Definition */


#endif
