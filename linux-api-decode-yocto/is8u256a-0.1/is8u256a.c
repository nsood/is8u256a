#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define DEVICE	"/dev/spidev1.1"
#define SUCCESS		0
#define FAILED		-1
#define SEND_TO_MACHINE		0XC1
#define RECV_TO_MACHINE		0XA1
#define LEN_SIZE		1
#define CMD_SIZE		5
#define LEN_OFF		0
#define CMD_OFF		LEN_SIZE
#define DAT_OFF		CMD_OFF+CMD_SIZE

#define DEBUG

#ifdef DEBUG
#define debug(format,args...) \
	printf(format,## args)
#else
#define debug(format,...) \
	do { } while (0)
#endif

struct transfer_s{
	unsigned int rece_len;
	unsigned int send_len;
	unsigned char *rece_buf;
	unsigned char *send_buf;
};

unsigned char buffer_in[1024];
unsigned char buffer_out[1024];

unsigned char RSA2048_E[4]={0x00,0x01,0x00,0x01};

unsigned char RSA2048_PlainText[256] = 
{
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,
	0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11,0X11
};

unsigned char RSA2048_CipherText[256] =
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

unsigned char RSA2048_N[256] =
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

unsigned char RSA2048_D[256] =
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

unsigned char RSA2048_P[128] =
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

unsigned char RSA2048_Q[128] =
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

unsigned char RSA2048_dP[128] =
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

unsigned char RSA2048_dQ[128] =
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

unsigned char RSA2048_qInv[128] =
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

void str_to_hex(unsigned char* dest, unsigned char* src, int len)
{
	unsigned char h1,h2,s1,s2;
	int i;
	//debug("\nstr_to_hex:");
	for ( i=0; i<len; i++ ) {
		h1 = src[ 2*i ];
		h2 = src[ 2*i + 1];

		s1 = toupper(h1) - 0x30;
		if ( s1 > 9 )  s1 -= 7;
		s2 = toupper(h2) - 0x30;
		if ( s2 > 9 )  s2 -= 7;

		dest[i] = s1*16 + s2;
		debug("%02x ",dest[i]);
	}
	//debug("\n");
}

unsigned char get_xor(unsigned char* src,unsigned char len)
{	
	int i;
	unsigned char result;

	result = src[0];
	for(i=1; i<len; i++ ) {
		result ^= src[i];
	}
	return result;
}

int spi_transfer(int fd, struct transfer_s *transfer_t)
{
	int ret;
	int i;

	for(i=0,ret=0;i<transfer_t->send_len;i++) {
		ret += write(fd, transfer_t->send_buf+i,1);
		debug("%02x ",transfer_t->send_buf[i]);
		usleep(10);
	}
	
	//ret = write(fd, transfer_t->send_buf,transfer_t->send_len);
	if (ret !=transfer_t->send_len)
		return FAILED;
	debug("\n");

	for(i=0,ret=0;i<transfer_t->rece_len;i++) {
		ret += read(fd, transfer_t->rece_buf+i,1);
		debug("%02x ",transfer_t->rece_buf[i]);
		usleep(10);
	}
	//ret = read(fd, transfer_t->rece_buf, transfer_t->rece_len);
	if (ret !=transfer_t->rece_len)
		return FAILED;
	debug("\n");

	return SUCCESS;
}

int init_check(int fd)
{
	int ret;
	unsigned char Check[] = {0xFB,0x33,0x44,0x55,0x66,0xBF};
	unsigned char RECV[10];
	
	memset(&RECV[0],10,0);
	write(fd, &Check[0], 6);
	usleep(1000*200);
	read(fd,&RECV[0],4);
	debug("init_check:recv : %02x %02x %02x %02x \n",RECV[0],RECV[1],RECV[2],RECV[3]);
	if ( RECV[0] == 0xFF && RECV[1] == 0xFF )
		return FAILED;
	return SUCCESS;
}

int init_mode(int fd)
{
	int ret;
	unsigned char INIT[] =  {0xFB,0x00,0X44,0XFF,0X66,0X26};
	unsigned char RECV[10];
	
	memset(&RECV[0],10,0);	
	write(fd, &INIT[0], 6);
	usleep(1000*200);
	read(fd,&RECV[0],3);
	debug("init_mode:recv : %02x %02x %02x \n",RECV[0],RECV[1],RECV[2]);
	if ( RECV[0] == 0x90 && RECV[1] == 0x00 )
		return SUCCESS;
	return FAILED;
}

int check_status(int fd)
{
	int ret;
	unsigned char CHECK[] = {0xE5};
	unsigned char RECV[10];
	write(fd, &CHECK[0], 1);
	usleep(10);
	read(fd,&RECV[0],1);
	debug("Check status : %02x\n",RECV[0]);
	if (RECV[0]==0x01)
		return SUCCESS;
	return 1;
}

void check_status_loop(int fd)
{
	do {
		debug("Check machine status...");
		usleep(1000*100);
	}while(check_status(fd));
}

void change_status(int fd,unsigned char status)
{
	write(fd, &status, 1);
	usleep(10);
}

int RSA2048_load(int fd,unsigned char* cmd, unsigned char* src, int src_len)
{
	int ret;
	struct transfer_s *transfer_t;
	transfer_t = malloc(sizeof(struct transfer_s));
	transfer_t->send_buf = buffer_out;
	transfer_t->rece_buf = buffer_in;

	memset(buffer_out ,0x0,sizeof(buffer_out));
	str_to_hex(buffer_out+LEN_SIZE,cmd, CMD_SIZE);
	memcpy(buffer_out+DAT_OFF,src,src_len);
	buffer_out[LEN_OFF] = CMD_SIZE + src_len+1;		//len include length of cmd and data and Xor
	buffer_out[buffer_out[LEN_OFF]] = get_xor(buffer_out,buffer_out[LEN_OFF]);
	transfer_t->send_len = buffer_out[LEN_OFF] + 1;		//send include 1(len)+len(data+xor)
	transfer_t->rece_len = 0;
	
	check_status_loop(fd);
	change_status(fd,SEND_TO_MACHINE);
	if(spi_transfer(fd,transfer_t)!=SUCCESS)
		printf("ERR:spi_transfer failed!\n");

	memset(buffer_in ,0x0,sizeof(buffer_in));
	transfer_t->send_len = 0;
	transfer_t->rece_len = 4;							//receive four return data expect {0x03,0x90,0x00,0x90}

	check_status_loop(fd);
	change_status(fd, RECV_TO_MACHINE);
	if(spi_transfer(fd,transfer_t)!=SUCCESS)
		printf("ERR:spi_transfer failed!\n");

	if ( buffer_in[1] != 0x90 ) {
		free(transfer_t);
		return FAILED;
	}
	free(transfer_t);
	return SUCCESS;	
}

int RSA2048_execute(int fd,unsigned char* cmd)
{
	int ret;
	struct transfer_s *transfer_t;
	transfer_t = malloc(sizeof(struct transfer_s));
	transfer_t->send_buf = buffer_out;
	transfer_t->rece_buf = buffer_in;

	memset(buffer_out ,0x0,sizeof(buffer_out));
	str_to_hex(buffer_out+LEN_SIZE,cmd, CMD_SIZE);
	buffer_out[LEN_OFF] = CMD_SIZE+1;				//len include length of cmd  and Xor
	buffer_out[buffer_out[LEN_OFF]] = get_xor(buffer_out,buffer_out[LEN_OFF]);
	transfer_t->send_len = buffer_out[LEN_OFF] + 1;		//send include 1(len)+len(xor)
	transfer_t->rece_len = 0;
	
	check_status_loop(fd);
	change_status(fd,SEND_TO_MACHINE);
	if(spi_transfer(fd,transfer_t)!=SUCCESS)
		printf("ERR:spi_transfer failed!\n");

	memset(buffer_in ,0x0,sizeof(buffer_in));
	transfer_t->send_len = 0;
	transfer_t->rece_len = 4;							//receive four return data expect {0x03,0x90,0x00,0x90}

	check_status_loop(fd);
	change_status(fd, RECV_TO_MACHINE);
	if(spi_transfer(fd,transfer_t)!=SUCCESS)
		printf("ERR:spi_transfer failed!\n");

	if ( buffer_in[1] != 0x90 ) {
		free(transfer_t);
		return FAILED;
	}
	free(transfer_t);
	return SUCCESS;	
}

int RSA2048_export(int fd,unsigned char* cmd, unsigned char* dest, int dest_len)
{
	int ret;
	struct transfer_s *transfer_t;
	transfer_t = malloc(sizeof(struct transfer_s));
	transfer_t->send_buf = buffer_out;
	transfer_t->rece_buf = buffer_in;

	if(dest_len > 128) {
		printf("ERR:dest_len is too long!\n");
		dest_len = 128;
	}

	memset(buffer_out ,0x0,sizeof(buffer_out));
	str_to_hex(buffer_out+LEN_SIZE,cmd, CMD_SIZE);
	buffer_out[LEN_OFF] = CMD_SIZE + 1;				//len include length of cmd and Xor
	buffer_out[buffer_out[LEN_OFF]] = get_xor(buffer_out,buffer_out[LEN_OFF]);
	transfer_t->send_len = buffer_out[LEN_OFF] + 1;		//send include 1(len)+len(data+xor)
	transfer_t->rece_len = 0;
	
	check_status_loop(fd);
	change_status(fd,SEND_TO_MACHINE);
	if(spi_transfer(fd,transfer_t)!=SUCCESS)
		printf("ERR:spi_transfer failed!\n");

	memset(buffer_in ,0x0,sizeof(buffer_in));
	transfer_t->send_len = 0;
	transfer_t->rece_len = 4 + dest_len;

	check_status_loop(fd);
	change_status(fd, RECV_TO_MACHINE);
	if(spi_transfer(fd,transfer_t)!=SUCCESS)
		printf("ERR:spi_transfer failed!\n");

	if ( buffer_in[0x81]!=0x90 || buffer_in[0]!=(dest_len+3) ) {
		free(transfer_t);							//should received (dest_len*byte + 90 00 + xor)
		return FAILED;
	}
	memcpy(dest,buffer_in+1,dest_len);				//ingore the first 'len + 90 00' byte
	
	free(transfer_t);
	return SUCCESS;	
}

int RSA2048_load_pubkey_E(int fd,unsigned char* RSA2048_E)
{

	int ret;
	ret = RSA2048_load(fd,"BF51000004", RSA2048_E, 4);
	if (ret != SUCCESS)
		return FAILED;
	return SUCCESS;
}

int RSA2048_load_pubkey_N(int fd,unsigned char* RSA2048_N)
{
	//pubkey_N == prikey_N
	int ret;
	//load first 128 bytes key
	ret = RSA2048_load(fd,"BF51000480", RSA2048_N, 128);
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_load_pubkey_N_128 failed!\n");
		return FAILED;
	}
	ret = RSA2048_load(fd,"BF51008480", RSA2048_N+128, 128);
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_load_pubkey_N_256 failed!\n");
		return FAILED;
	}
	return SUCCESS;
}

int RSA2048_load_prikey_D(int fd,unsigned char* RSA2048_D)
{
	int ret;
	//load first 128 bytes key
	ret = RSA2048_load(fd,"BF51010480", RSA2048_D, 128);
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_load_prikey_D_128 failed!\n");
		return FAILED;
	}
	ret = RSA2048_load(fd,"BF51018480", RSA2048_D+128, 128);
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_load_prikey_D_256 failed!\n");
		return FAILED;
	}
	return SUCCESS;
}

int RSA2048_load_prikey_P(int fd,unsigned char* RSA2048_P)
{

	int ret;
	ret = RSA2048_load(fd,"BF51010480", RSA2048_P, 128);
	if (ret != SUCCESS)
		return FAILED;
	return SUCCESS;
}

int RSA2048_load_prikey_Q(int fd,unsigned char* RSA2048_Q)
{

	int ret;
	ret = RSA2048_load(fd,"BF51018480", RSA2048_Q, 128);
	if (ret != SUCCESS)
		return FAILED;
	return SUCCESS;
}

int RSA2048_load_prikey_dP(int fd,unsigned char* RSA2048_dP)
{

	int ret;
	ret = RSA2048_load(fd,"BF51020480", RSA2048_dP, 128);
	if (ret != SUCCESS)
		return FAILED;
	return SUCCESS;
}

int RSA2048_load_prikey_dQ(int fd,unsigned char* RSA2048_dQ)
{

	int ret;
	ret = RSA2048_load(fd,"BF51028480", RSA2048_dQ, 128);
	if (ret != SUCCESS)
		return FAILED;
	return SUCCESS;
}

int RSA2048_load_prikey_qInv(int fd,unsigned char* RSA2048_qInv)
{

	int ret;
	ret = RSA2048_load(fd,"BF51030480", RSA2048_qInv, 128);
	if (ret != SUCCESS)
		return FAILED;
	return SUCCESS;
}

int RSA2048_Encrypt(int fd)
{	
	int ret;
	ret = RSA2048_execute(fd,"BF11C00000");
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_Encrypt failed!\n");
		return FAILED;
	}
}

int RSA2048_Decrypt_STD(int fd)
{	
	int ret;
	ret = RSA2048_execute(fd,"BF12C00000");
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_Decrypt_STD failed!\n");
		return FAILED;
	}
}

int RSA2048_Decrypt_CRT(int fd)
{	
	int ret;
	ret = RSA2048_execute(fd,"BF12C08000");
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_Decrypt_CRT failed!\n");
		return FAILED;
	}
}

int RSA2048_load_text(int fd,unsigned char* text)
{
	//RSA2048_load_text : load plain text or cipher text
	int ret;
	//load first 128 bytes key
	ret = RSA2048_load(fd,"BF50000080", text, 128);
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_load_text_128 failed!\n");
		return FAILED;
	}
	ret = RSA2048_load(fd,"BF50008080", text+128, 128);
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_load_text_256 failed!\n");
		return FAILED;
	}
	return SUCCESS;
}

int RSA2048_export_result(int fd,unsigned char*dest)
{
	//RSA2048_export_result used for get the result of Encrypt or Decrypt 
	int ret;
	ret = RSA2048_export(fd,"BF52000080",dest,128);
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_export_result_128 failed!\n");
		return FAILED;
	}
	ret = RSA2048_export(fd,"BF52008080",dest+128,128);
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_export_result_256 failed!\n");
		return FAILED;
	}
	return SUCCESS;
}

int RSA2048_generate_key_STD(int fd)
{
	int ret;
	ret = RSA2048_execute(fd, "BF10C00000");
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_generate_key_STD failed!\n");
		return FAILED;
	}
	return SUCCESS;		
}

int RSA2048_generate_key_CRT(int fd)
{
	int ret;
	ret = RSA2048_execute(fd, "BF10C08000");
	if (ret != SUCCESS) {
		debug("ERR:RSA2048_generate_key_CRT failed!\n");
		return FAILED;
	}
	return SUCCESS;		
}


int main(int argc, char **argv)
{
	int ret;
	int fd;
	unsigned char CipherText[256] = {0};
	unsigned char PlainText[256] = {0};
	fd = open(DEVICE,O_RDWR);

	if(fd<0)
	{
		printf("D:open device  failed!\n");
		exit(1);
	}

	//check
	ret = init_check(fd);
	//init
	ret = init_mode(fd);
	//func

	ret = RSA2048_load_pubkey_E(fd,RSA2048_E);
	ret = RSA2048_load_pubkey_N(fd,RSA2048_N);
	ret = RSA2048_load_prikey_D(fd,RSA2048_D);
	ret = RSA2048_load_prikey_P(fd,RSA2048_P);
	ret = RSA2048_load_prikey_Q(fd,RSA2048_Q);
	ret = RSA2048_load_prikey_dP(fd,RSA2048_dP);
	ret = RSA2048_load_prikey_dQ(fd,RSA2048_dQ);
	ret = RSA2048_load_prikey_qInv(fd,RSA2048_qInv);

	ret = RSA2048_load_text(fd,RSA2048_PlainText);
	ret = RSA2048_Encrypt(fd);
	ret = RSA2048_export_result(fd,CipherText);

	ret = memcmp(CipherText,RSA2048_CipherText,256);
	if(ret!=0) printf("Encrypt failed!\n");

	ret = RSA2048_load_text(fd,RSA2048_CipherText);
	ret = RSA2048_Decrypt_CRT(fd);
	ret = RSA2048_export_result(fd,PlainText);

	ret = memcmp(PlainText,RSA2048_PlainText,256);
	if(ret!=0) printf("Decrypt failed!\n");

	if (ret != SUCCESS) {
		printf("ERR:Some action failed!\n");
	}
	else {
		printf("ALL actoin success!\n");
	}
	close(fd);
	return SUCCESS;
}



