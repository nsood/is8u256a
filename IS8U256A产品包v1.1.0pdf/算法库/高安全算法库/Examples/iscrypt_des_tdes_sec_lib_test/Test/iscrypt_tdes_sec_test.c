#include <string.h>

#include "iscrypt_des_tdes_sec.h"
#include "iscrypt_tdes_sec_test.h"

extern unsigned char xdata space_for_test[1024];

extern BLOCKCIPHERPARAM xdata BlockCipherParam;

unsigned char code TDES_KEY[] = 
{
	0X01,0X23,0X45,0X67,0X89,0XAB,0XCD,0XEF,0XFE,0XDC,0XBA,0X98,0X76,0X54,0X32,0X10
};

unsigned char code TDES_IV[] = 
{
	0X13,0X57,0X9B,0XDF,0X02,0X46,0X8A,0XCE
};

unsigned char code TDES_PLAINTEXT[] = 
{
	0X01,0X23,0X45,0X67,0X89,0XAB,0XCD,0XE7,	\
	0X89,0XAB,0XCD,0XE7,0X01,0X23,0X45,0X67,	\
	0X13,0X57,0X9B,0XDF,0X02,0X46,0X8A,0XCE,	\
	0X02,0X46,0X8A,0XCE,0X13,0X57,0X9B,0XDF,	\
	0X01,0X23,0X45,0X67,0X89,0XAB,0XCD,0XEF
};

unsigned char code TDES_CIPHERTEXT_ECB[] = 
{
	0X7F,0X1D,0X0A,0X77,0X82,0X6B,0X8A,0XFF,	\
	0XAF,0X1A,0X75,0X49,0X3B,0X25,0XD7,0X44,	\
	0X0F,0X67,0XE2,0XEB,0X76,0XA5,0X25,0X9C,	\
	0XA0,0XD4,0X58,0XD7,0X67,0X96,0XFF,0X8E,	\
	0X1A,0X4D,0X67,0X2D,0XCA,0X6C,0XB3,0X35
};

unsigned char code TDES_CIPHERTEXT_CBC[] = 
{
	0X9E,0X78,0X5B,0XF2,0XF9,0XA7,0X57,0X04,	\
	0XC3,0X18,0X89,0X3E,0X40,0XDA,0XCE,0XBD,	\
	0X0E,0X4B,0X6D,0X8E,0X80,0X00,0XE8,0X74,	\
	0X4D,0XED,0X7F,0XCB,0XCF,0X38,0X58,0XA1,	\
	0X3B,0X23,0X47,0X62,0X7C,0X12,0X48,0XC1
};

unsigned char TDES_SEC_TEST()
{
	unsigned char xdata ret;
	unsigned char xdata sl = D_HIGH_LEVEL_S;

	memcpy(space_for_test, TDES_KEY, 2*TDES_BLOCK_SIZE);
	memcpy(space_for_test+2*TDES_BLOCK_SIZE, TDES_IV, TDES_BLOCK_SIZE);

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+3*TDES_BLOCK_SIZE, TDES_PLAINTEXT, 5*TDES_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_ECB | SYM_ENCRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+2*TDES_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+3*TDES_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+3*TDES_BLOCK_SIZE;
	BlockCipherParam.pbReserve = &sl;

	ret = TDESCryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+3*TDES_BLOCK_SIZE, TDES_CIPHERTEXT_ECB, 5*TDES_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+3*TDES_BLOCK_SIZE, TDES_CIPHERTEXT_ECB, 5*TDES_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_ECB | SYM_DECRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+2*TDES_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+3*TDES_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+3*TDES_BLOCK_SIZE;
	BlockCipherParam.pbReserve = &sl;

	ret = TDESCryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+3*TDES_BLOCK_SIZE, TDES_PLAINTEXT, 5*TDES_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+3*TDES_BLOCK_SIZE, TDES_PLAINTEXT, 5*TDES_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_CBC | SYM_ENCRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+2*TDES_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+3*TDES_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+8*TDES_BLOCK_SIZE;
	BlockCipherParam.pbReserve = &sl;

	ret = TDESCryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+8*TDES_BLOCK_SIZE, TDES_CIPHERTEXT_CBC, 5*TDES_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	memcpy(space_for_test+3*TDES_BLOCK_SIZE, TDES_CIPHERTEXT_CBC, 5*TDES_BLOCK_SIZE);


	BlockCipherParam.bOpMode = SYM_CBC| SYM_DECRYPT;
	BlockCipherParam.pbKey = space_for_test;
	BlockCipherParam.pbIV = space_for_test+2*TDES_BLOCK_SIZE;

	BlockCipherParam.pbInput = space_for_test+3*TDES_BLOCK_SIZE;
	BlockCipherParam.bTotalBlock = 5;
	BlockCipherParam.pbOutput = space_for_test+8*TDES_BLOCK_SIZE;
	BlockCipherParam.pbReserve = &sl;

	ret = TDESCryptSEC(&BlockCipherParam);
	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+8*TDES_BLOCK_SIZE, TDES_PLAINTEXT, 5*TDES_BLOCK_SIZE);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;

}
