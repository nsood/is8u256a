#include <string.h>
#include "iscrypt_sm2.h"
#include "iscrypt_sm3.h"
#include "iscrypt_sm2_sec.h"
#include "iscrypt_sm2_test.h"

//
unsigned char xdata space_for_test[1024];

//
SM2POINT xdata Point;

SM2PUBLICKEYCTX xdata PubKey_A;
SM2PUBLICKEYCTX xdata PubKey_B;
SM2PUBLICKEYCTX xdata TempPubKey_A;
SM2PUBLICKEYCTX xdata TempPubKey_B;

SM2PRIVATEKEYCTX xdata PriKey_A;
SM2PRIVATEKEYCTX xdata PriKey_B;
SM2PRIVATEKEYCTX xdata TempPriKey_A; 
SM2PRIVATEKEYCTX xdata TempPriKey_B;

IDINFO xdata IDInfo_A, xdata IDInfo_B;

SM2PLAINTEXT xdata Plain;
SM2CIPHERTEXT xdata Cipher;

SM2SIGNATURE xdata Signature;

SM2KEYEXCHANGEPARAM xdata KeyExchangeParam;


// TEST CONST
unsigned char code SM2PublicKey[64] = 
{
	0X09,0XF9,0XDF,0X31,0X1E,0X54,0X21,0XA1,0X50,0XDD,0X7D,0X16,0X1E,0X4B,0XC5,0XC6,0X72,0X17,0X9F,0XAD,0X18,0X33,0XFC,0X07,0X6B,0XB0,0X8F,0XF3,0X56,0XF3,0X50,0X20,	\
	0XCC,0XEA,0X49,0X0C,0XE2,0X67,0X75,0XA5,0X2D,0XC6,0XEA,0X71,0X8C,0XC1,0XAA,0X60,0X0A,0XED,0X05,0XFB,0XF3,0X5E,0X08,0X4A,0X66,0X32,0XF6,0X07,0X2D,0XA9,0XAD,0X13
};

unsigned char code SM2PrivateKey[32] = 
{
	0X39,0X45,0X20,0X8F,0X7B,0X21,0X44,0XB1,0X3F,0X36,0XE3,0X8A,0XC6,0XD3,0X9F,0X95,0X88,0X93,0X93,0X69,0X28,0X60,0XB5,0X1A,0X42,0XFB,0X81,0XEF,0X4D,0XF7,0XC5,0XB8						  	
};



unsigned char code SM2KeyExchangeParam[] = 
{
	// SELF TEMP PUBLIC KEY AND PRIVATE KEY
	0X64,0XCE,0XD1,0XBD,0XBC,0X99,0XD5,0X90,0X04,0X9B,0X43,0X4D,0X0F,0XD7,0X34,0X28,0XCF,0X60,0X8A,0X5D,0XB8,0XFE,0X5C,0XE0,0X7F,0X15,0X02,0X69,0X40,0XBA,0XE4,0X0E,	\
	0X37,0X66,0X29,0XC7,0XAB,0X21,0XE7,0XDB,0X26,0X09,0X22,0X49,0X9D,0XDB,0X11,0X8F,0X07,0XCE,0X8E,0XAA,0XE3,0XE7,0X72,0X0A,0XFE,0XF6,0XA5,0XCC,0X06,0X20,0X70,0XC0,	\
	0XD4,0XDE,0X15,0X47,0X4D,0XB7,0X4D,0X06,0X49,0X1C,0X44,0X0D,0X30,0X5E,0X01,0X24,0X00,0X99,0X0F,0X3E,0X39,0X0C,0X7E,0X87,0X15,0X3C,0X12,0XDB,0X2E,0XA6,0X0B,0XB3,	\
	// SELF INHERENT PUBLIC KEY AND PRIVATE KEY
	0X16,0X0E,0X12,0X89,0X7D,0XF4,0XED,0XB6,0X1D,0XD8,0X12,0XFE,0XB9,0X67,0X48,0XFB,0XD3,0XCC,0XF4,0XFF,0XE2,0X6A,0XA6,0XF6,0XDB,0X95,0X40,0XAF,0X49,0XC9,0X42,0X32,	\
	0X4A,0X7D,0XAD,0X08,0XBB,0X9A,0X45,0X95,0X31,0X69,0X4B,0XEB,0X20,0XAA,0X48,0X9D,0X66,0X49,0X97,0X5E,0X1B,0XFC,0XF8,0XC4,0X74,0X1B,0X78,0XB4,0XB2,0X23,0X00,0X7F,	\
	0X81,0XEB,0X26,0XE9,0X41,0XBB,0X5A,0XF1,0X6D,0XF1,0X16,0X49,0X5F,0X90,0X69,0X52,0X72,0XAE,0X2C,0XD6,0X3D,0X6C,0X4A,0XE1,0X67,0X84,0X18,0XBE,0X48,0X23,0X00,0X29,	\
	// OTHER TEMP PUBLIC KEY AND PRIVATE KEY
	0XAC,0XC2,0X76,0X88,0XA6,0XF7,0XB7,0X06,0X09,0X8B,0XC9,0X1F,0XF3,0XAD,0X1B,0XFF,0X7D,0XC2,0X80,0X2C,0XDB,0X14,0XCC,0XCC,0XDB,0X0A,0X90,0X47,0X1F,0X9B,0XD7,0X07,	\
	0X2F,0XED,0XAC,0X04,0X94,0XB2,0XFF,0XC4,0XD6,0X85,0X38,0X76,0XC7,0X9B,0X8F,0X30,0X1C,0X65,0X73,0XAD,0X0A,0XA5,0X0F,0X39,0XFC,0X87,0X18,0X1E,0X1A,0X1B,0X46,0XFE,	\
	0X7E,0X07,0X12,0X48,0X14,0XB3,0X09,0X48,0X91,0X25,0XEA,0XED,0X10,0X11,0X13,0X16,0X4E,0XBF,0X0F,0X34,0X58,0XC5,0XBD,0X88,0X33,0X5C,0X1F,0X9D,0X59,0X62,0X43,0XD6,	\
	// OTHER INHERENT PUBLIC KEY AND PRIVATE KEY
	0X6A,0XE8,0X48,0XC5,0X7C,0X53,0XC7,0XB1,0XB5,0XFA,0X99,0XEB,0X22,0X86,0XAF,0X07,0X8B,0XA6,0X4C,0X64,0X59,0X1B,0X8B,0X56,0X6F,0X73,0X57,0XD5,0X76,0XF1,0X6D,0XFB,	\
	0XEE,0X48,0X9D,0X77,0X16,0X21,0XA2,0X7B,0X36,0XC5,0XC7,0X99,0X20,0X62,0XE9,0XCD,0X09,0XA9,0X26,0X43,0X86,0XF3,0XFB,0XEA,0X54,0XDF,0XF6,0X93,0X05,0X62,0X1C,0X4D,	\
	0X78,0X51,0X29,0X91,0X7D,0X45,0XA9,0XEA,0X54,0X37,0XA5,0X93,0X56,0XB8,0X23,0X38,0XEA,0XAD,0XDA,0X6C,0XEB,0X19,0X90,0X88,0XF1,0X4A,0XE1,0X0D,0XEF,0XA2,0X29,0XB5,	\
	// SELF ID
	0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,	\
	// OTHER ID (Don't be curious, it's same with 'SELF ID'. Just test!)
	0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,	\
};

char code SM2Plaintext[] = "encryption standard";

char code SM2Message[] = "message digest";


// TEST FUNCTION
char GENERATE_KEY_TEST()
{
	unsigned char ret;

	/////////////////////////////////////////////////////////////////
	PubKey_A.x = space_for_test;
	PubKey_A.y = space_for_test+32;

	PriKey_A.d = space_for_test+64;

	ret = SM2GenKeyPairSEC(&PubKey_A, &PriKey_A);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}

char SM2_ENCRYPT_DECRYPT_TEST()
{
	unsigned char ret;

	/////////////////////////////////////////////////////////////////

	// prepare key
	memcpy(space_for_test, SM2PublicKey, 64);
	memcpy(space_for_test+64, SM2PrivateKey, 32);

	PubKey_A.x = space_for_test;
	PubKey_A.y = space_for_test+32;

	PriKey_A.d = space_for_test+64;

	/////////////////////////////////////////////////////////////////
	
	// prepare plaintext
	memcpy(space_for_test+0x100, SM2Plaintext, strlen(SM2Plaintext));
	Plain.pd = space_for_test+0x100;
	Plain.len = strlen(SM2Plaintext);

	// prepare ciphertext
	Point.x = space_for_test+0x200;
	Point.y = space_for_test+0x220;

	Cipher.p = &Point;
	Cipher.c = space_for_test+0x260;
	Cipher.h = space_for_test+0x240;

	//
	ret = SM2EncryptSEC(&PubKey_A, &Plain, &Cipher);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	Plain.pd = space_for_test+0x300;
	Plain.len = 0x00;

	ret = SM2DecryptSEC(&PriKey_A, &Cipher, &Plain);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	Plain.pd[Plain.len] = '\0';
	ret = strcmp(SM2Plaintext, Plain.pd);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}

char SM2_SIGN_VERIFY_TEST()
{
	unsigned char ret;
	unsigned char xdata *tmp_msg;
	unsigned char xdata tmp_msg_len;

	/////////////////////////////////////////////////////////////////
	// prepare key
	memcpy(space_for_test, SM2PublicKey, 64);
	memcpy(space_for_test+64, SM2PrivateKey, 32);

	PubKey_A.x = space_for_test;
	PubKey_A.y = space_for_test+32;

	PriKey_A.d = space_for_test+64;

	/////////////////////////////////////////////////////////////////
	// precompute step 1: Za
	memcpy(space_for_test+0x100, SM2KeyExchangeParam+384, 16);

	IDInfo_A.pd = space_for_test+0x100;
	IDInfo_A.len = 16;

	ret = SM2GetZ(&PubKey_A, &IDInfo_A, space_for_test+0x100);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	tmp_msg = space_for_test+0x100;
	tmp_msg_len = 32;

	// M~ = ZA || M
 	memcpy(space_for_test+0x120, SM2Message, strlen(SM2Message));
	tmp_msg_len += strlen(SM2Message);


	// precompute step 2: e = Hash(Za || M)
	SM3Init();

	while (tmp_msg_len >= 64)
	{
		SM3Update(tmp_msg);

		tmp_msg += 64;
		tmp_msg_len -= 64;
	}

	SM3Final(tmp_msg, tmp_msg_len, space_for_test+0x100);

	// SM2 sign
	Signature.r = space_for_test+0x200;
	Signature.s = space_for_test+0x220;

	ret = SM2SignSEC(&PriKey_A, space_for_test+0x100, &Signature);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////

	ret = SM2Verify(&PubKey_A, space_for_test+0x100, &Signature);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}

char SM2_KEY_EXCHANGE_TEST()
{
	unsigned char ret;

	unsigned char xdata *pZa, xdata *pZb;

	// Just as alias
	unsigned char xdata *pbKeyAB, xdata *pbKeyBA;

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test, SM2KeyExchangeParam, sizeof (SM2KeyExchangeParam));

	//
	TempPubKey_A.x = space_for_test;
	TempPubKey_A.y = space_for_test+32;
	TempPriKey_A.d = space_for_test+64;

	PubKey_A.x = space_for_test+96;
	PubKey_A.y = space_for_test+128;
	PriKey_A.d = space_for_test+160;

	TempPubKey_B.x = space_for_test+192;
	TempPubKey_B.y = space_for_test+224;
	TempPriKey_B.d = space_for_test+256;

	PubKey_B.x = space_for_test+288;
	PubKey_B.y = space_for_test+320;
	PriKey_B.d = space_for_test+352;

	IDInfo_A.pd = space_for_test+384;
	IDInfo_A.len = 16;

	IDInfo_B.pd = space_for_test+400;
	IDInfo_B.len = 16;

	// precompute Za
	pZa = space_for_test+432;

	ret = SM2GetZ(&PubKey_A, &IDInfo_A, pZa);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	// precompute Zb
	pZb = space_for_test+464;

	ret = SM2GetZ(&PubKey_B, &IDInfo_B, pZb);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	// A is initiator, and B is responder

	/////////////////////////////////////////////////////////////////
	memset(&KeyExchangeParam, 0x00, sizeof (KeyExchangeParam));

	KeyExchangeParam.role = INITIATOR;
	KeyExchangeParam.keyLenExpected = 128;
	KeyExchangeParam.pSelfTempPubKey = &TempPubKey_A;
	KeyExchangeParam.pSelfTempPriKey = &TempPriKey_A;
	KeyExchangeParam.pSelfPubKey = &PubKey_A;
	KeyExchangeParam.pSelfPriKey = &PriKey_A;
	KeyExchangeParam.pOtherTempPubKey = &TempPubKey_B;
	KeyExchangeParam.pOtherPubKey = &PubKey_B;
	KeyExchangeParam.pSelfZ = pZa;
	KeyExchangeParam.pOtherZ = pZb;

	pbKeyAB = space_for_test + 0x200;

	ret = SM2KeyExchange(&KeyExchangeParam, pbKeyAB);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memset(&KeyExchangeParam, 0x00, sizeof (KeyExchangeParam));

	KeyExchangeParam.role = RESPONDER;
	KeyExchangeParam.keyLenExpected = 128;
	KeyExchangeParam.pSelfTempPubKey = &TempPubKey_B;
	KeyExchangeParam.pSelfTempPriKey = &TempPriKey_B;
	KeyExchangeParam.pSelfPubKey = &PubKey_B;
	KeyExchangeParam.pSelfPriKey = &PriKey_B;
	KeyExchangeParam.pOtherTempPubKey = &TempPubKey_A;
	KeyExchangeParam.pOtherPubKey = &PubKey_A;
	KeyExchangeParam.pSelfZ = pZb;
	KeyExchangeParam.pOtherZ = pZa;

	pbKeyBA = space_for_test + 0x300;

	ret = SM2KeyExchange(&KeyExchangeParam, pbKeyBA);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	ret = memcmp(pbKeyAB, pbKeyBA, 128);
	if (0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}

char SM2_KEY_GET_Z_TEST()
{
	unsigned char ret;
	unsigned char xdata *pbZ;

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test, SM2KeyExchangeParam, sizeof (SM2KeyExchangeParam));

	PubKey_A.x = space_for_test+96;
	PubKey_A.y = space_for_test+128;
	PriKey_A.d = space_for_test+160;


	IDInfo_A.pd = space_for_test+384;
	IDInfo_A.len = 16;

	pbZ = space_for_test+0x200;

	ret = SM2GetZ(&PubKey_A, &IDInfo_A, pbZ);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}
