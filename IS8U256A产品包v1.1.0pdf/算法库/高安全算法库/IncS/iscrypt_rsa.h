/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_rsa.h
* Author:		PeiChao
* Version:		1.0.0.131121
* Date:			2013.11.21
* Description:
*				Supply other bit length's RSA, it's different with orignal.
* 	
* Others:		
* 
* Function List:	
*   			1. RSAGenKeyPair
*				4. RSAEncrypt
*				5. RSADecrypt
*				6. RSASign
*				7. RSAVerify
*
* History:		
*   1. Date:			2014.11.19
*      Author:			PeiChao
*      Modification:	Change the declaration of function "RSASign", use macro definition.
*
*   2. ......
\****************************************************************/
#ifndef	__IS_RSA_H__
#define __IS_RSA_H__

#include "iscrypt.h"


/* choice of the algorithm type */
#define RSA1024				0x00
#define RSA2048				0x01

/* type of RSA private key operation */
#define STD_TYPE			0x00
#define CRT_TYPE			0x08

/* definiton of structure about key parameters */
typedef struct Struct_RSAPrivateKeyCRT
{

	/* Prime1 */
	unsigned char xdata *p;
	/* Prime2 */
	unsigned char xdata *q;
	/* Prime1 Exponent */
	unsigned char xdata *dP;
	/* Prime2 Exponent */
	unsigned char xdata *dQ;
	/* Coefficient */
	unsigned char xdata *qInv;

}RSAPRIVATEKEYCRT;

typedef struct Struct_RSAPrivateKeySTD
{

	/* Private Exponent*/
	unsigned char xdata *d;
	/* modulus */
	unsigned char xdata *n;

}RSAPRIVATEKEYSTD;

#define RSAPRIVATEKEYCTX	void

typedef struct Struct_RSAPublicKey
{

	/* Public Exponent */
	unsigned char xdata *e;
	/* modulus */
	unsigned char xdata *n;

}RSAPUBLICKEYCTX;

typedef struct Struct_RSAKey
{
	/* Public Key */
	RSAPUBLICKEYCTX xdata *pRSAPubKey;
	/* Private Key */
	RSAPRIVATEKEYCTX xdata *pRSAPriKey;

}RSAKEYCTX;


/* Variable */
extern unsigned char xdata IS_BUFFER_RSA[1284];

/* External Function Definition */
unsigned char RSAGenKeyPair(
	unsigned char bMode,				// in
	RSAPUBLICKEYCTX xdata *pRSAPubKey,	// in, out
	RSAPRIVATEKEYCTX xdata *pRSAPriKey	// out
);

unsigned char RSAEncrypt(		
	unsigned char bMode,				// in
	RSAPUBLICKEYCTX xdata *pRSAPubKey,	// in
	unsigned char xdata *pbPlain		// in, out
);

unsigned char RSADecrypt(
	unsigned char bMode,				// in
	RSAPRIVATEKEYCTX xdata *pRSAPriKey,	// in
	unsigned char xdata *pbCipher		// in, out
);

#define RSASign(bmode, pRSAPriKey, pbDigest)	\
			RSADecrypt((bmode), (pRSAPriKey), (pbDigest))

unsigned char RSAVerify(		
	unsigned char bMode,				// in
	RSAPUBLICKEYCTX xdata *pRSAPubKey,	// in
	unsigned char xdata *pbSignature,	// in
	unsigned char *pbDigest				// in
);

#endif
