#include "Test\iscrypt_des_test.h"
#include "Test\iscrypt_tdes_test.h"

void main()
{

	unsigned char ret;

	ret = DES_TEST();

	ret = TDES_TEST();

	while(1) ;
}