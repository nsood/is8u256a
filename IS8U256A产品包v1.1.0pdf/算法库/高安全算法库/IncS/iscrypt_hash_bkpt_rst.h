/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:		is8u_hash_bkpt_rst.h
* Author:        	PeiChao
* Version:			1.0.0.131119        
* Date:				2013.11.19
* Description:		
* 					
*
* Others:         
*					
* Function List:  
*   				1. HASHSetBkpt
*					2. HASHRestore
*
* History:
*
*   1. Date:				
*      Author:				
*	   Version:
*      Modification:		
*
\****************************************************************/
#ifndef __IS_HASH_BKPT_RST_H__
#define __IS_HASH_BKPT_RST_H__

#include "iscrypt.h"

#define SHA1_IV_SIZE			20
#define SHA256_IV_SIZE			32
#define SHA384_IV_SIZE			64
#define SHA512_IV_SIZE			64
#define SM3_IV_SIZE				32

#define SHA1_MSG_LEN_SIZE		8
#define SHA256_MSG_LEN_SIZE		8
#define SHA384_MSG_LEN_SIZE		16
#define SHA512_MSG_LEN_SIZE		16
#define SM3_MSG_LEN_SIZE		8


unsigned char HASHSetBkpt(
	unsigned char ChoiceOfHASH,					// in
	unsigned char xdata *pbRareIV,				// out
	unsigned char xdata *pLengthHasProcessed		// out
);

unsigned char HASHRestore(
	unsigned char ChoiceOfHASH,					// in
	unsigned char xdata *pbRareIV,				// in
	unsigned char xdata *pLengthHasProcessed		// in
);


#endif
