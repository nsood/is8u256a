/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_sha.h
* Author:		PeiChao
* Version:		1.0.0.131112
* Date:			2013.11.12
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. SHA1Init
*				2. SHA1Update
*				3. SHA1Final
*   			4. SHA256Init
*				5. SHA256Update
*				6. SHA256Final
*   			7. SHA384Init
*				8. SHA384Update
*				9. SHA384Final
*   			10. SHA512Init
*				11. SHA512Update
*				12. SHA512Final

*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_SHA_H__
#define __IS_SHA_H__

#include "iscrypt.h"

#define SHA1_BLOCK_SIZE			64
#define SHA256_BLOCK_SIZE		64
#define SHA384_BLOCK_SIZE		128
#define SHA512_BLOCK_SIZE		128

#define SHA1_DIGEST_SIZE		20
#define SHA256_DIGEST_SIZE		32
#define SHA384_DIGEST_SIZE		48
#define SHA512_DIGEST_SIZE		64

/* VARIABLE */

/* External Function Definition */
//-----SHA-1-------------------------------//
void SHA1Init();

void SHA1Update(
	unsigned char xdata *pMessage		//	in
);

unsigned char SHA1Final(
	unsigned char xdata *pbMessage,		//	in 
	unsigned char bLength,				//	in 
	unsigned char xdata *pbDigest		//	out
);


//-----SHA-256-------------------------------//
void SHA256Init();

void SHA256Update(
	unsigned char xdata *pMessage		//	in
);

unsigned char SHA256Final(
	unsigned char xdata *pbMessage,		//	in 
	unsigned char bLength,				//	in 
	unsigned char xdata *pbDigest		//	out
);

//-----SHA-384-------------------------------//
void SHA384Init();

void SHA384Update(
	unsigned char xdata *pMessage		//	in
);

unsigned char SHA384Final(
	unsigned char xdata *pbMessage,		//	in 
	unsigned char bLength,				//	in 
	unsigned char xdata *pbDigest		//	out
);

//-----SHA-512-------------------------------//
void SHA512Init();

void SHA512Update(
	unsigned char xdata *pMessage		//	in
);

unsigned char SHA512Final(
	unsigned char xdata *pbMessage,		//	in 
	unsigned char bLength,				//	in 
	unsigned char xdata *pbDigest		//	out
);

/* Application Function Definition */

#endif
