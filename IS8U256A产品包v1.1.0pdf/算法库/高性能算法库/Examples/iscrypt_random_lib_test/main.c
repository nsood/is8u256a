#include "iscrypt_random.h"

sfr	rCFCR  = 0x8E;
sfr	rPCON1 = 0x96;
sfr	rPCON0 = 0xEA;

void main()
{
	unsigned char xdata space_for_test[256] = {0x00};

	rCFCR  = 0x00;
	rCFCR  = 0x12;
	rPCON0 = 0xFF;
	rPCON1 = 0xFF;

	/* */
	GenRandom(0, space_for_test);
	GenRandom(16, space_for_test);
	GenRandom(256, space_for_test);
	GenRandom(513, space_for_test);


	/* */
	GetFactoryCode(space_for_test);

	while(1) ;
}

