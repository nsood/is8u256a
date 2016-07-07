#include "Test\iscrypt_rsa_sec_test.h"
#include "iscrypt_rsa2048_selftest.h"

unsigned char main()
{
	unsigned char xdata ret;

	ret = RSA1024_DECRYPT_SEC_TEST();

	if(0 != ret)
	{
		goto ErrorExit;
	}

	ret = RSA2048_DECRYPT_SEC_TEST();

	if(0 != ret)
	{
		goto ErrorExit;
	}

	ret = RSA1024_SIGN_SEC_TEST();

	if(0 != ret)
	{
		goto ErrorExit;
	}

	ret = RSA2048_SIGN_SEC_TEST();

	if(0 != ret)
	{
		goto ErrorExit;
	}

	ret = RSA_SelfTest();

	return 0;

ErrorExit:
	return 1;
}
