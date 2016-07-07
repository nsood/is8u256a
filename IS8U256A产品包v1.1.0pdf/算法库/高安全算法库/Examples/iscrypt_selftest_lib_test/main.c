#include "iscrypt_selftest.h"

// bit7    bit6    bit5    bit4    bit3    bit2    bit1    bit0
// SM4     SM3     SM2     SM1     --      Random  RSA     SHA256

void main()
{
    unsigned char xdata ret;
    
    ret = SelfTest();
    
    while(ret);
}