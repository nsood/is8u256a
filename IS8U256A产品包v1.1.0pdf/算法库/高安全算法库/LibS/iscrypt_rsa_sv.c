/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:		iscrypt_rsa_sv.c
* Author:			PeiChao
* Version:			1.0.0.131212
* Date:				2013.12.12
* Description:		
*					The function definition and implementation
*					about RSA Sign and Verify.
*
* Others:
*
* Function List:
*
*					1. RSASign
*					2. RSAVerify
*
* History:
*
*   <  author  >    <  date  >    <  version  >    <  description  >
*     PeiChao        12/12/13        1.0.0.0         building this module
*     PeiChao        19/11/14        1.0.1.0         Delete function "RSASing", Change the declaration
*													 of function "RSASign", use macro definition.
*
\****************************************************************/
#include <string.h>

#include "iscrypt.h"
#include "iscrypt_rsa.h"

/****************************************************************\
* Function:			RSAVerify
*
* Description: 		
*
* Calls:			
*					RSAEncrypt
*					memcmp
*
* Called By:		
*
* Input:
*					bMode
*						The operation mode to set the length of rsa
*					which mode to use between STD and CRT.
*
*					pRSAPubKey
*						Point to RSA private key.
*
*					pbSignature
*						Point to the signature.
*
*					pbDigest
*						Point to the digest of msg that will be signed.
*
* Output:			
*					1. pbDigest
*							The signature will stored in here.
*
* Return:			
*					SUCCESS
*					FAIL
*					OUT_OF_RANGE_ERROR
*
* Others:			None
*
* Remark:	
*					The Signature will be modified after call the funtion,
*					So if signature will be used later, note backup it.
*
\****************************************************************/
unsigned char RSAVerify(		
	unsigned char bMode,					// in
	RSAPUBLICKEYCTX xdata *pRSAPubKey,		// in
	unsigned char xdata *pbSignature,		// in
	unsigned char *pbDigest					// in
){
	unsigned char xdata ret;
	int xdata len;

	if (SUCCESS != (ret = RSAEncrypt(bMode, pRSAPubKey, pbSignature)))
	{
		return ret;
	}

	/* */
	if (bMode & 0x01)
	{
		len = 256;
	}
	else
	{
		len = ((bMode & 0xF0) >> 1) + 128;
	}

	if (memcmp(pbSignature, pbDigest, len))
	{
		return FAIL;
	}

	return SUCCESS;
}
