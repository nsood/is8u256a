/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*文件名称：CIU98320A_25Q80.c
*作    者：李宪法
*版    本：V1.0.0
*日    期：2012.09.03
*功能描述：完成W25Q80的擦读写及读ID号
*函数列表：
*			1、
*			2、
*			3、
*历史记录：
*	1、 日期：
*		版本：
*		作者：
*	修改内容：
*	2、.....
\***************************************************/
#include "CIU98320A_spi.h"
#include "CIU98320A.h"

unsigned char Buff1_For_Test[8]={0x0};
unsigned char Buff2_For_Test[8]={0x0};

//UINT32 BusyCheck(void)
//{
//	unsigned short id=0x0;
//
//	Buff1_For_Test[0] = 0x05;
//
//	SPI0On();
//    SPI0TransmitData(Buff1_For_Test,Buff2_For_Test,3);
//	SPI0Off();
//
//	return id;
//}

/***************************************************\
*函数名称：SpiFlashReadID
*函数功能：Normal-mode读W25Q80的ID
*输入参数：无
*返 回 值：ID号：0x13EF
*其它说明：
\***************************************************/
UINT32 SpiFlashReadID(void)
{
	unsigned short id=0x0;

	Buff1_For_Test[0] = 0x90;

	SPI0On();
    SPI0TransmitData(Buff1_For_Test,Buff2_For_Test,6);
	SPI0Off();

	id = (Buff2_For_Test[4]<<8) | Buff2_For_Test[5];

	return id;
}


