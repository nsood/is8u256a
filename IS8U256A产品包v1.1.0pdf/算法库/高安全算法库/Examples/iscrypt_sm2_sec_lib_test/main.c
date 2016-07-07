#include "Test\iscrypt_sm2_test.h"

void main()
{

	GENERATE_KEY_TEST();

	SM2_ENCRYPT_DECRYPT_TEST();

	SM2_SIGN_VERIFY_TEST();

	SM2_KEY_EXCHANGE_TEST();

	SM2_KEY_GET_Z_TEST();

	/////////////////////////////////////////////////////////////////

	return ;
}