/****************************************************************\
* Copyright (C) 2005-2011 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:			iscrypt_random_sec.h
* Author:				PeiChao
* Version:				1.0.0.0
* Date:					2014.05.21
* Description:
*
* Others:
*
* Function List:
*						1.	RNG_StartupTest
*						1.	GenRandomSEC
*
* History:
*
*   1. Date:
*      Author:
*      Modification:
*
*   2. ......
\****************************************************************/
#ifndef	__IS_RANDOM_S_H__
#define __IS_RANDOM_S_H__

#include "iscrypt.h"

unsigned char RNG_StartupTest( void );

unsigned char GenRandomSEC(
	unsigned short bRandomLen,		// in
	unsigned char xdata *pbRandom	// out
);

#endif

