#include <string.h>

#include "iscrypt_des_tdes_sec.h"
#include "iscrypt_des_sec_test.h"

unsigned char xdata space_for_test[1024];

BLOCKCIPHERPARAM xdata BlockCipherParam;

unsigned char code DES_KEY[] = 
{
	0X01,0X23,0X45,0X67,0X89,0XAB,0XCD,0XEF
};

unsigned char code DES_IV[] = 
{
	0X13,0X57,0X9B,0XDF,0X02,0X46,0X8A,0XCE
};

unsigned char code DES_PLAINTEXT[] = 
{
	0X01,0X23,0X45,0X67,0X89,0XAB,0XCD,0XE7,	\
	0X89,0XAB,0XCD,0XE7,0X01,0X23,0X45,0X67,	\
	0X13,0X57,0X9B,0XDF,0X02,0X46,0X8A,0XCE,	\
	0X02,0X46,0X8A,0XCE,0X13,0X57,0X9B,0XDF,	\
	0X01,0X23,0X45,0X67,0X89,0XAB,0XCD,0XEF
};

unsigned char code DES_CIPHERTEXT_ECB[] = 
{
	0XC9,0X57,0X44,0X25,0X6A,0X5E,0XD3,0X1D,	\
	0X65,0XFB,0X86,0XE1,0X1E,0X39,0XA2,0X63,	\
	0X07,0X1C,0XAD,0X79,0X67,0XF5,0X50,0XB4,	\
	0X96,0X35,0X8F,0X70,0X49,0X4C,0X02,0XB2,	\
	0X56,0XCC,0X09,0XE7,0XCF,0XDC,0X4C,0XEF
};

unsigned char code DES_CIPHERTEXT_CBC[] = 
{
	0X7D,0X85,0X1C,0XFF,0XE1,0X84,0XFB,0X87,	\
	0X5C,0X71,0X96,0XC8,0X4F,0XDF,0X4E,0XCF,	\
	0X8B,0XDA,0XE0,0X42,0X4F,0XDC,0X41,0X8E,	\
	0X13,0X02,0XCE,0X0C,0X34,0X23,0XE3,0X31,	\
	0XE5,0XC7,0X3E,0X34,0XF1,0X98,0X26,0XDE
};


unsigned char DES_SEC_TEST()
{
	unsigned char xdata ret;
	unsigned char xdata sl = D_HIGH_LEVEL_S;

	memcpy(space_for_test, DES_KEY, DES_BLOCK_SIZE);
	memcpy(space_for_test+DES_BLOCK_SIZE, DES_IV, DES_BLOCK_SIZE);

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*DES_BLOCK_SIZE, DES_PLAINTEXT, 5*DES_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_ECB | SYM_ENCRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+DES_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*DES_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+2*DES_BLOCK_SIZE;
	BlockCipherParam.pbReserve = &sl;

	ret = DESCryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+2*DES_BLOCK_SIZE, DES_CIPHERTEXT_ECB, 5*DES_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*DES_BLOCK_SIZE, DES_CIPHERTEXT_ECB, 5*DES_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_ECB | SYM_DECRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+DES_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*DES_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+2*DES_BLOCK_SIZE;
	BlockCipherParam.pbReserve = &sl;

	ret = DESCryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+2*DES_BLOCK_SIZE, DES_PLAINTEXT, 5*DES_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*DES_BLOCK_SIZE, DES_PLAINTEXT, 5*DES_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_CBC | SYM_ENCRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+DES_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*DES_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+7*DES_BLOCK_SIZE;
	BlockCipherParam.pbReserve = &sl;

	ret = DESCryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+7*DES_BLOCK_SIZE, DES_CIPHERTEXT_CBC, 5*DES_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+2*DES_BLOCK_SIZE, DES_CIPHERTEXT_CBC, 5*DES_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_CBC| SYM_DECRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+DES_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+2*DES_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+7*DES_BLOCK_SIZE;
	BlockCipherParam.pbReserve = &sl;

	ret = DESCryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+7*DES_BLOCK_SIZE, DES_PLAINTEXT, 5*DES_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}
