/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_sm2.h
* Author:		PeiChao
* Version:		1.0.0.131120
* Date:			2013.11.20
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. SM2GenKeyPairSEC
*				2. SM2EncryptSEC
*				3. SM2DecryptSEC
*				4. SM2SignSEC
*				5. SM2Verify
*				6. SM2KeyExchange
*				7. SM2GetZ
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_SM2_SEC_H__
#define __IS_SM2_SEC_H__

#include "iscrypt.h"
#include "iscrypt_sm2.h"

/* Variable */

/* all Function Definition */
unsigned char SM2GenKeyPairSEC(
	SM2PUBLICKEYCTX xdata *pSM2PubKey,	// out
	SM2PRIVATEKEYCTX xdata *pSM2PriKey	// out
);

unsigned char SM2EncryptSEC(
	SM2PUBLICKEYCTX xdata *pSM2PubKey,	// in
	SM2PLAINTEXT xdata *pPlaintext,		// in
	SM2CIPHERTEXT xdata *pCiphertext	// out
);

unsigned char SM2DecryptSEC(
	SM2PRIVATEKEYCTX xdata *pSM2PriKey,	// in
	SM2CIPHERTEXT xdata *pCiphertext,	// in	   	
	SM2PLAINTEXT xdata *pPlaintext		// out
);

unsigned char SM2SignSEC(
	SM2PRIVATEKEYCTX xdata *pSM2PriKey,	// in
	unsigned char xdata *pbDigest,		// in
	SM2SIGNATURE xdata *pSignature 		// out
);

unsigned char SM2Verify(
	SM2PUBLICKEYCTX xdata *pSM2PubKey,	// in
	unsigned char xdata *pbDigest,		// in
	SM2SIGNATURE xdata *pSignature		// in
);

#endif


