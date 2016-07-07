#include <string.h>
#include "iscrypt_sm3.h"
#include "iscrypt_sm3_test.h"

unsigned char xdata space_for_test[1024];

unsigned char code SM3_VECTOR[] = {
	0X61,0X62,0X63,0X64,0X62,0X63,0X64,0X65,	\
	0X63,0X64,0X65,0X66,0X64,0X65,0X66,0X67,	\
	0X65,0X66,0X67,0X68,0X66,0X67,0X68,0X69,	\
	0X67,0X68,0X69,0X6A,0X68,0X69,0X6A,0X6B,	\
	0X69,0X6A,0X6B,0X6C,0X6A,0X6B,0X6C,0X6D,	\
	0X6B,0X6C,0X6D,0X6E,0X6C,0X6D,0X6E,0X6F,	\
	0X6D,0X6E,0X6F,0X70,0X6E,0X6F,0X70,0X71,	\
	0X6E,0X6F,0X70,0X71,0X6E,0X6F,0X70,0X71

};

unsigned char code DIGEST_SM3_3[] = 
{
	0X66, 0XC7, 0XF0, 0XF4, 0X62, 0XEE, 0XED, 0XD9, 0XD1, 0XF2, 0XD4, 0X6B, 0XDC, 0X10, 0XE4, 0XE2, 0X41, 0X67, 0XC4, 0X87, 0X5C, 0XF2, 0XF7, 0XA2, 0X29, 0X7D, 0XA0, 0X2B, 0X8F, 0X4B, 0XA8, 0XE0
};

unsigned char code DIGEST_SM3_55[] = 
{
    0X86,0X94,0XBD,0XBC,0X9B,0X99,0X25,0X0A,0X68,0X93,0XA5,0X3C,0X64,0X8F,0XEA,0X52,0XD8,0X52,0XF2,0X5E,0X7C,0X99,0XF2,0XCD,0X98,0XCC,0X3F,0X5B,0XBB,0X5D,0XE7,0X55
};

unsigned char code DIGEST_SM3_56[] = 
{
	0X63, 0X9B, 0X6C, 0XC5, 0XE6, 0X4D, 0X9E, 0X37, 0XA3, 0X90, 0XB1, 0X92, 0XDF, 0X4F, 0XA1, 0XEA, 0X07, 0X20, 0XAB, 0X74, 0X7F, 0XF6, 0X92, 0XB9, 0XF3, 0X8C, 0X4E, 0X66, 0XAD, 0X7B, 0X8C, 0X05
};

unsigned char code DIGEST_SM3_63[] = 
{
    0X61,0XA7,0XBE,0X24,0X9E,0X4E,0X4C,0X64,0X8E,0X9A,0XEC,0XDF,0X6B,0XCB,0X39,0XFE,0X5E,0X02,0X9C,0X3E,0XB9,0X92,0X33,0XCC,0XE2,0XC6,0X4B,0XDF,0X73,0XF7,0X04,0XBE
};

unsigned char code DIGEST_SM3_64[] = 
{
	0X25, 0XE3, 0X41, 0X3D, 0X11, 0X9C, 0X66, 0X7A, 0X80, 0X2D, 0X51, 0X58, 0X6F, 0X1E, 0X44, 0X3D, 0XE9, 0XF9, 0XCD, 0XAE, 0X12, 0X32, 0X7A, 0XF9, 0X74, 0XEF, 0XF7, 0XC5, 0XE8, 0X30, 0X15, 0X02
};
												 
unsigned char code DIGEST_SM3_128[] = 
{
	0X06, 0XFA, 0XCB, 0X95, 0XD3, 0X29, 0X0F, 0X56, 0XC1, 0XB4, 0X07, 0X01, 0X8B, 0X5A, 0XF2, 0XEF, 0XA1, 0X4B, 0X4B, 0XE6, 0X16, 0X9A, 0X67, 0X21, 0XDE, 0XB1, 0X41, 0XBC, 0XE6, 0XB4, 0XA5, 0X45
};

unsigned char code DIGEST_SM3_184[] = 
{
	0X59, 0XDA, 0X36, 0X7F, 0X78, 0X07, 0X6A, 0XA4, 0X04, 0X37, 0X9A, 0XEA, 0X0E, 0X84, 0X4D, 0X61, 0X4C, 0XCE, 0X94, 0X8F, 0X63, 0XA6, 0X29, 0X68, 0X3F, 0X67, 0X8F, 0X5D, 0XE4, 0XE0, 0X80, 0X6F
};


char SM3_TEST()
{
	unsigned char xdata ret;
	memcpy(space_for_test, SM3_VECTOR, 64);

	/////////////////////////////////////////////////////////////////
	SM3Init();

	ret = SM3Final(space_for_test, 3, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SM3_3, 32);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	SM3Init();

	ret = SM3Final(space_for_test, 55, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SM3_55, 32);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	SM3Init();

	ret = SM3Final(space_for_test, 56, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SM3_56, 32);

	if (0 != ret)
	{
		goto ErrorExit;
	}
    
	/////////////////////////////////////////////////////////////////
	SM3Init();

	ret = SM3Final(space_for_test, 63, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SM3_63, 32);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	SM3Init();

	SM3Update(space_for_test);

	ret = SM3Final(space_for_test, 0, space_for_test+0x200);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+0x200, DIGEST_SM3_64, 32);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	/////////////////////////////////////////////////////////////////
	SM3Init();

	SM3Update(space_for_test);

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

	return 0;

ErrorExit:
	return 1;
}
