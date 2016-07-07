/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_crypt.h
* Author:		PeiChao
* Version:		1.0.0.131112
* Date:			2013.11.12
* Description:
* 	
* Others:		
* 
* Function List:	
*   1. ......
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_CRYPT_H__
#define __IS_CRYPT_H__


/* Algorithm Type */
#define DES				0x00
#define TDES			0x01
#define AES				0x02
#define SM1				0x10
#define SSF33			0x11
#define SMS4			0x12

#define SHA1			0x20
#define SHA224			0x21
#define SHA256			0x22
#define SHA384			0x23
#define SHA512			0x24
#define MD4				0x25
#define MD5				0x26
#define SM3				0x30

#define RSA				0x40
#define DSA				0x60

#define ECC				0x80
#define SM2				0x90

#define RC4				0xC0


/* RETURN VALUE */
#define SUCCESS						0x00
#define FAIL						0x01
#define UNKNOWN_ERROR				0x02
#define NOT_SUPPORT_YET_ERROR		0x03

#define NOT_INITIALIZE_ERROR		0x04
#define OBJECT_ERROR				0x05
#define MEMORY_ERROR				0x06

#define IN_DATA_LENGTH_ERROR		0x07
#define IN_DATA_ERROR				0x08

#define HASH_OBJECT_ERROR			0x09
#define HASH_ERROR					0x0A
#define HASH_NOT_EQUAL_ERROR		0x0B
#define MESSAGE_OUT_OF_RANGE		0x0C
#define INVALID_PARA				0x0D

#define NO_ROOM						0x30



#endif
