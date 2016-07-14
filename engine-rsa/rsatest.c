#include <stdio.h> 
#include <openssl/bio.h> 
#include <openssl/engine.h> 
#include <openssl/rsa.h> 
#include <openssl/ssl.h>
#include <openssl/err.h>

BIO *bio_err = NULL;
BIO *bio_stdout = NULL;

/* Try to load an engine in a shareable library */
static ENGINE *try_load_engine(BIO *err, const char *engine)
{
    ENGINE *e = ENGINE_by_id("dynamic");
    if (e) {
        if (!ENGINE_ctrl_cmd_string(e, "SO_PATH", engine, 0)
            || !ENGINE_ctrl_cmd_string(e, "LOAD", NULL, 0)) {
            ENGINE_free(e);
            e = NULL;
        }
    }
    return e;
}

ENGINE *setup_engine(BIO *err, const char *engine)
{
    ENGINE *e = NULL;

	ENGINE_load_builtin_engines();

    if (engine) {
        if ((e = ENGINE_by_id(engine)) == NULL
            && (e = try_load_engine(err, engine)) == NULL) {
            BIO_printf(err, "invalid engine \"%s\"\n", engine);
            ERR_print_errors(err);
            return NULL;
        }
		if(!ENGINE_init(e)) {
			/* the engine couldn't initialise, release 'e' */
			ENGINE_free(e);
			return NULL;
		}
        if (!ENGINE_set_default(e, ENGINE_METHOD_RSA)) {
            BIO_printf(err, "can't use that engine\n");
            ERR_print_errors(err);
            ENGINE_free(e);
            return NULL;
        }

        BIO_printf(err, "engine \"%s\" set.\n", ENGINE_get_id(e));
		ENGINE_finish(e);
        /* Free our "structural" reference. */
        ENGINE_free(e);
    }
	
    return e;
}

char *test_engine(unsigned char*str,char *path_key)
{
    char *p_en;
    RSA *p_rsa;
    FILE *file;
    int flen,rsa_len;
    if((file=fopen(path_key,"r"))==NULL){
        perror("open key file error");
        return NULL;    
    }   
/*
    if((p_rsa=PEM_read_RSA_PUBKEY(file,NULL,NULL,NULL))==NULL){
        ERR_print_errors_fp(stdout);
        return NULL;
    }   
*/
    flen=strlen(str);
    rsa_len=RSA_size(p_rsa);
    p_en=(unsigned char *)malloc(rsa_len+1);
    memset(p_en,0,rsa_len+1);
    if(RSA_public_encrypt(rsa_len,(unsigned char *)str,(unsigned char*)p_en,p_rsa,RSA_NO_PADDING)<0){
        return NULL;
    }
    RSA_free(p_rsa);
    fclose(file);
    return p_en;
	return 0;
}

int main(int argc, char *argv[])
{
    unsigned char *buf;
    unsigned char bufin[1024]={0};
    const char *engine = "rsa";
    RSA *p_rsa=RSA_new();
    ENGINE *e = NULL;
    bio_err = BIO_new_fp(stderr, BIO_NOCLOSE | BIO_FP_TEXT);
    bio_stdout = BIO_new_fp(stdout, BIO_NOCLOSE | BIO_FP_TEXT);

    setup_engine(bio_err, engine);
//   ERR_load_crypto_strings();
//    OpenSSL_add_all_algorithms();
	/**/
	//for testing
	/**/
    printf("\nmain test ssh\n");
    e = ENGINE_by_id(engine);
    printf("engine id :%s,name:%s\n",ENGINE_get_id(e),ENGINE_get_name(e));
    p_rsa->meth = ENGINE_get_RSA(e);
    RSA_public_encrypt(128,(unsigned char*)bufin,(unsigned char*)buf,p_rsa,RSA_PKCS1_OAEP_PADDING);
//    buf = test_engine(bufin,"test_pub.key");
    RSA_free(p_rsa);
    if (bio_err != NULL)
        BIO_free(bio_err);

    return 0;
}

