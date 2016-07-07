/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_random.h
* Author:		PeiChao
* Version:		1.0.0.131112
* Date:			2013.11.12
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. GenRandom
*				2. GetFactoryCode
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_RANDOM_H__
#define __IS_RANDOM_H__

#include "iscrypt.h"

void GenRandom(
	unsigned short bRandomLen,		// in
	unsigned char xdata *pbRandom	// out
);

void GetFactoryCode(
	unsigned char xdata *pbFtyCode	// out
);

#endif
