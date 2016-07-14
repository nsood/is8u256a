#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#include "key_prase.h"

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

#define SEND_TO_MACHINE		0XC1
#define RECV_TO_MACHINE		0XA1
#define LEN_SIZE		1
#define CMD_SIZE		5
#define LEN_OFF		0
#define CMD_OFF		LEN_SIZE
#define DAT_OFF		CMD_OFF+CMD_SIZE

struct transfer_s{
	unsigned int rece_len;
	unsigned int send_len;
	unsigned char *rece_buf;
	unsigned char *send_buf;
};

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
	
	ret += export_RSA2048_key(RSA2048_key_t);
	
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
	ret += RSA2048_load_prikey_D(fd,RSA2048_key_t->RSA2048_D);
	ret += RSA2048_load_prikey_P(fd,RSA2048_key_t->RSA2048_P);
	ret += RSA2048_load_prikey_Q(fd,RSA2048_key_t->RSA2048_Q);
	ret += RSA2048_load_prikey_dP(fd,RSA2048_key_t->RSA2048_dP);
	ret += RSA2048_load_prikey_dQ(fd,RSA2048_key_t->RSA2048_dQ);
	ret += RSA2048_load_prikey_qInv(fd,RSA2048_key_t->RSA2048_qInv);

	ret += RSA2048_load_text(fd,RSA2048_PlainText);
	ret += RSA2048_Encrypt(fd);
	ret += RSA2048_export_result(fd,CipherText);

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
	free(RSA2048_key_t);
	close(fd);
	return SUCCESS;
}



