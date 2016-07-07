/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_rsa2048_sec.h
* Author:		PeiChao
* Version:		1.0.0.131216
* Date:			2013.12.16
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. RSADecryptSCA
*				2. RSASignSCA
*   			1. RSADecryptSEC
*				2. RSASignSEC
*
* History:		
*   1. Date:		
*      Author:		
*      Modification:
*				
*   2. ......
\****************************************************************/
#ifndef	__IS_ISCRYPT_RSA_SEC_H__
#define __IS_ISCRYPT_RSA_SEC_H__

#include "iscrypt.h"
#include "iscrypt_rsa.h"

extern unsigned char xdata IS_BUFFER_RSA_SCA[1284];

/* External Function Definition */
unsigned char RSADecryptSCA(
	unsigned char bMode,				// in
	RSAKEYCTX xdata *pRSAKey,			// in
	unsigned char xdata *pbMessage		// in, out
);

#define RSASignSCA(bmode, pRSAKey, pbDigest)	\
	RSADecryptSCA((bmode), (pRSAKey), (pbDigest))

unsigned char RSADecryptSEC(
	unsigned char bMode,				//in 
	RSAKEYCTX xdata *pRSAKey,			//in 
	unsigned char xdata *pbCiphertext	//in,out
);

#define RSASignSEC(bmode, pRSAKey, pbDigest)	\
			RSADecryptSEC((bmode), (pRSAKey), (pbDigest))

#endif
