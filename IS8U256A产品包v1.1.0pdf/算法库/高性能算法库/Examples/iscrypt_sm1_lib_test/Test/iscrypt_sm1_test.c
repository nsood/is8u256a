#include <string.h>
#include "iscrypt_sm1.h"
#include "iscrypt_sm1_test.h"

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
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,0X22,	\
	0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,0X33,	\
	0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12,0X12
};

unsigned char code BLOCK_CRYPT_CIPHERTEXT_SM1_ECB[] = 
{
	0X69,0XE8,0X60,0X72,0X29,0X60,0X04,0X35,0XC8,0X35,0XF9,0XB5,0X2D,0XA3,0X08,0XFC,	\
	0X4B,0X68,0XD9,0X04,0X30,0X76,0X66,0X81,0X29,0X28,0XAA,0X4D,0XBF,0X58,0X42,0X44,	\
	0X7C,0X38,0X60,0X85,0X87,0X77,0X9C,0X87,0X8B,0X2A,0X5E,0XDE,0X88,0XE0,0X34,0X78,	\
	0XA9,0X62,0X66,0XD3,0XE0,0X0E,0XB9,0X9A,0XD3,0X68,0XB8,0XFC,0XAE,0X5B,0X3F,0XB9
};

unsigned char code BLOCK_CRYPT_CIPHERTEXT_SM1_CBC[] = 
{
	0X69,0XE8,0X60,0X72,0X29,0X60,0X04,0X35,0XC8,0X35,0XF9,0XB5,0X2D,0XA3,0X08,0XFC,	\
	0XB8,0X9A,0X75,0XD4,0X9B,0X3F,0XB0,0X7E,0X5A,0XCC,0XBC,0XFB,0X4C,0X4D,0X58,0X11,	\
	0XE2,0XF5,0X68,0X29,0XFA,0XD1,0XDD,0X9E,0X04,0X47,0X7F,0X6C,0X98,0X1E,0X7B,0X7C,	\
	0X39,0X45,0X7C,0X0B,0XD3,0X15,0XA8,0X01,0XF2,0X53,0X4C,0X6A,0X58,0X1F,0XC5,0X0E
};


char SM1_TEST()
{
	unsigned char ret;

	memcpy(space_for_test, BLOCK_CRYPT_KEY, SM1_BLOCK_SIZE);
	memcpy(space_for_test+SM1_BLOCK_SIZE, BLOCK_CRYPT_IV, SM1_BLOCK_SIZE);

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*SM1_BLOCK_SIZE, BLOCK_CRYPT_PLAINTEXT, 4*SM1_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_ECB | SYM_ENCRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+SM1_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*SM1_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 4;
	BlockCipherParam.pbOutput = space_for_test+2*SM1_BLOCK_SIZE;

	ret = SM1Crypt(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+2*SM1_BLOCK_SIZE, BLOCK_CRYPT_CIPHERTEXT_SM1_ECB, 4*SM1_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*SM1_BLOCK_SIZE, BLOCK_CRYPT_CIPHERTEXT_SM1_ECB, 4*SM1_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_ECB | SYM_DECRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+SM1_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*SM1_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 4;
	BlockCipherParam.pbOutput = space_for_test+2*SM1_BLOCK_SIZE;

	ret = SM1Crypt(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+2*SM1_BLOCK_SIZE, BLOCK_CRYPT_PLAINTEXT, 4*SM1_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*SM1_BLOCK_SIZE, BLOCK_CRYPT_PLAINTEXT, 4*SM1_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_CBC | SYM_ENCRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+SM1_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*SM1_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 4;
	BlockCipherParam.pbOutput = space_for_test+6*SM1_BLOCK_SIZE;

	ret = SM1Crypt(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+6*SM1_BLOCK_SIZE, BLOCK_CRYPT_CIPHERTEXT_SM1_CBC, 4*SM1_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*SM1_BLOCK_SIZE, BLOCK_CRYPT_CIPHERTEXT_SM1_CBC, 4*SM1_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_CBC| SYM_DECRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+SM1_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*SM1_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 4;
	BlockCipherParam.pbOutput = space_for_test+6*SM1_BLOCK_SIZE;

	ret = SM1Crypt(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+6*SM1_BLOCK_SIZE, BLOCK_CRYPT_PLAINTEXT, 4*SM1_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}

