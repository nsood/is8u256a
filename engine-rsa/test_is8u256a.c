#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#include "key_prase.h"
#include "is8u256a.h"

#define DEVICE	"/dev/spidev1.1"

#define DEBUG

#ifdef DEBUG
#define debug(format,args...) \
	printf(format,## args)
#else
#define debug(format,...) \
	do { } while (0)
#endif

#define SUCCESS	0
#define FAILED	1

struct RSA2048_key {
	unsigned char *RSA2048_E;
	unsigned char *RSA2048_N;
	unsigned char *RSA2048_D;
	unsigned char *RSA2048_P;
	unsigned char *RSA2048_Q;
	unsigned char *RSA2048_dP;
	unsigned char *RSA2048_dQ;
	unsigned char *RSA2048_qInv;
};

unsigned char buffer_in[1024];
unsigned char buffer_out[1024];

unsigned char RSA2048_E[4] = {0};
unsigned char RSA2048_N[256] = {0};
unsigned char RSA2048_D[256] = {0};
unsigned char RSA2048_P[128] = {0};
unsigned char RSA2048_Q[128] = {0};
unsigned char RSA2048_dP[128] = {0};
unsigned char RSA2048_dQ[128] = {0};
unsigned char RSA2048_qInv[128] = {0};

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
	0x7f,0x4f,0xcb,0x6f,0x13,0xa0,0xf2,0x99,0xbc,0x62,0x1d,0xcd,0xd9,0x50,0x43,0xd6,
	0x62,0x83,0x93,0xc3,0x2b,0x1e,0x61,0x49,0x4f,0x4e,0xa6,0xda,0x1c,0x16,0xd9,0x20,
	0x68,0x9e,0x95,0x27,0x83,0x3f,0x62,0x3a,0x23,0x96,0xd2,0x0b,0x35,0x10,0x80,0xc5,
	0xc3,0x17,0xd0,0x26,0x3d,0xd2,0x46,0xe8,0xb2,0x7e,0x24,0xd1,0xa2,0x70,0x43,0xd4,
	0xfe,0x60,0x9f,0x7a,0x1c,0xd4,0x34,0xc9,0xd3,0x0c,0x0f,0xe7,0x01,0xa8,0x29,0x85,
	0xd5,0x4d,0xf1,0xfe,0x82,0xb5,0x30,0x37,0x69,0xfe,0x91,0x93,0x37,0x51,0x07,0xf3,
	0xbe,0x82,0xb1,0xc9,0xde,0xd5,0x45,0x9b,0xe5,0xee,0xda,0xd2,0xd1,0xad,0x05,0xc9,
	0x53,0x97,0x42,0xc4,0xb0,0x73,0xf5,0x42,0x4c,0x05,0x57,0x7d,0xda,0xf1,0x46,0x33,
	0x06,0x15,0x38,0x4f,0x69,0xae,0x1a,0x4e,0x4d,0x6d,0xa2,0x1d,0x13,0xd8,0x9d,0x3b,
	0x90,0x1a,0x80,0x48,0xca,0x3c,0x8a,0x6c,0x6e,0x52,0x04,0x0b,0x26,0xda,0x4e,0x69,
	0x5c,0xa2,0x81,0xe7,0xce,0xd3,0xb3,0x90,0xd7,0xe7,0x2c,0x1f,0x1d,0x79,0xbc,0xb5,
	0x7b,0x30,0x67,0x08,0x72,0x17,0xdb,0x9b,0xe6,0x7f,0x51,0x19,0x31,0xff,0x63,0x60,
	0xb7,0x19,0xe0,0x44,0xdd,0xb1,0xc3,0xaf,0x43,0x03,0x65,0xaf,0x34,0x8b,0xa5,0x68,
	0x84,0x4b,0xa8,0x99,0x8e,0xcc,0xdb,0xdb,0x68,0x39,0x22,0x16,0x5d,0x9b,0xca,0x00,
	0x1c,0x6c,0x8d,0xf0,0x6a,0x6f,0x83,0xd2,0x9e,0xd9,0x7a,0xcc,0xfa,0x2a,0x51,0xd3,
	0x12,0x7d,0xa7,0x19,0x9d,0xb0,0x85,0xae,0xc2,0x1b,0x2c,0xf1,0x68,0xcf,0xdd,0x16
};

int main(int argc, char **argv)
{
	int ret=0;
	int fd;
	unsigned char CipherText[256] = {0};
	unsigned char PlainText[256] = {0};

	struct RSA2048_key *RSA2048_key_t;
	RSA2048_key_t = (struct RSA2048_key*)malloc(sizeof(struct RSA2048_key));
	RSA2048_key_t->RSA2048_E = RSA2048_E;
	RSA2048_key_t->RSA2048_N = RSA2048_N;
	RSA2048_key_t->RSA2048_D = RSA2048_D;
	RSA2048_key_t->RSA2048_P = RSA2048_P;
	RSA2048_key_t->RSA2048_Q = RSA2048_Q;
	RSA2048_key_t->RSA2048_dP = RSA2048_dP;
	RSA2048_key_t->RSA2048_dQ = RSA2048_dQ;
	RSA2048_key_t->RSA2048_qInv = RSA2048_qInv;
	
//	ret += import_RSA2048_key(RSA2048_key_t);
	ret += import_RSA2048_pubkey(RSA2048_key_t);

	if (access("id_rsa.txt",0)!=-1)
		system("rm id_rsa.txt");
	if (access("id_rsa.pub.pem",0)!=-1)
		system("rm id_rsa.pub.pem");
	if (access("id_rsa.pub.txt",0)!=-1)
		system("rm id_rsa.pub.txt");
	
	fd = open(DEVICE,O_RDWR);

	if(fd<0)
	{
		printf("D:open device  failed!\n");
		exit(1);
	}

	//check
	ret += init_check(fd);
	//init
	ret += init_mode(fd);
	//func

	ret += RSA2048_load_pubkey_E(fd,RSA2048_key_t->RSA2048_E);
	ret += RSA2048_load_pubkey_N(fd,RSA2048_key_t->RSA2048_N);
/*
	ret += RSA2048_load_pubkey_E(fd,RSA2048_key_t->RSA2048_E);
	ret += RSA2048_load_pubkey_N(fd,RSA2048_key_t->RSA2048_N);
	ret += RSA2048_load_prikey_D(fd,RSA2048_key_t->RSA2048_D);
	ret += RSA2048_load_prikey_P(fd,RSA2048_key_t->RSA2048_P);
	ret += RSA2048_load_prikey_Q(fd,RSA2048_key_t->RSA2048_Q);
	ret += RSA2048_load_prikey_dP(fd,RSA2048_key_t->RSA2048_dP);
	ret += RSA2048_load_prikey_dQ(fd,RSA2048_key_t->RSA2048_dQ);
	ret += RSA2048_load_prikey_qInv(fd,RSA2048_key_t->RSA2048_qInv);
*/
	ret += RSA2048_load_text(fd,RSA2048_PlainText);
	ret += RSA2048_Encrypt(fd);
	ret += RSA2048_export_result(fd,CipherText);

	ret += memcmp(CipherText,RSA2048_CipherText,256);
	if(ret!=0) printf("Encrypt failed!\n");
/*
	ret += RSA2048_load_text(fd,RSA2048_CipherText);
	ret += RSA2048_Decrypt_CRT(fd);
	ret += RSA2048_export_result(fd,PlainText);

	ret += memcmp(PlainText,RSA2048_PlainText,256);
	if(ret!=0) printf("Decrypt failed!\n");
*/
	if (ret != SUCCESS) {
		printf("ERR:Some action failed!\n");
	}
	else {
		printf("ALL actoin success!\n");
	}
	free(RSA2048_key_t);
	close(fd);
	return SUCCESS;
}



