#include <stdio.h>
#include <string.h>
#include <openssl/engine.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/opensslconf.h>

#include <fcntl.h>
#include "is8u256a.h"
#define DEVICE	"/dev/spidev1.1"

static int RSA_is8_public_encrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding)
{
	int ret=0;
	int fd;
	unsigned char tmp[256]={0};
	memcpy(tmp,from,256);
	fd = open(DEVICE,O_RDWR);
	if(fd<0) {
		printf("D:open device  failed!\n");
		exit(1);
	}

	printf("\ntest test test\n");
	ret += RSA2048_load_text(fd,tmp);
	ret += RSA2048_Encrypt(fd);
	ret += RSA2048_export_result(fd,to);

	close(fd);
	if(ret==0)
		return 1;
	return 0;
}

static int RSA_is8_public_decrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding)
{
	return 1;
}

static int RSA_is8_private_encrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding)
{
	return 1;
}

static int RSA_is8_private_decrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding)
{
	int ret=0;
	int fd;
	unsigned char tmp[256]={0};
	memcpy(tmp,from,256);
	fd = open(DEVICE,O_RDWR);
	if(fd<0) {
		printf("D:open device  failed!\n");
		exit(1);
	}
	
	ret += RSA2048_load_text(fd,tmp);
	ret += RSA2048_Decrypt_CRT(fd);
	ret += RSA2048_export_result(fd,to);

	close(fd);
	if(ret==0)
		return 1;
	return 0;
}

static int RSA_is8_sign(int type, const unsigned char *m, unsigned int m_length, unsigned char *sigret, unsigned int *siglen, const RSA *rsa)
{
	int ret=0;
	int fd;
	unsigned char tmp[256]={0};
	unsigned char *digest;

	MD5(m, m_length, digest);
	memcpy(tmp,digest,MD5_DIGEST_LENGTH);
	fd = open(DEVICE,O_RDWR);
	if(fd<0) {
		printf("D:open device  failed!\n");
		exit(1);
	}
	
	ret += RSA2048_load_text(fd,tmp);
	ret += RSA2048_Sign_CRT(fd);
	ret += RSA2048_export_result(fd,sigret);

	close(fd);
	if(ret==0)
		return 1;
	return 0;
}

static int RSA_is8_verify(int dtype, const unsigned char *m, unsigned int m_length, const unsigned char *sigbuf, unsigned int siglen, const RSA *rsa)
{
	int ret=0;
	int fd;
	unsigned char tmp[256]={0};
	unsigned char *digest;

	MD5(m, m_length, digest);
	memcpy(tmp,digest,MD5_DIGEST_LENGTH);

	fd = open(DEVICE,O_RDWR);
	if(fd<0) {
		printf("D:open device  failed!\n");
		exit(1);
	}
	
	ret += RSA2048_load_text(fd,tmp);
	ret += RSA2048_load_signature(fd,sigbuf);
	ret += RSA2048_Verify(fd);
	
	close(fd);
	if(ret==0)
		return 1;
	return 0;
}
                       
static int RSA_is8_init(RSA *rsa)
{
	return 1;
}

static int RSA_is8_finish(RSA *rsa)
{
	return 1;
}

static RSA_METHOD rsa_meth = {
	"External IS8U256A",
	RSA_is8_public_encrypt,
	NULL,
	NULL,
	RSA_is8_private_decrypt,
	NULL,
	NULL,
	RSA_is8_init,
	RSA_is8_finish,
	0,
	NULL,
	RSA_is8_sign,
	RSA_is8_verify,
	NULL
};

static int rsa_init(ENGINE *e)
{
	return 1;
}

static const char *engine_e_rsa_id = "rsa";
static const char *engine_e_rsa_name = "External IS8U256A";

static int bind_helper(ENGINE *e,const char *id)
{
	if (!ENGINE_set_id(e, engine_e_rsa_id) ||
		!ENGINE_set_name(e, engine_e_rsa_name) ||
		!ENGINE_set_flags(e, ENGINE_METHOD_RSA) ||
		!ENGINE_set_init_function(e, rsa_init) ||
		!ENGINE_set_RSA(e, &rsa_meth)) {
		return 0;
	}

	return 1;
}

static ENGINE *ENGINE_rsa(void)
{
	ENGINE *ret = ENGINE_new();
	if (!ret)
		return NULL;
	if (!bind_helper(ret, engine_e_rsa_id)) {
		ENGINE_free(ret);
		return NULL;
	}
	return ret;
}

void ENGINE_load_rsa(void)
{
	ENGINE *toadd = ENGINE_rsa();
	if (!toadd)
		return;
	ENGINE_add(toadd);
	ENGINE_free(toadd);
	ERR_clear_error();
}

IMPLEMENT_DYNAMIC_BIND_FN(bind_helper)
IMPLEMENT_DYNAMIC_CHECK_FN()
