#ifndef IS8U256A_H
#define IS8U256A_H

int init_check(int fd);
int init_mode(int fd);

int RSA2048_load_pubkey_E(int fd,unsigned char* RSA2048_E);
int RSA2048_load_pubkey_N(int fd,unsigned char* RSA2048_N);
int RSA2048_load_prikey_D(int fd,unsigned char* RSA2048_D);
int RSA2048_load_prikey_P(int fd,unsigned char* RSA2048_P);
int RSA2048_load_prikey_Q(int fd,unsigned char* RSA2048_Q);
int RSA2048_load_prikey_dP(int fd,unsigned char* RSA2048_dP);
int RSA2048_load_prikey_dQ(int fd,unsigned char* RSA2048_dQ);
int RSA2048_load_prikey_qInv(int fd,unsigned char* RSA2048_qInv);

int RSA2048_Encrypt(int fd);
int RSA2048_Decrypt_STD(int fd);
int RSA2048_Decrypt_CRT(int fd);
int RSA2048_Sign_STD(int fd);
int RSA2048_Sign_CRT(int fd);
int RSA2048_Verify(int fd);
int RSA2048_load_text(int fd,unsigned char* text);
int RSA2048_load_signature(int fd,unsigned char* text);
int RSA2048_export_result(int fd,unsigned char*dest);

#endif
