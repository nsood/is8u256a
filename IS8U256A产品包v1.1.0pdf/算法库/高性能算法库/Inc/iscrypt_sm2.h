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
*   			1. SM2GenKeyPair
*				2. SM2Encrypt
*				3. SM2Decrypt
*				4. SM2Sign
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
#ifndef	__IS_SM2_H__
#define __IS_SM2_H__

#include "iscrypt.h"

typedef struct Struct_SM2_PubKey
{
	// As the name, point to the coordinate 'x'
	unsigned char xdata *x;

	// As the name, point to the coordinate 'y'
	unsigned char xdata *y;

}SM2PUBLICKEYCTX, SM2POINT;

typedef struct Struct_SM2_PriKey
{
	unsigned char xdata *d;

}SM2PRIVATEKEYCTX;


typedef struct Struct_BigInteger
{
	// Point to the data
	unsigned char xdata *pd;

	// The length of above data
	unsigned char len;

}BIGINTEGER, SM2PLAINTEXT, IDINFO;


typedef struct Struct_SM2_Ciphertext
{

	// C1 -- It's one point of the current elliptic curve.
	SM2POINT xdata *p;

	// C2 -- The true ciphertext.
	unsigned char xdata *c;

	// C3 -- Reserve for algorithm which has hash value,
	// as lucky, the SM2 is, so you need it.
	unsigned char xdata *h;

	// The length of C2(ciphertext).
	unsigned char clen;

}SM2CIPHERTEXT;


typedef struct Struct_SM2_Signature
{

	// As the name
	unsigned char xdata *r;

	// As the name
	unsigned char xdata *s;

}SM2SIGNATURE;


typedef struct Struct_SM2_KeyExchange
{

	// The role of the player
	unsigned char role;

	// The length of key which should to be exchanged
	unsigned char keyLenExpected;

	// The temporary public key of mine
	SM2PUBLICKEYCTX xdata *pSelfTempPubKey;

	// The temporary private key of mine
	SM2PRIVATEKEYCTX xdata *pSelfTempPriKey;

	// The inherent public key of mine
	SM2PUBLICKEYCTX xdata *pSelfPubKey;

	// The inherent private key of mine
	SM2PRIVATEKEYCTX xdata *pSelfPriKey;

	// The temporary public key of the ohter party
	SM2PUBLICKEYCTX xdata *pOtherTempPubKey;

	// The inherent public key of the ohter party
	SM2PUBLICKEYCTX xdata *pOtherPubKey;

	// The Z-value of mine
	unsigned char xdata *pSelfZ;

	// The Z-value of the other party
	unsigned char xdata *pOtherZ;

}SM2KEYEXCHANGEPARAM;


/* */
#define	INITIATOR		0x00
#define	RESPONDER		0x01

/* Variable */

/* all Function Definition */
unsigned char SM2GenKeyPair(
	SM2PUBLICKEYCTX xdata *pSM2PubKey,	// out
	SM2PRIVATEKEYCTX xdata *pSM2PriKey	// out
);

unsigned char SM2Encrypt(
	SM2PUBLICKEYCTX xdata *pSM2PubKey,	// in
	SM2PLAINTEXT xdata *pPlaintext,		// in
	SM2CIPHERTEXT xdata *pCiphertext	// out
);

unsigned char SM2Decrypt(
	SM2PRIVATEKEYCTX xdata *pSM2PriKey,	// in
	SM2CIPHERTEXT xdata *pCiphertext,	// in	   	
	SM2PLAINTEXT xdata *pPlaintext		// out
);

unsigned char SM2Sign(
	SM2PRIVATEKEYCTX xdata *pSM2PriKey,	// in
	unsigned char xdata *pbDigest,		// in
	SM2SIGNATURE xdata *pSignature 		// out
);

unsigned char SM2Verify(
	SM2PUBLICKEYCTX xdata *pSM2PubKey,	// in
	unsigned char xdata *pbDigest,		// in
	SM2SIGNATURE xdata *pSignature		// in
);

unsigned char SM2KeyExchange(
	SM2KEYEXCHANGEPARAM xdata *pSM2KeyExchangeParam,	// in
	unsigned char xdata *pbKey							// out
);

/* Application Function Definition */
unsigned char SM2GetZ(
	SM2PUBLICKEYCTX xdata *pSM2PubKey,	// in
	IDINFO xdata *pIDInfo,				// in
	unsigned char xdata *pbZValue		// out
);

#endif


