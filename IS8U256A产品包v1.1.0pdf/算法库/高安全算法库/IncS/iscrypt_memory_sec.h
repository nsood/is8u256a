/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_memory_sec.h
* Author:		PeiChao
* Version:		1.0.0.0
* Date:			2014.05.09
* Description:
* 	
* Others:		
* 
* Function List:	
*   			1. memcpy_s
*				2. memcmp_s
*
* History:		
*   1. Date:	
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef	__IS_MEMORY_H__
#define __IS_MEMORY_H__

void memcpy_s(void * dst, void * src, int count);

int memcmp_s(void * dst, void * src, int count);

#endif
