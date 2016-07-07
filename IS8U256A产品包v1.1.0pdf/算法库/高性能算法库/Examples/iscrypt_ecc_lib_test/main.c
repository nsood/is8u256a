#include "Test\iscrypt_ecc_test.h"

void main()
{
    unsigned char ret;
    
    ret = ECC_TEST_160();
    
    ret = ECC_TEST_192();
    
    ret = ECC_TEST_224();
    
    ret = ECC_TEST_256();   

	while (1);
}
