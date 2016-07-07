#include "Test\rsa_test.h"
#include "iscrypt_rsa.h"

sfr	rCFCR  = 0x8E;
sfr	rPCON1 = 0x96;
sfr	rPCON0 = 0xEA;

RSAPUBLICKEYCTX xdata RSAPubKey;

RSAPRIVATEKEYSTD xdata RSAPriKeySTD;
RSAPRIVATEKEYCRT xdata RSAPriKeyCRT;

void main()
{
	rCFCR  = 0x00;
	rCFCR  = 0x00;

	rPCON0 = 0xFF;
	rPCON1 = 0xFF;

	GENERATE_KEY_TEST();

	RSA_ENCRYPT_TEST();

	RSA_DECRYPT_TEST();

	RSA_SIGN_TEST();

	RSA_VERIFY_TEST();

	RSA_WHOLE_TEST();

	RSA_TEST();

	while (1);

}
