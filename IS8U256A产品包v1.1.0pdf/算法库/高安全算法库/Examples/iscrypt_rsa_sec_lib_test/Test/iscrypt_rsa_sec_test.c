#include <string.h>

#include "iscrypt_rsa2048_sec.h"

unsigned char xdata space_for_test[1536];

RSAKEYCTX xdata RSAKey;
RSAPUBLICKEYCTX xdata RSAPubKey;
RSAPRIVATEKEYCRT xdata RSAPriKeyCRT;

unsigned char code RSA_PLAINTEXT[256] = 
{
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,	\
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11
};

unsigned char code RSA1024_CIPHERTEXT[128] =
{
	0X9B,0X80,0XE6,0X84,0X2E,0X9B,0X5C,0X83,0X24,0X01,0X2F,0XD6,0X27,0XB5,0XC4,0XBE,
	0XD4,0XA8,0X82,0XF7,0X8A,0XAE,0X86,0XCA,0XF9,0X3C,0X15,0XD1,0XCD,0XD0,0X57,0X20,
	0X96,0X40,0XF6,0X0E,0X6F,0X14,0XFD,0XC7,0X91,0X10,0XEC,0X87,0X67,0XA7,0X47,0X93,
	0X1D,0X64,0XF9,0XEA,0XB2,0XFE,0XC7,0X48,0X46,0X03,0X1B,0X16,0X9E,0X98,0X22,0XBE,
	0X3E,0XCD,0XCF,0X6E,0X8B,0XC9,0X5E,0X1B,0X81,0X09,0XF9,0X71,0XE3,0XF5,0XE5,0X5E,
	0XCF,0X87,0XB6,0XBE,0X8D,0XDC,0X7C,0XE8,0X9C,0X9B,0X0E,0XEA,0X94,0X3F,0X25,0X23,
	0X14,0X5D,0XFA,0X61,0XFA,0XA4,0XAB,0XF1,0X3F,0X7B,0X05,0XA3,0XAA,0X71,0X84,0X11,
	0X30,0XA9,0X69,0X15,0X0B,0XD9,0XEB,0X1F,0XFB,0X68,0X39,0XA5,0X1C,0X08,0X2B,0XA8
};

unsigned char code RSA2048_CIPHERTEXT[256] =
{
	0X5F,0X2B,0X76,0X3E,0XA1,0X0A,0X13,0X7B,0XFA,0XB9,0XFA,0XA3,0X26,0X57,0X5E,0X33,
	0XC7,0X53,0X88,0X97,0X0D,0X84,0X48,0X2B,0XD3,0X01,0X61,0XB5,0X1D,0XAF,0XA8,0X10,
	0X06,0X6E,0X93,0X85,0X30,0X16,0XA7,0XF8,0XEB,0X84,0XFA,0X33,0X42,0X3D,0XF2,0X32,
	0X69,0XB0,0XC1,0X4C,0X3B,0XF7,0X0E,0X5A,0XDD,0X62,0X01,0X35,0X9F,0X70,0X73,0X9D,
	0XD2,0X73,0XC4,0X3F,0X7B,0X83,0X60,0X3B,0X07,0X3F,0XF9,0X3F,0X33,0X8A,0X1F,0X09,
	0XA2,0X84,0X3D,0X8C,0X1F,0X4D,0XAD,0XBE,0X0F,0X49,0XFB,0XA0,0XDA,0X44,0XD4,0XC1,
	0X16,0X29,0XF5,0XD2,0XCB,0X2C,0XE2,0XAE,0X88,0X42,0X4B,0X37,0X86,0X2E,0X5B,0XAE,
	0X00,0X49,0XB3,0XAF,0X94,0X04,0X11,0X46,0X7C,0XDD,0X38,0XEA,0XCB,0XB3,0XF5,0X40,
	0X43,0XEB,0X69,0XC5,0X38,0X84,0XFE,0X67,0X58,0XA3,0X47,0X81,0X38,0X2E,0X37,0XAB,
	0XE9,0XDF,0X01,0XC1,0X9D,0X54,0XF4,0XC3,0X4C,0X5D,0X7F,0X97,0X6B,0X55,0X1A,0X66,
	0XC0,0X0D,0X29,0X6A,0X91,0XFC,0XA2,0X93,0X1E,0X14,0X4F,0X48,0XA6,0X67,0X71,0XAF,
	0XC7,0X2D,0X3D,0XC3,0XF2,0X0F,0XAB,0X07,0X2B,0X00,0XA8,0X90,0X58,0XF5,0X77,0XDC,
	0X27,0X50,0XE2,0X4F,0X5F,0X5D,0X22,0X7D,0X70,0X3B,0X2D,0X78,0X10,0X95,0X5C,0XD7,
	0X44,0XBC,0X9B,0X04,0X05,0X5B,0X3D,0XB2,0XC7,0X05,0X33,0XA0,0XD0,0XE2,0X6B,0X1F,
	0XA6,0X57,0X51,0X93,0X77,0X48,0XA7,0X66,0X61,0X3E,0X98,0XD8,0X16,0X67,0XBE,0XE9,
	0X95,0XB8,0XD3,0X4A,0X7C,0XCC,0X9D,0XF7,0XC7,0X34,0X86,0X47,0XB3,0XE0,0X41,0X5D
};

///////////////////////////////////////////////////////////
unsigned char code RSA1024_PUB_KEY_N[128] =
{
	0XAD,0X95,0XDB,0X00,0X8C,0X43,0XBA,0X10,0XBC,0XF4,0X07,0X1D,0XF5,0X1A,0X73,0X74,
	0X53,0X0E,0XD9,0XEA,0X34,0XDD,0XFB,0XAF,0X83,0X4E,0X43,0X27,0XCF,0X19,0XD1,0XCB,
	0X51,0X14,0X85,0X0C,0XC3,0X6E,0X45,0XF1,0XF8,0X40,0XE7,0XAC,0X97,0XF7,0XC3,0X1B,
	0XEC,0X7F,0X2A,0X2C,0X58,0X6C,0X27,0XB0,0X8E,0X11,0X5C,0XDF,0XE0,0XD9,0X0F,0X95,
	0XC4,0XC4,0X91,0X81,0X9A,0X0D,0XB5,0X65,0X60,0XDE,0X3E,0X3F,0X03,0X0E,0X28,0X4A,
	0X60,0XA6,0X14,0XC1,0XD0,0XEC,0XB7,0X89,0X44,0XCE,0X7D,0XE1,0X80,0XB3,0X70,0X77,
	0X4E,0X37,0X93,0XCD,0X4A,0X46,0XF0,0XFE,0XE4,0XB0,0X1B,0XC5,0X78,0XD9,0XEF,0X42,
	0X0E,0XB1,0X57,0XA0,0XCB,0X3F,0X26,0XCB,0XF4,0X0C,0XF9,0XEB,0XAE,0X93,0XF7,0X81
};

unsigned char code RSA1024_PRI_KEY_D[128] =
{
	0X9E,0X94,0XA8,0XDE,0X77,0X45,0XE8,0X56,0X22,0X49,0X4D,0XB7,0X30,0X94,0X59,0XA5,
	0X8B,0XBB,0XA5,0X99,0X31,0X73,0X1A,0XDB,0XDD,0X39,0X42,0X60,0XBB,0XF2,0XFA,0X96,
	0XA4,0X1B,0XFA,0XF1,0X0E,0X19,0X50,0X0D,0X1E,0X9F,0X2D,0X07,0XA0,0X4D,0XD9,0X11,
	0X49,0X9D,0X63,0X09,0XE0,0X3D,0XEE,0X84,0X7D,0X45,0X9F,0X73,0X68,0X16,0XE5,0X04,
	0X8C,0X1D,0X19,0X80,0X52,0X27,0XEF,0XC7,0XBF,0XF1,0X31,0XA7,0XE9,0XEB,0XB8,0XB6,
	0X77,0X20,0XB4,0XCE,0X2C,0X50,0X3C,0X9C,0X7D,0X55,0X67,0X3E,0X0B,0X06,0X55,0X1C,
	0X17,0X85,0X25,0XA0,0X1D,0X37,0X8B,0X6D,0X14,0X31,0XED,0X3D,0X02,0XEA,0XD8,0X79,
	0X0F,0XA0,0X4D,0X69,0X80,0X00,0X97,0X5A,0XC5,0XDF,0X98,0X96,0X9D,0X16,0XBD,0X81
};

unsigned char code RSA1024_PRI_KEY_P[64] =
{
	0XC5,0X5A,0X4E,0X7F,0X0D,0X56,0X09,0X1F,0X40,0X7F,0X71,0X6E,0X7F,0X1E,0X5F,0X5A,
	0X23,0X7E,0X1D,0X7B,0X5C,0X7F,0X71,0X7C,0X16,0X7F,0X02,0X47,0X2B,0X7F,0X67,0X6E,
	0X05,0X6B,0X3D,0X18,0X10,0X76,0X0C,0X7F,0X01,0X7F,0X07,0X4F,0X71,0X37,0X4C,0X77,
	0X61,0X7F,0X28,0X3B,0X7E,0X36,0X7A,0X54,0X3E,0X76,0X3E,0X7B,0X66,0X63,0X72,0X43
};

unsigned char code RSA1024_PRI_KEY_Q[64] =
{
	0XE1,0X2B,0X6F,0X5A,0X34,0X6E,0X0D,0X7D,0X56,0X2C,0X3C,0X7E,0X4D,0X65,0X71,0X7F,
	0X6D,0X5B,0X39,0X6F,0X5C,0X5A,0X37,0X7E,0X5C,0X7B,0X1C,0X4A,0X13,0X3C,0X1B,0X7F,
	0X4F,0X7F,0X51,0X7C,0X6E,0X64,0X7D,0X73,0X4D,0X19,0X44,0X26,0X31,0X0F,0X4B,0X7B,
	0X02,0X77,0X6E,0X6E,0X23,0X1F,0X49,0X6D,0X0C,0X7F,0X34,0X6F,0X18,0X3E,0X5C,0XEB
};

unsigned char code RSA1024_PRI_KEY_DP[64] =
{
	0XBE,0X1B,0X87,0X00,0X16,0XBD,0XA9,0X1D,0XE4,0XC8,0X9F,0X61,0X3C,0XAC,0XEA,0X57,
	0X6F,0X57,0X3E,0X59,0X26,0X3A,0X51,0XFC,0XA1,0XC3,0X09,0X53,0XBB,0X90,0X07,0XF7,
	0X50,0XDB,0X03,0XC8,0X19,0X9B,0X4D,0XE0,0X4E,0X75,0XAA,0X7A,0X19,0X6A,0X96,0X8B,
	0X6D,0X6C,0XCB,0X39,0XBC,0X14,0X08,0X74,0XFC,0X92,0X75,0X0F,0XF4,0X0A,0X99,0XF7
};

unsigned char code RSA1024_PRI_KEY_DQ[64] =
{
	0X7A,0X4F,0X4C,0XB2,0X34,0X0E,0X9F,0XB7,0X38,0X6A,0XD9,0X05,0X46,0X67,0X57,0X2A,
	0X7F,0XAD,0X70,0XDA,0X63,0XD1,0X01,0X99,0XDB,0X04,0X68,0X8E,0X78,0X3A,0X4B,0X39,
	0X71,0X66,0X58,0X4D,0XFD,0XED,0X0A,0X13,0XEA,0X8A,0X51,0XF1,0X68,0XEE,0XC4,0XF2,
	0X71,0X99,0X8C,0X5B,0XB9,0X2A,0X52,0X89,0X30,0XA3,0X9C,0X48,0XC8,0X63,0X7F,0XB7
};

unsigned char code RSA1024_PRI_KEY_QINV[64] =
{
	0X0D,0X16,0X81,0XF3,0XA2,0X24,0XF2,0X86,0XEC,0XAA,0XF1,0XF8,0X26,0X77,0X75,0XAD,
	0X58,0X2F,0XA4,0XBD,0X02,0X27,0X37,0X88,0X9C,0X08,0X20,0XB1,0X12,0X91,0X93,0XC3,
	0X65,0X5A,0X5D,0XAF,0X74,0XBB,0XAD,0XB1,0X3B,0XCF,0X6E,0XF5,0XFC,0XAE,0X12,0X05,
	0XB5,0X0D,0X5E,0X82,0X43,0XE0,0XC1,0XE7,0X33,0XB3,0X3D,0X40,0X0D,0X99,0XE7,0X29
};
        
///////////////////////////////////////////////////////////
unsigned char code RSA2048_PUB_KEY_N[256] =
{
	0XB3,0X05,0XE4,0XAD,0X9B,0X9D,0X92,0X3E,0X9E,0XD2,0XF7,0X2B,0X3C,0X41,0X9A,0XB2,
	0X75,0X9B,0X1E,0X14,0XF1,0X1C,0X38,0X97,0XDF,0X91,0X73,0X3C,0X05,0X6E,0X24,0XC6,
	0X88,0X48,0XD7,0X9C,0XD4,0XDA,0X1B,0X4F,0X5B,0X82,0XFC,0X5D,0XD5,0XE1,0X44,0XA6,
	0XDF,0X6B,0XBE,0XBC,0X03,0X53,0X70,0X4C,0X04,0X6C,0XB5,0XDD,0X78,0X29,0X59,0XC2,
	0XCC,0X0D,0X91,0X47,0X3F,0X9F,0X87,0XC2,0XC4,0X66,0X64,0XEA,0X16,0XA8,0X2B,0X0B,
	0X29,0X59,0XBE,0X6F,0X2D,0XCA,0XB7,0XA3,0X46,0X68,0X78,0X9B,0X85,0X63,0X95,0XD2,
	0X3F,0X3D,0XEB,0X7E,0XCB,0XDE,0XCE,0XF4,0X54,0X31,0X3A,0X71,0X2C,0X52,0XFC,0XA4,
	0X60,0X3C,0X44,0X06,0XCA,0X3A,0X5F,0X7A,0X74,0XDF,0XFF,0XB0,0X65,0X5B,0X5E,0X8B,
	0XF0,0X11,0XB4,0XDC,0XBD,0X9D,0X64,0X69,0X41,0X50,0XEE,0X59,0XC1,0XCA,0X1A,0XE2,
	0XC2,0X27,0X92,0XBD,0XFA,0X23,0X01,0XE1,0X91,0X26,0XCE,0XF3,0X4B,0X8A,0XFA,0XB6,
	0X26,0X04,0X38,0XA6,0XA2,0X15,0XD7,0X53,0XE9,0X51,0XDA,0XEC,0XE8,0X2D,0X1E,0X17,
	0XDF,0XC2,0X8C,0XA3,0X57,0XD6,0X89,0XBB,0X24,0X32,0XB0,0X6F,0XF2,0X54,0X89,0XAA,
	0X9D,0XCE,0XE3,0XCE,0XCC,0X43,0X04,0X35,0X3C,0XE2,0XE2,0X83,0X20,0X79,0X99,0X0B,
	0XE0,0X45,0XB1,0XDD,0X7F,0XEE,0X73,0X96,0XC3,0XE9,0X1B,0X4D,0XC7,0X02,0X79,0X96,
	0XF1,0X7D,0XD4,0X64,0X27,0X93,0XBD,0X4E,0XCC,0X83,0X3E,0X51,0X16,0X9C,0X0A,0XBC,
	0X88,0XA5,0X2D,0XD2,0XB5,0X30,0XDA,0X2A,0XE9,0X60,0X57,0X8E,0X2F,0X2A,0XA0,0XF1
};

unsigned char code RSA2048_PRI_KEY_D[256] =
{
	0X63,0X3F,0X98,0X28,0XBB,0X46,0X1F,0X26,0XC2,0X4C,0X79,0X25,0X2A,0X11,0XC0,0XDE,
	0XC1,0X1E,0X8F,0X0D,0XD3,0X21,0XEF,0X2A,0X1B,0X92,0XFA,0X8C,0XC3,0X01,0XEE,0X37,
	0X76,0XA4,0XD3,0X8C,0X29,0XE1,0X05,0X14,0XF8,0XC9,0XE4,0X79,0X6D,0X32,0XA7,0X29,
	0XD0,0X61,0X5E,0X6B,0XC3,0X78,0X45,0XA0,0X8F,0X2F,0X69,0X9F,0XEF,0X97,0X15,0X21,
	0X4E,0X99,0X12,0XFA,0XAA,0X06,0X1A,0X70,0XDB,0X0B,0X5D,0X54,0XFD,0XDC,0X9B,0X88,
	0X63,0X93,0X52,0X65,0X36,0XC0,0XD5,0X10,0X1A,0XDF,0X9E,0X45,0XB2,0X2C,0XA4,0X89,
	0XDB,0XEF,0XCB,0X18,0X0F,0X94,0X65,0XAD,0XC4,0XE3,0X49,0XE0,0X26,0X4F,0X97,0XAA,
	0XD5,0X83,0X73,0XBF,0X43,0XEC,0X1A,0XB4,0XBC,0X08,0XD7,0X2B,0X06,0XF6,0X21,0XB2,
	0X8A,0XEC,0X74,0XD8,0X0C,0XCF,0X9B,0XF7,0X63,0X3F,0XCE,0X0C,0X56,0X47,0XD1,0X5F,
	0X74,0X23,0X76,0X7F,0XA1,0X2C,0XDB,0X05,0X52,0XE8,0X67,0X3D,0X5F,0X72,0X28,0X31,
	0X06,0XDB,0X7B,0XA0,0X00,0X3B,0X0A,0X68,0X49,0X2B,0X68,0X26,0XD4,0XAB,0XA0,0X8D,
	0XB2,0X69,0X76,0X74,0X32,0XE7,0X92,0X3C,0X9E,0X95,0X73,0X82,0XF9,0X41,0XDD,0X3A,
	0XD4,0X42,0XBB,0XC3,0X1D,0X24,0XED,0XEF,0XD4,0XBA,0X7A,0XD4,0X9E,0X61,0X8B,0X69,
	0XCA,0X23,0X43,0X01,0X21,0XD0,0XC9,0X9D,0XB7,0X4A,0X46,0X90,0X6A,0X60,0XCD,0X10,
	0X22,0X36,0X4D,0X50,0XEC,0X25,0XD6,0X8C,0X71,0XF6,0XC8,0X4C,0X40,0XE0,0X0E,0XBD,
	0XE6,0XBF,0X87,0X9B,0XB0,0XB3,0X68,0X26,0XBC,0X08,0X0E,0XED,0XBA,0X23,0X6E,0X65
};

unsigned char code RSA2048_PRI_KEY_P[128] =
{
	0XC5,0X59,0X4D,0X6F,0X38,0X3F,0X7D,0X5B,0X78,0X1B,0X28,0X77,0X37,0X76,0X06,0X5A,
	0X50,0X6E,0X10,0X28,0X47,0X4D,0X5C,0X7F,0X15,0X3A,0X57,0X7F,0X10,0X7F,0X23,0X7E,
	0X11,0X7F,0X7C,0X2B,0X4A,0X56,0X0E,0X39,0X09,0X6D,0X68,0X4E,0X06,0X6D,0X05,0X3F,
	0X1B,0X7F,0X5A,0X76,0X38,0X3F,0X10,0X7F,0X2F,0X6D,0X6D,0X3D,0X3E,0X7F,0X5E,0X78,
	0X69,0X7F,0X38,0X5D,0X76,0X1B,0X46,0X3B,0X43,0X75,0X61,0X1B,0X1F,0X5F,0X08,0X3F,
	0X24,0X4E,0X42,0X3F,0X04,0X3D,0X2A,0X7E,0X26,0X3E,0X5F,0X1F,0X44,0X2B,0X53,0X6F,
	0X6C,0X7D,0X5C,0X3E,0X31,0X5B,0X4D,0X3E,0X28,0X64,0X28,0X4F,0X02,0X75,0X3D,0X77,
	0X34,0X23,0X11,0X6D,0X71,0X35,0X2D,0X57,0X6E,0X7D,0X77,0X5F,0X79,0X7D,0X65,0XAB
};

unsigned char code RSA2048_PRI_KEY_Q[128] =
{
	0XE8,0X3A,0X53,0X5F,0X1B,0X7F,0X39,0X6F,0X59,0X7B,0X35,0X66,0X63,0X7D,0X7A,0X3F,
	0X07,0X6E,0X24,0X6C,0X16,0X6B,0X1C,0X2F,0X5A,0X2B,0X25,0X6F,0X11,0X75,0X18,0X6F,
	0X59,0X1F,0X06,0X57,0X48,0X5E,0X1A,0X6F,0X15,0X63,0X25,0X3F,0X5E,0X4E,0X22,0X6F,
	0X19,0X57,0X4E,0X59,0X2A,0X3F,0X2C,0X43,0X57,0X6F,0X2E,0X7E,0X7D,0X7D,0X10,0X1B,
	0X4D,0X35,0X24,0X3F,0X12,0X4D,0X75,0X5B,0X0E,0X3B,0X72,0X7D,0X44,0X78,0X04,0X6F,
	0X6F,0X64,0X15,0X56,0X33,0X3F,0X2C,0X6E,0X03,0X67,0X3C,0X6D,0X4C,0X3F,0X3A,0X7F,
	0X17,0X6F,0X38,0X7E,0X64,0X5F,0X0B,0X69,0X6C,0X5F,0X54,0X37,0X68,0X7F,0X0C,0X3F,
	0X68,0X77,0X62,0X6E,0X3D,0X6A,0X65,0X5F,0X4C,0X5D,0X06,0X3B,0X66,0X20,0X7F,0XD3
};

unsigned char code RSA2048_PRI_KEY_DP[128] =
{
	0X40,0X15,0X24,0X88,0XE6,0X09,0XEF,0XC9,0XE0,0XF1,0X68,0XAD,0X75,0XAB,0XF4,0X9A,
	0X25,0X1D,0XE8,0X4F,0X3C,0X00,0X09,0XF6,0X16,0X4D,0X90,0X95,0XE9,0X24,0X6F,0XC1,
	0X03,0X2B,0X93,0X85,0X77,0X29,0X04,0X8B,0X4E,0XDD,0X61,0X0E,0X5D,0X15,0XCF,0XAB,
	0X53,0X61,0X82,0X5D,0X7B,0X1C,0X37,0X5E,0X25,0X67,0X72,0X1E,0X7E,0X09,0XDC,0X02,
	0X5B,0XB7,0X7C,0XF5,0X14,0X61,0XFC,0XE7,0X47,0X9B,0X79,0X01,0XD6,0XA9,0X04,0X43,
	0X84,0XA5,0X88,0XEB,0X6F,0X93,0XF1,0X15,0X6F,0X93,0XB7,0X4D,0XAE,0XD4,0X26,0XCE,
	0XBA,0XBA,0XE6,0X56,0X27,0XAE,0XCF,0X21,0X4C,0XFA,0X61,0X00,0X6E,0XFA,0XE5,0X0F,
	0XAD,0X35,0X69,0XF6,0X50,0XD9,0X84,0XB4,0XAC,0X63,0X3F,0X7D,0X18,0X35,0X38,0XEB
};

unsigned char code RSA2048_PRI_KEY_DQ[128] =
{
	0XD4,0XDA,0X28,0XF2,0X82,0X7C,0X81,0X03,0X4B,0X8B,0XFF,0XAD,0X02,0X41,0XCF,0X5B,
	0X98,0X0E,0XDF,0X39,0X66,0XEE,0XF3,0XDD,0X7F,0X13,0X0E,0XF3,0X97,0X97,0XB1,0X36,
	0XD6,0X03,0XF6,0XC6,0XE7,0XA0,0XC1,0X2F,0XD1,0XF5,0X96,0XFD,0X57,0X0D,0XDC,0XC7,
	0XE1,0XFD,0X40,0XE5,0XBF,0X30,0X39,0XFC,0XDB,0X56,0X1F,0XD2,0X76,0X68,0XBB,0XEB,
	0X9A,0X3F,0XBC,0X22,0X47,0X3F,0X51,0XF2,0X8C,0XBF,0XF6,0X37,0X55,0X1B,0X80,0X4D,
	0X37,0X57,0X0F,0XAB,0X7B,0XBB,0X4A,0X98,0XE7,0X6B,0XA7,0X5A,0X32,0XC9,0XBD,0X6F,
	0X21,0XE6,0XA2,0X6C,0X4E,0XC9,0X42,0XE7,0X75,0X1A,0X87,0X51,0X65,0XE9,0X15,0X2B,
	0XC5,0X2F,0XAF,0XBB,0X85,0X75,0X50,0XC7,0X21,0X72,0X1E,0X35,0X31,0X6D,0X56,0X5B
};

unsigned char code RSA2048_PRI_KEY_QINV[128] =
{
	0XAC,0X68,0XFC,0X7F,0X43,0XE5,0X06,0XF5,0XC7,0X2C,0XEE,0X8A,0X29,0X3E,0XD1,0X76,
	0XAF,0X5A,0XD1,0XDC,0XC1,0X0B,0XEB,0XE5,0XB6,0X80,0X3B,0XFA,0XA0,0X97,0X8C,0XC8,
	0XEA,0X1A,0X6B,0X39,0XDB,0X3E,0XD8,0X44,0X72,0X82,0X58,0XBC,0X7C,0X59,0XDC,0X3F,
	0X60,0XCB,0X72,0XCF,0XCE,0XF3,0X10,0XAA,0XCE,0XAB,0X35,0X1C,0X1A,0XC9,0X44,0XBB,
	0XFF,0X0B,0X7A,0XFA,0X31,0X66,0XD3,0XC9,0X85,0X1F,0X60,0X71,0X68,0XEE,0X64,0X8C,
	0X88,0X7F,0XA5,0X30,0XD1,0X3F,0XFC,0X70,0X4D,0X28,0X4B,0XE7,0XB7,0X5E,0X21,0X7A,
	0X90,0XCF,0X82,0X47,0X84,0XA8,0X41,0XCC,0XF8,0X61,0X99,0XEE,0X0F,0XAB,0X00,0XA0,
	0X2F,0X9F,0X58,0X8D,0X85,0X7C,0X12,0X86,0X4A,0XBC,0X8B,0X67,0XAB,0X73,0X75,0X11
};

///////////////////////////////////////////////////////////

unsigned char RSA1024_DECRYPT_SEC_TEST()
{
	unsigned char xdata ret;

	memcpy(space_for_test, RSA1024_PRI_KEY_P, 64);
	memcpy(space_for_test+128, RSA1024_PRI_KEY_Q, 64);
	memcpy(space_for_test+256, RSA1024_PRI_KEY_DP, 64);
	memcpy(space_for_test+384, RSA1024_PRI_KEY_DQ, 64);
	memcpy(space_for_test+512, RSA1024_PRI_KEY_QINV, 64);
	memcpy(space_for_test+640, RSA1024_CIPHERTEXT, 128);

	memcpy(space_for_test+768, RSA1024_PUB_KEY_N, 128);

	space_for_test[896] = 0x00;
	space_for_test[897] = 0x01;
	space_for_test[898] = 0x00;
	space_for_test[899] = 0x01;

	RSAPriKeyCRT.p = space_for_test;
	RSAPriKeyCRT.q = space_for_test+128;
	RSAPriKeyCRT.dP = space_for_test+256;
	RSAPriKeyCRT.dQ = space_for_test+384;
	RSAPriKeyCRT.qInv = space_for_test+512;

	RSAPubKey.e = space_for_test+896;
	RSAPubKey.n = space_for_test+768;

	RSAKey.pRSAPubKey = &RSAPubKey;
	RSAKey.pRSAPriKey = &RSAPriKeyCRT;

	ret = RSADecryptSEC(RSA1024|CRT_TYPE, &RSAKey, space_for_test+640);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+640, RSA_PLAINTEXT, 128);
	
	if (0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}

unsigned char RSA2048_DECRYPT_SEC_TEST()
{
	unsigned char xdata ret;

	memcpy(space_for_test, RSA2048_PRI_KEY_P, 128);
	memcpy(space_for_test+128, RSA2048_PRI_KEY_Q, 128);
	memcpy(space_for_test+256, RSA2048_PRI_KEY_DP, 128);
	memcpy(space_for_test+384, RSA2048_PRI_KEY_DQ, 128);
	memcpy(space_for_test+512, RSA2048_PRI_KEY_QINV, 128);
	memcpy(space_for_test+640, RSA2048_CIPHERTEXT, 256);

	memcpy(space_for_test+896, RSA2048_PUB_KEY_N, 256);

	space_for_test[1152] = 0x00;
	space_for_test[1153] = 0x01;
	space_for_test[1154] = 0x00;
	space_for_test[1155] = 0x01;

	RSAPriKeyCRT.p = space_for_test;
	RSAPriKeyCRT.q = space_for_test+128;
	RSAPriKeyCRT.dP = space_for_test+256;
	RSAPriKeyCRT.dQ = space_for_test+384;
	RSAPriKeyCRT.qInv = space_for_test+512;

	RSAPubKey.e = space_for_test+1152;
	RSAPubKey.n = space_for_test+896;

	RSAKey.pRSAPubKey = &RSAPubKey;
	RSAKey.pRSAPriKey = &RSAPriKeyCRT;

	ret = RSADecryptSEC(RSA2048|CRT_TYPE, &RSAKey, space_for_test+640);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+640, RSA_PLAINTEXT, 256);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}

unsigned char RSA1024_SIGN_SEC_TEST()
{
	unsigned char xdata ret;

	memcpy(space_for_test, RSA1024_PRI_KEY_P, 64);
	memcpy(space_for_test+128, RSA1024_PRI_KEY_Q, 64);
	memcpy(space_for_test+256, RSA1024_PRI_KEY_DP, 64);
	memcpy(space_for_test+384, RSA1024_PRI_KEY_DQ, 64);
	memcpy(space_for_test+512, RSA1024_PRI_KEY_QINV, 64);
	memcpy(space_for_test+640, RSA1024_CIPHERTEXT, 128);

	memcpy(space_for_test+768, RSA1024_PUB_KEY_N, 128);
	space_for_test[896] = 0x00;
	space_for_test[897] = 0x01;
	space_for_test[898] = 0x00;
	space_for_test[899] = 0x01;

	RSAPriKeyCRT.p = space_for_test;
	RSAPriKeyCRT.q = space_for_test+128;
	RSAPriKeyCRT.dP = space_for_test+256;
	RSAPriKeyCRT.dQ = space_for_test+384;
	RSAPriKeyCRT.qInv = space_for_test+512;

	RSAPubKey.e = space_for_test+896;
	RSAPubKey.n = space_for_test+768;

	RSAKey.pRSAPubKey = &RSAPubKey;
	RSAKey.pRSAPriKey = &RSAPriKeyCRT;

	ret = RSASignSEC(RSA1024|CRT_TYPE, &RSAKey, space_for_test+640);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+640, RSA_PLAINTEXT, 128);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}

unsigned char RSA2048_SIGN_SEC_TEST()
{
	unsigned char xdata ret;

	memcpy(space_for_test, RSA2048_PRI_KEY_P, 128);
	memcpy(space_for_test+128, RSA2048_PRI_KEY_Q, 128);
	memcpy(space_for_test+256, RSA2048_PRI_KEY_DP, 128);
	memcpy(space_for_test+384, RSA2048_PRI_KEY_DQ, 128);
	memcpy(space_for_test+512, RSA2048_PRI_KEY_QINV, 128);
	memcpy(space_for_test+640, RSA2048_CIPHERTEXT, 256);

	memcpy(space_for_test+896, RSA2048_PUB_KEY_N, 256);

	space_for_test[1152] = 0x00;
	space_for_test[1153] = 0x01;
	space_for_test[1154] = 0x00;
	space_for_test[1155] = 0x01;

	RSAPriKeyCRT.p = space_for_test;
	RSAPriKeyCRT.q = space_for_test+128;
	RSAPriKeyCRT.dP = space_for_test+256;
	RSAPriKeyCRT.dQ = space_for_test+384;
	RSAPriKeyCRT.qInv = space_for_test+512;

	RSAPubKey.e = space_for_test+1152;
	RSAPubKey.n = space_for_test+896;

	RSAKey.pRSAPubKey = &RSAPubKey;
	RSAKey.pRSAPriKey = &RSAPriKeyCRT;

	ret = RSASignSEC(RSA2048|CRT_TYPE, &RSAKey, space_for_test+640);

	if (SUCCESS != ret)
	{
		goto ErrorExit;
	}

	ret = memcmp(space_for_test+640, RSA_PLAINTEXT, 256);

	if (0 != ret)
	{
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	return 1;
}

