#include "Test\iscrypt_des_sec_test.h"
#include "Test\iscrypt_tdes_sec_test.h"
#include "iscrypt_des_selftest.h"

unsigned char main()
{
	unsigned char xdata ret;

	ret = DES_SEC_TEST();

	if(0 != ret)
	{
		goto ErrorExit;
	}

	ret = TDES_SEC_TEST();

	if(0 != ret)
	{
		goto ErrorExit;
	}

	ret = DES_SelfTest();

	if(0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}