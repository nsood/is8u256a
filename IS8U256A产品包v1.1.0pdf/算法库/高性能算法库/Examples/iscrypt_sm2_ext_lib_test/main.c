#include <string.h>
#include "iscrypt_sm2_ext.h"

unsigned char xdata space_for_test[1024];

unsigned char code r[32] = 
{
	0X59,0X27,0X6E,0X27,0XD5,0X06,0X86,0X1A,0X16,0X68,0X0F,0X3A,0XD9,0XC0,0X2D,0XCC,0XEF,0X3C,0XC1,0XFA,0X3C,0XDB,0XE4,0XCE,0X6D,0X54,0XB8,0X0D,0XEA,0XC1,0XBC,0X21
};

unsigned char code m[32] = 
{
	0X65,0X6E,0X63,0X72,0X79,0X70,0X74,0X69,0X6F,0X6E,0X20,0X73,0X74,0X61,0X6E,0X64,0X61,0X72,0X64
};

unsigned char code SM2PrivateKey[32] = 
{
	0X39,0X45,0X20,0X8F,0X7B,0X21,0X44,0XB1,0X3F,0X36,0XE3,0X8A,0XC6,0XD3,0X9F,0X95,0X88,0X93,0X93,0X69,0X28,0X60,0XB5,0X1A,0X42,0XFB,0X81,0XEF,0X4D,0XF7,0XC5,0XB8
};

unsigned char code SM2PublicKey[64] = 
{
	0X09,0XF9,0XDF,0X31,0X1E,0X54,0X21,0XA1,0X50,0XDD,0X7D,0X16,0X1E,0X4B,0XC5,0XC6,0X72,0X17,0X9F,0XAD,0X18,0X33,0XFC,0X07,0X6B,0XB0,0X8F,0XF3,0X56,0XF3,0X50,0X20,	\
	0XCC,0XEA,0X49,0X0C,0XE2,0X67,0X75,0XA5,0X2D,0XC6,0XEA,0X71,0X8C,0XC1,0XAA,0X60,0X0A,0XED,0X05,0XFB,0XF3,0X5E,0X08,0X4A,0X66,0X32,0XF6,0X07,0X2D,0XA9,0XAD,0X13
};
 

SM2POINT xdata Point;

SM2PUBLICKEYCTX xdata PubKey_A;
SM2PRIVATEKEYCTX xdata PriKey_A;

BIGINTEGER xdata Data;

unsigned char xdata *pC2, *pC3;
unsigned char xdata *m1;

void main()
{

	memcpy(space_for_test, SM2PrivateKey, 32);
	memcpy(space_for_test+32, SM2PublicKey, 64);


	//-----------------------------------------------------
	// 19
	memcpy(space_for_test+96, m, 19);

	//
	PubKey_A.x = space_for_test + 32;
	PubKey_A.y = space_for_test + 64;

	Point.x = space_for_test + 512;
	Point.y = space_for_test + 544;

	SM2EncryptInit(&PubKey_A, &Point);


	Data.pd = space_for_test + 96;
	Data.len = 19;

	pC3 = space_for_test + 576;
	pC2 = space_for_test + 608;

	SM2EncryptFinal(&Data, pC2, pC3);


	//
	PriKey_A.d = space_for_test;

	SM2DecryptInit(&PriKey_A, &Point);

	Data.pd = pC2;
	Data.len = 19;

	m1 = pC2;

	SM2DecryptFinal(&Data, pC3, m1);

	memcmp(m1, space_for_test + 96, 19);


	//-----------------------------------------------------
	// 128
	memset(space_for_test+96, 0x00, 128);

	//
	PubKey_A.x = space_for_test + 32;
	PubKey_A.y = space_for_test + 64;

	Point.x = space_for_test + 512;
	Point.y = space_for_test + 544;

	SM2EncryptInit(&PubKey_A, &Point);

	SM2EncryptUpdate(space_for_test+96, space_for_test+608);

	// pbData can be any address
	Data.pd = space_for_test;
	Data.len = 0;

	pC3 = space_for_test + 576;
	// pC2 can be any address too
	pC2 = space_for_test;

	SM2EncryptFinal(&Data, pC2, pC3);


	//
	PriKey_A.d = space_for_test;

	SM2DecryptInit(&PriKey_A, &Point);

	SM2DecryptUpdate(space_for_test+608, space_for_test+608);

	Data.pd = pC2;
	Data.len = 0;

	m1 = pC2;

	SM2DecryptFinal(&Data, pC3, m1);


	//-----------------------------------------------------
	// 128 + 127
	memset(space_for_test+96, 0x00, 128+127);

	//
	PubKey_A.x = space_for_test + 32;
	PubKey_A.y = space_for_test + 64;

	Point.x = space_for_test + 512;
	Point.y = space_for_test + 544;

	SM2EncryptInit(&PubKey_A, &Point);

	SM2EncryptUpdate(space_for_test+96, space_for_test+608);

	Data.pd = space_for_test + 96 + 128;
	Data.len = 127;

	pC3 = space_for_test + 576;
	pC2 = space_for_test + 608 + 128;

	SM2EncryptFinal(&Data, pC2, pC3);


	//
	PriKey_A.d = space_for_test;

	SM2DecryptInit(&PriKey_A, &Point);

	SM2DecryptUpdate(space_for_test+608, space_for_test+608);

	Data.pd = pC2;
	Data.len = 127;

	m1 = pC2;

	SM2DecryptFinal(&Data, pC3, m1);


	//-----------------------------------------------------
	// 128 + 128
	memset(space_for_test+96, 0x00, 128+128);

	//
	PubKey_A.x = space_for_test + 32;
	PubKey_A.y = space_for_test + 64;

	Point.x = space_for_test + 512;
	Point.y = space_for_test + 544;

	SM2EncryptInit(&PubKey_A, &Point);

	SM2EncryptUpdate(space_for_test+96, space_for_test+608);

	SM2EncryptUpdate(space_for_test+96+128, space_for_test+608+128);

	// can be any
	Data.pd = space_for_test;
	Data.len = 0;

	pC3 = space_for_test + 576;
	// can be any
	pC2 = space_for_test;

	SM2EncryptFinal(&Data, pC2, pC3);


	//
	PriKey_A.d = space_for_test;

	SM2DecryptInit(&PriKey_A, &Point);

	SM2DecryptUpdate(space_for_test+608, space_for_test+608);

	SM2DecryptUpdate(space_for_test+608+128, space_for_test+608+128);

	// can be any
	Data.pd = pC2;
	Data.len = 0;

	m1 = pC2;

	SM2DecryptFinal(&Data, pC3, m1);


	//-----------------------------------------------------
	// 128 + 128 + 127
	memset(space_for_test+96, 0x00, 128+128+127);

	//
	PubKey_A.x = space_for_test + 32;
	PubKey_A.y = space_for_test + 64;

	Point.x = space_for_test + 512;
	Point.y = space_for_test + 544;

	SM2EncryptInit(&PubKey_A, &Point);

	SM2EncryptUpdate(space_for_test+96, space_for_test+608);

	SM2EncryptUpdate(space_for_test+96+128, space_for_test+608+128);

	Data.pd = space_for_test+96+128+128;
	Data.len = 127;

	pC3 = space_for_test + 576;
	pC2 = space_for_test + 608 + 128 +128;
	SM2EncryptFinal(&Data, pC2, pC3);


	//
	PriKey_A.d = space_for_test;

	SM2DecryptInit(&PriKey_A, &Point);

	SM2DecryptUpdate(space_for_test+608, space_for_test+608);

	SM2DecryptUpdate(space_for_test+608+128, space_for_test+608+128);

	Data.pd = pC2;
	Data.len = 127;

	m1 = pC2;

	SM2DecryptFinal(&Data, pC3, m1);



	//
	while (1);
}
