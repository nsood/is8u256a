#include <string.h>
#include "iscrypt_sm3.h"
#include "iscrypt_sha.h"
#include "iscrypt_hash_bkpt_rst.h"

unsigned char xdata space_for_test[1024];

unsigned char code SHA_VECTOR[] = 
{
	0X61,0X62,0X63,0X64,0X62,0X63,0X64,0X65,	\
	0X63,0X64,0X65,0X66,0X64,0X65,0X66,0X67,	\
	0X65,0X66,0X67,0X68,0X66,0X67,0X68,0X69,	\
	0X67,0X68,0X69,0X6A,0X68,0X69,0X6A,0X6B,	\
	0X69,0X6A,0X6B,0X6C,0X6A,0X6B,0X6C,0X6D,	\
	0X6B,0X6C,0X6D,0X6E,0X6C,0X6D,0X6E,0X6F,	\
	0X6D,0X6E,0X6F,0X70,0X6E,0X6F,0X70,0X71,	\
	0X6E,0X6F,0X70,0X71,0X6E,0X6F,0X70,0X71
};


unsigned char code DIGEST_SHA1_128[] = 
{
	0XA5,0X1C,0X64,0X93,0X9D,0X88,0X69,0X7D,0XE0,0XFF,0XC4,0X8E,0X94,0XC9,0XED,0X2A,
	0X24,0XA8,0X16,0X85
};

unsigned char code DIGEST_SHA1_184[] = 
{
	0XF6,0XCC,0X70,0X5E,0X37,0X75,0XE2,0X28,0X3C,0XE6,0X8F,0XF7,0XD1,0XC3,0X4F,0XB3,
	0XDB,0X14,0X1E,0X41
};

unsigned char code DIGEST_SHA256_128[] = 
{
	0XDA,0X77,0XE7,0XEB,0X40,0XB7,0XB8,0X94,0X88,0X84,0XA7,0X1B,0X43,0XA8,0X6C,0X1B,
	0X1C,0XCD,0XF5,0X1C,0X25,0X5E,0X8C,0X83,0XC8,0X08,0XF1,0XE0,0X06,0X0A,0XCB,0X83
};

unsigned char code DIGEST_SHA256_184[] = 
{
	0XC5,0XB8,0X88,0X71,0X88,0X64,0X3D,0X00,0X1E,0XF0,0X80,0X5B,0X1B,0X64,0XEF,0XA7,
	0X4A,0XDF,0X8A,0XDC,0XA8,0X6C,0X85,0XB9,0X9B,0X1A,0X68,0X5D,0X50,0XD7,0XAA,0XB5
};

unsigned char code DIGEST_SM3_128[] = 
{
	0X06,0XFA,0XCB,0X95,0XD3,0X29,0X0F,0X56,0XC1,0XB4,0X07,0X01,0X8B,0X5A,0XF2,0XEF,
	0XA1,0X4B,0X4B,0XE6,0X16,0X9A,0X67,0X21,0XDE,0XB1,0X41,0XBC,0XE6,0XB4,0XA5,0X45
};

unsigned char code DIGEST_SM3_184[] = 
{
	0X59,0XDA,0X36,0X7F,0X78,0X07,0X6A,0XA4,0X04,0X37,0X9A,0XEA,0X0E,0X84,0X4D,0X61,
	0X4C,0XCE,0X94,0X8F,0X63,0XA6,0X29,0X68,0X3F,0X67,0X8F,0X5D,0XE4,0XE0,0X80,0X6F
};

/////////////////////////////////////////////////////////////////
char HASH_BKPT_RST_TEST()
{
	unsigned char xdata ret;
	unsigned char xdata sha_backup_iv[64];
	unsigned char xdata sha_backup_msg_length[16];

	memcpy(space_for_test, SHA_VECTOR, 64);

	/////////////////////////////////////////////////////////////////
	//SHA1
	SHA1Init();

	SHA1Update(space_for_test);
	ret = HASHSetBkpt(SHA1, sha_backup_iv, sha_backup_msg_length);
	
	// Do other things
	SHA256Init();

	// 
	ret = HASHRestore(SHA1, sha_backup_iv, sha_backup_msg_length);
	SHA1Update(space_for_test);

	ret = SHA1Final(space_for_test, 0, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SHA1_128, 20);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	SHA1Init();

	SHA1Update(space_for_test);

	SHA1Update(space_for_test);
	ret = HASHSetBkpt(SHA1, sha_backup_iv, sha_backup_msg_length);

	// Do other things
	SHA256Init();

	// 
	ret = HASHRestore(SHA1, sha_backup_iv, sha_backup_msg_length);
	ret = SHA1Final(space_for_test, 56, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SHA1_184, 20);

	if (0 != ret)
	{
		goto ErrorExit;
	}


	/////////////////////////////////////////////////////////////////
	//SHA256
	SHA256Init();

	SHA256Update(space_for_test);
	ret = HASHSetBkpt(SHA256, sha_backup_iv, sha_backup_msg_length);
	
	// Do other things
	SM3Init();

	// 
	ret = HASHRestore(SHA256, sha_backup_iv, sha_backup_msg_length);
	SHA256Update(space_for_test);

	ret = SHA256Final(space_for_test, 0, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SHA256_128, 32);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	SHA256Init();

	SHA256Update(space_for_test);

	SHA256Update(space_for_test);
	ret = HASHSetBkpt(SHA256, sha_backup_iv, sha_backup_msg_length);

	// Do other things
	SM3Init();

	// 
	ret = HASHRestore(SHA256, sha_backup_iv, sha_backup_msg_length);
	ret = SHA256Final(space_for_test, 56, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SHA256_184, 32);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	//SM3
	SM3Init();

	SM3Update(space_for_test);
	ret = HASHSetBkpt(SM3, sha_backup_iv, sha_backup_msg_length);
	
	// Do other things
	SHA1Init();

	// 
	ret = HASHRestore(SM3, sha_backup_iv, sha_backup_msg_length);
	SM3Update(space_for_test);

	ret = SM3Final(space_for_test, 0, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SM3_128, 32);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	SM3Init();

	SM3Update(space_for_test);

	SM3Update(space_for_test);
	ret = HASHSetBkpt(SM3, sha_backup_iv, sha_backup_msg_length);

	// Do other things
	SHA1Init();

	// 
	ret = HASHRestore(SM3, sha_backup_iv, sha_backup_msg_length);
	ret = SM3Final(space_for_test, 56, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SM3_184, 32);

	if (0 != ret)
	{
		goto ErrorExit;
	}


	return SUCCESS;

ErrorExit:
	return FAIL;
}
