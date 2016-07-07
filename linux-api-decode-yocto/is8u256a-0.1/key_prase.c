
/* 
 * File:   main.c
 * Author: jli@acorn-net.com
 *
 * Created on 2016年7月6日, 下午5:47
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

#define Debug printf("FILE: %s, LINE: %d\n",__FILE__,__LINE__)

#define KEY_TYPES   8
#define FILENAME    "id_rsa.txt"
#define SUCCESS     0
#define FAILED      1

FILE *fp;
char key_name_tmp[20]={0};
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
int key_name_get = 0;
int key_name_len[KEY_TYPES] = {0};
int key_off[KEY_TYPES] = {0};
int key_name_off[KEY_TYPES+1] = {0};

unsigned char RSA2048_E[4] = {0};
unsigned char RSA2048_N[256] = {0};
unsigned char RSA2048_D[256] = {0};
unsigned char RSA2048_P[256] = {0};
unsigned char RSA2048_Q[256] = {0};
unsigned char RSA2048_dP[256] = {0};
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
                debug("%s offset : %d\n",key_name[key_name_get],key_name_off[key_name_get]);
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
            //if (c==0x20||c==0x3A||c==0x0A)
            //    continue;
            debug("%c",c);
       }
       //debug("\n");
    }
}

int get_key(int key_off,int next_key_name_off,int key_len,unsigned char *key)
{
    int i,i_key;
    char c;
    unsigned char high,low;
    
    int flag=0; //means high byte or low byte
    
    fseek(fp,key_off,SEEK_SET);
    for(i_key=0,i=0; i<next_key_name_off-key_off; i++) {
        c = fgetc(fp);
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
            memset(key+i_key,high*16+low,1);
            //debug("%02x\t",*(key+i_key));
            i_key++;
        }
        //debug("high : %x\t low : %x\tkey_i : %d\n",high,low,i_key);
    }
    debug("final the i_key=%d\n",i_key);
    for(i=0;i<key_len;i++) {
        debug("%02x ",*(key+i));
    }
    debug("\n");
    if(key_len == i_key)
        return SUCCESS;
    else
        return FAILED;
}

int get_RSA2048_N()
{
    return get_key(key_off[0]+8,key_name_off[1],256,RSA2048_N);//+8 deal first 0x0A 0x20 0x00 unused bytes
}
int get_RSA2048_D()
{
    return get_key(key_off[2]+8,key_name_off[3],256,RSA2048_D);//+8 deal first 0x0A 0x20 0x00 unused bytes
}
int get_RSA2048_P()
{
    return get_key(key_off[3]+8,key_name_off[4],128,RSA2048_P);//+8 deal first 0x0A 0x20 0x00 unused bytes
}
int get_RSA2048_Q()
{
    return get_key(key_off[4]+8,key_name_off[5],128,RSA2048_Q);//+8 deal first 0x0A 0x20 0x00 unused bytes
}
int get_RSA2048_dP()
{
    return get_key(key_off[5]+8,key_name_off[6],128,RSA2048_dP);//+8 deal first 0x0A 0x20 0x00 unused bytes
}
int get_RSA2048_dQ()
{
    return get_key(key_off[6]+8,key_name_off[7],128,RSA2048_dQ);//+8 deal first 0x0A 0x20 0x00 unused bytes
}
int get_RSA2048_qInv()
{
    return get_key(key_off[7],key_name_off[8],128,RSA2048_qInv);
}

int main(int argc, char **argv)
{
    int ret;

    system("openssl rsa -in id_rsa -noout -text > id_rsa.txt");
    if((fp = fopen(FILENAME, "rb")) == 0) {
        printf("Can't open %s, program will to exit.", FILENAME);
        exit(1);
    }
    ret = fseek(fp,0,SEEK_END);
    file_length = ftell(fp);
    rewind(fp);
    debug("file length is %d\n",file_length);
    
    get_key_length();
    get_key_offset();
    get_key_all();
    
    ret = get_RSA2048_N();
    ret = get_RSA2048_D();
    ret = get_RSA2048_P();
    ret = get_RSA2048_Q();
    ret = get_RSA2048_dP();
    ret = get_RSA2048_dQ();
    ret = get_RSA2048_qInv();
    
    if(ret!=SUCCESS)
        printf("Some action failed !\n");
    
    //debug("\nfile offset is %d now\n",off);
    fclose(fp);
    return 0;
}

