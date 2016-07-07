#include <string.h>
#include "iscrypt_sm4_sec.h"
#include "iscrypt_sm4_test.h"

unsigned char xdata space_for_test[1024];

BLOCKCIPHERPARAM xdata BlockCipherParam;

unsigned char code BLOCK_CRYPT_KEY[] = 
{
	0X01,0X23,0X45,0X67,0X89,0XAB,0XCD,0XEF,0XFE,0XDC,0XBA,0X98,0X76,0X54,0X32,0X10
};

unsigned char code BLOCK_CRYPT_IV[] = 
{
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00
};

unsigned char code BLOCK_CRYPT_PLAINTEXT[] = 
{
	0X01,0X23,0X45,0X67,0X89,0XAB,0XCD,0XEF,0XFE,0XDC,0XBA,0X98,0X76,0X54,0X32,0X10,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,	\
	0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,	\
	0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12
};

unsigned char code BLOCK_CRYPT_CIPHERTEXT_SM4_ECB[] = 
{
	0X68,0X1E,0XDF,0X34,0XD2,0X06,0X96,0X5E,0X86,0XB3,0XE9,0X4F,0X53,0X6E,0X42,0X46,	\
	0X6B,0X36,0X33,0XA5,0XED,0X04,0XF5,0XAB,0XD5,0X19,0X78,0X70,0XB5,0X50,0X66,0X42,	\
	0X7C,0X3B,0XC4,0XEB,0X1C,0X18,0XE7,0XF1,0XD8,0X79,0XEA,0X60,0X2E,0XEC,0X46,0XCF,	\
	0X99,0XCF,0XE9,0XD2,0XB4,0XF8,0X8C,0XB9,0XD5,0X20,0X49,0XF7,0X58,0XE2,0X30,0XD9,	\
	0X70,0X62,0X8D,0X12,0X92,0X3E,0X19,0X2B,0XDF,0X4A,0XBE,0XAD,0X23,0X03,0X14,0X6D
};

unsigned char code BLOCK_CRYPT_CIPHERTEXT_SM4_CBC[] = 
{
	0X68,0X1E,0XDF,0X34,0XD2,0X06,0X96,0X5E,0X86,0XB3,0XE9,0X4F,0X53,0X6E,0X42,0X46,	\
	0XD0,0X24,0X87,0XC9,0X6F,0XC8,0X74,0X7A,0XE3,0X71,0X6B,0XDB,0X95,0X7C,0XEB,0XC4,	\
	0XA9,0X50,0X5A,0X72,0XA5,0X27,0XC0,0XFF,0XFA,0X7F,0X76,0X33,0XAA,0XB6,0XC0,0X4A,	\
	0X07,0XF0,0XFF,0XEB,0X3A,0X21,0XFE,0X17,0XF3,0X90,0X83,0XB5,0X85,0XCF,0X44,0X3F,	\
	0X3D,0XBC,0XDD,0XA1,0X7F,0X32,0X1C,0X8F,0X0C,0X92,0X40,0X69,0X22,0XBE,0XBA,0XCB
};


char SM4_TEST()
{
	unsigned char ret;
    unsigned char xdata sl = D_HIGH_LEVEL_S;

	memcpy(space_for_test, BLOCK_CRYPT_KEY, SM4_BLOCK_SIZE);
	memcpy(space_for_test+SM4_BLOCK_SIZE, BLOCK_CRYPT_IV, SM4_BLOCK_SIZE);

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*SM4_BLOCK_SIZE, BLOCK_CRYPT_PLAINTEXT, 5*SM4_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_ECB | SYM_ENCRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+SM4_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*SM4_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+2*SM4_BLOCK_SIZE;
    BlockCipherParam.pbReserve = &sl;

	ret = SM4CryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+2*SM4_BLOCK_SIZE, BLOCK_CRYPT_CIPHERTEXT_SM4_ECB, 5*SM4_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*SM4_BLOCK_SIZE, BLOCK_CRYPT_CIPHERTEXT_SM4_ECB, 5*SM4_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_ECB | SYM_DECRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+SM4_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*SM4_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+2*SM4_BLOCK_SIZE;
    BlockCipherParam.pbReserve = &sl;


	ret = SM4CryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+2*SM4_BLOCK_SIZE, BLOCK_CRYPT_PLAINTEXT, 5*SM4_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*SM4_BLOCK_SIZE, BLOCK_CRYPT_PLAINTEXT, 5*SM4_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_CBC | SYM_ENCRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+SM4_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*SM4_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+7*SM4_BLOCK_SIZE;
    BlockCipherParam.pbReserve = &sl;

	ret = SM4CryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+7*SM4_BLOCK_SIZE, BLOCK_CRYPT_CIPHERTEXT_SM4_CBC, 5*SM4_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*SM4_BLOCK_SIZE, BLOCK_CRYPT_CIPHERTEXT_SM4_CBC, 5*SM4_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_CBC| SYM_DECRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+SM4_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*SM4_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+7*SM4_BLOCK_SIZE;
    BlockCipherParam.pbReserve = &sl;

	ret = SM4CryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+7*SM4_BLOCK_SIZE, BLOCK_CRYPT_PLAINTEXT, 5*SM4_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}

