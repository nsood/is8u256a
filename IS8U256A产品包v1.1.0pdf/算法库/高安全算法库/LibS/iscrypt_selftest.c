#include "iscrypt_selftest.h"
#include "iscrypt_random_sec.h"

// bit7    bit6    bit5    bit4    bit3    bit2    bit1    bit0
// SM4     SM3     SM2     SM1     --      Random  RSA     SHA256


unsigned char SelfTest()
{
    unsigned char res = 0;
    unsigned char xdata ret;

 	ret = SHA256_SelfTest();

 	res |= ret;

 	ret = RSA_SelfTest();
    if (0 != ret)
    {
        ret = 1;
    }

 	res |= (ret << 1);

	ret = RNG_SelfTest();

	res |= (ret << 2);

	ret = SM1_SelfTest();

	res |= (ret << 4);

	ret = SM2_SelfTest();
    if (0 != ret)
    {
        ret = 1;
    }

	res |= (ret << 5);

	ret = SM3_SelfTest();

	res |= (ret << 6);

	ret = SM4_SelfTest();

	res |= (ret << 7);

    return res;  
}