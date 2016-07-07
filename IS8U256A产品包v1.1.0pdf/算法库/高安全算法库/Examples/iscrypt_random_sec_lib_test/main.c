#include "iscrypt_random_sec.h"

int main()
{
	unsigned char xdata space_for_test[64] = {0x00};

	GenRandomSEC(16, space_for_test);
	GenRandomSEC(16, space_for_test);
	GenRandomSEC(16, space_for_test);
	GenRandomSEC(16, space_for_test);

	return 0;

}

