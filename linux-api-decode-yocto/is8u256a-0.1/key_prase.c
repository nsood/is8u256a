
/* 
 * File:   key_prase.c
 * Author: jli@acorn-net.com
 *
 * Created on 2016-07-06
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define DEBUG

#ifdef DEBUG
#define debug(format,args...) \
	printf(format,## args)
#else
#define debug(format,...) \
	do { } while (0)
#endif

#define KEY_TYPES	8
#define SUCCESS	0
#define FAILED	1
#define FILENAME	"id_rsa.txt"

#define RSA_KEY_N	0
#define RSA_KEY_E	1
#define RSA_KEY_D	2
#define RSA_KEY_P	3
#define RSA_KEY_Q	4
#define RSA_KEY_dP	5
#define RSA_KEY_dQ	6
#define RSA_KEY_qInv	7

FILE *fp;
char key_name[][20]={	
	"modulus:",
        "publicExponent:",
        "privateExponent:",
        "prime1:",
        "prime2:",
        "exponent1:",
        "exponent2:",
        "coefficient:"
    };
int file_length;
int key_name_len[KEY_TYPES] = {0};
int key_off[KEY_TYPES] = {0};
int key_name_off[KEY_TYPES+1] = {0};

unsigned char RSA2048_E[4] = {0};
unsigned char RSA2048_N[256] = {0};
unsigned char RSA2048_D[256] = {0};
unsigned char RSA2048_P[128] = {0};
unsigned char RSA2048_Q[128] = {0};
unsigned char RSA2048_dP[128] = {0};
unsigned char RSA2048_dQ[128] = {0};
unsigned char RSA2048_qInv[128] = {0};

void get_key_length()
{
	int i;
	for(i=0; i<KEY_TYPES; i++) {
		key_name_len[i] = strlen(key_name[i]);
		debug("%s length : %d\n",key_name[i],key_name_len[i]);
	}
	key_name_off[i] = file_length;
}

void get_key_offset()
{
	char c;
	int off = 0;
	int key_name_get = 0;
	char key_name_tmp[20]={0};

	rewind(fp);
	while(off++ < file_length) {
		c = fgetc(fp);
		//debug("%c",c);
		if( c == key_name[key_name_get][0] ) {
            	//debug("\nget key_name[%d] :%c\n",key_name_get,c);
			fseek(fp,-1,SEEK_CUR);
			fgets(key_name_tmp,key_name_len[key_name_get]+1,fp);
			if(!strcmp(key_name_tmp,key_name[key_name_get])){
				debug("%s\n",key_name_tmp);
				fseek(fp,-key_name_len[key_name_get],SEEK_CUR);
				key_name_off[key_name_get] = ftell(fp);
				fseek(fp,key_name_len[key_name_get],SEEK_CUR);
				key_off[key_name_get] = ftell(fp);
				 debug("%s name offset : %d\tkey offset : %d\n",key_name[key_name_get],key_name_off[key_name_get],key_off[key_name_get]);
				key_name_get++;
			}
			memset(key_name_tmp,0,20);
		}   
	}
}

void get_key_all()
{
	int i,j;
	char c;
	for(i=0; i<KEY_TYPES; i++) {
		if(i==1) continue;
		fseek(fp,key_off[i],SEEK_SET);
		for(j=0;j<key_name_off[i+1]-key_off[i]; j++) {
			c = fgetc(fp);
			//	if (c==0x20||c==0x3A||c==0x0A)
			//    	continue;
			debug("%c",c);
		}
		//debug("\n");
	}
}

int get_key(int key_off,int next_key_name_off,int key_len,unsigned char *key)
{
	int i,i_key;
	int flag=0; //means high byte or low byte
	char c;
	unsigned char high,low;
	unsigned char first_byte;

	fseek(fp,key_off,SEEK_SET);
	for(i_key=0,i=0; i<next_key_name_off-key_off; i++) {
		c = fgetc(fp);
#ifdef DEBUG
		if(i==0) debug("first char %c \n",c);
#endif
		if(c==0x20||c==0x3A||c==0x0A)
			continue;
			//debug("%c",c);
		if('0'<=c && c <='9') c -= '0';
		if('a'<=c && c <='f') c = c - 'a' + 10;
		if(0==flag){
			flag = 1;
			high = c;
		        //debug("\t");
		} else {
			flag = 0;
			low = c;
			if(0==(high*16+low)&&(1==i))
				continue;
			memset(key+i_key,high*16+low,1);
		        //debug("%02x\t",*(key+i_key));
		        i_key++;
		}
		//debug("high : %x\t low : %x\tkey_i : %d\n",high,low,i_key);
	}
#ifdef DEBUG
	debug("final the i_key=%d\n",i_key);
	for(i=0;i<key_len;i++) {
		debug("%02x ",*(key+i));
	}
	debug("\n");
#endif
	if(key_len == i_key)
		return SUCCESS;
	else
		return FAILED;
}

int get_RSA2048_E()
{
	int i;
	char c;
	char tmp_s[20];
	unsigned char E[4] = {0x00,0x01,0x00,0x01};
	
	fseek(fp,key_off[RSA_KEY_E]+1,SEEK_SET);
	fgets(tmp_s,6,fp);
	debug("%s\n",tmp_s);
	if(!strcmp(tmp_s,"65537"))
		memcpy(RSA2048_E, E, 4);
#ifdef DEBUG
	for(i=0;i<4;i++)
		debug("%02x ",RSA2048_E[i]);
	debug("\n");
#endif

	return SUCCESS;
}

int get_RSA2048_N()
{
	return get_key(key_off[RSA_KEY_N]+5,key_name_off[RSA_KEY_E],256,RSA2048_N);//+6 deal first 0x0A 0x20 unused bytes
}
int get_RSA2048_D()
{
	return get_key(key_off[RSA_KEY_D]+5,key_name_off[RSA_KEY_P],256,RSA2048_D);//+6 deal first 0x0A 0x20 unused bytes
}
int get_RSA2048_P()
{
	return get_key(key_off[RSA_KEY_P]+5,key_name_off[RSA_KEY_Q],128,RSA2048_P);//+6 deal first 0x0A 0x20 unused bytes
}
int get_RSA2048_Q()
{
	return get_key(key_off[RSA_KEY_Q]+5,key_name_off[RSA_KEY_dP],128,RSA2048_Q);//+6 deal first 0x0A 0x20 unused bytes
}
int get_RSA2048_dP()
{
	return get_key(key_off[RSA_KEY_dP]+5,key_name_off[RSA_KEY_dQ],128,RSA2048_dP);//+6 deal first 0x0A 0x20 unused bytes
}
int get_RSA2048_dQ()
{
	return get_key(key_off[RSA_KEY_dQ]+5,key_name_off[RSA_KEY_qInv],128,RSA2048_dQ);//+6 deal first 0x0A 0x20 unused bytes
}
int get_RSA2048_qInv()
{
	return get_key(key_off[RSA_KEY_qInv]+5,key_name_off[8],128,RSA2048_qInv);
}

int main(int argc, char **argv)
{
	int ret=0;

	system("openssl rsa -in id_rsa -noout -text > id_rsa.txt");
	if((fp = fopen(FILENAME, "rb")) == 0) {
		    printf("Can't open %s, program will to exit.", FILENAME);
	exit(1);
	}
	ret = fseek(fp,0,SEEK_END);
	file_length = ftell(fp);
	debug("file length is %d\n",file_length);
    
	get_key_length();
	get_key_offset();
#ifdef DEBUG
	get_key_all();
#endif
	ret += get_RSA2048_N();
	ret += get_RSA2048_D();
	ret += get_RSA2048_P();
	ret += get_RSA2048_Q();
	ret += get_RSA2048_dP();
	ret += get_RSA2048_dQ();
	ret += get_RSA2048_qInv();
    
	if(ret!=SUCCESS)
	    printf("Some action failed !\n");
    
	fclose(fp);
	return 0;
}

