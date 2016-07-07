/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_des_selftest.h
* Author:		LiuJingjing
* Version:		1.0.0.0
* Date:			2013.12.05
* Description:
* 	
* Others:		
* 
* Function List:	
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_SELFTEST_H__
#define __IS_SELFTEST_H__

unsigned char RNG_SelfTest( void );

unsigned char SM1_SelfTest( void );

unsigned char SM2_SelfTest( void );

unsigned char SM3_SelfTest( void );

unsigned char SM4_SelfTest( void );

unsigned char SHA256_SelfTest( void );

unsigned char RSA_SelfTest(void);

unsigned char SelfTest(void);

#endif
