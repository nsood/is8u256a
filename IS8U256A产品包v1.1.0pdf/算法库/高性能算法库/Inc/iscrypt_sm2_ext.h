/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_sm2_ext.h
* Author:		PeiChao
* Version:		1.0.0.131121
* Date:			2013.11.21
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. SM2EncryptInit
*				2. SM2EncryptUpdate
*				3. SM2EncryptFinal
*				4. SM2DecryptInit
*				5. SM2DecryptUpdate
*				6. SM2DecryptFinal
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_SM2_EXT_H__
#define __IS_SM2_EXT_H__

#include "iscrypt.h"
#include "iscrypt_sm2.h"

/* Variable */

/* External Function Definition */
unsigned char SM2EncryptInit(
	SM2PUBLICKEYCTX xdata *pSM2PubKey,	// in
	SM2POINT xdata *pC1					// out
);

unsigned char SM2EncryptUpdate(
	unsigned char xdata *pDataPart,		// in
	unsigned char xdata *pC2Part		// out
);

unsigned char SM2EncryptFinal(
	BIGINTEGER xdata *pDataLastPart,	// in
	unsigned char xdata *pC2LastPart,	// out
	unsigned char xdata *pC3			// out

);

unsigned char SM2DecryptInit(
	SM2PRIVATEKEYCTX xdata *pSM2PriKey,	// in
	SM2POINT xdata *pC1					// in
);

unsigned char SM2DecryptUpdate(
	unsigned char xdata *pC2Part,		// in	   	
	unsigned char xdata *pDataPart		// out
);

unsigned char SM2DecryptFinal(
	BIGINTEGER xdata *pC2LastPart,		// in
	unsigned char xdata *pC3,			// in
	unsigned char xdata *pDataLastPart	// out
);

#endif
