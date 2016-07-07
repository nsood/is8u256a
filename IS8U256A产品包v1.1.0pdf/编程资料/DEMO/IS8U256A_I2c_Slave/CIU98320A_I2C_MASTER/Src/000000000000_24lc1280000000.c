/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*文件名称：CIU98320A_24lc128.c
*作    者：李宪法
*版    本：V1.0.0
*日    期：2012.09.14
*功能描述：
*			完成I2C从设备24LC128芯片的各种操作
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
#include "CIU98320A.h"
#include "CIU98320A_typesmacro.h"
#include "CIU98320A_i2c_master.h"

/***************************************************\
*函数名称：ByteWrite
*函数功能：24LC128完成写一字节
*输入参数：
*			1、UINT16 address；数据的目的地址
*			2、UINT8 data；待写入的一字节数据
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void ByteWrite(UINT16 address,UINT8 data)
{
	UINT8 addr_h;
	UINT8 addr_l;
	addr_h = (address>>8)&0xFF;
	addr_l = address&0xFF;

	I2CTransmitData(0x30,0xA0);

	I2CTransmitData(0x31,addr_h);

	I2CTransmitData(0x31,addr_l);

	I2CTransmitData(0x31,data);
	I2CGenerateStop();

	I2CBusStatCheck();
}

/***************************************************\
*函数名称：RandomRead
*函数功能：24LC128完成读一字节
*输入参数：
*			1、UINT16 address；待读取数据的地址
*输出参数：无
*返 回 值：读取结果
*其它说明：
\***************************************************/
UINT8 RandomRead(UINT16 address)
{
	UINT8 addr_h;
	UINT8 addr_l;
	UINT8 datatmp;

	addr_h = (address>>8)&0xFF;
	addr_l = address&0xFF;

	I2CTransmitData(0x30,0xA0);

	I2CTransmitData(0x31,addr_h);

	I2CTransmitData(0x31,addr_l);

	I2CTransmitData(0x25,0xA1);

	datatmp = I2CReceiveData(0x21);
	I2CGenerateStop();

	return datatmp;
}

/***************************************************\
*函数名称：PageWrite
*函数功能：24LC128完成写64字节
*输入参数：
*			1、UINT16 address；待写入数据的目的地址
*			2、UINT8 *pData；待写入数据的源地址
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void PageWrite(UINT16 address,UINT8 *pData)
{
	UINT8 addr_l=0x0;
	UINT8 addr_h=0x0;
	UINT8 i=0x0;
	
	addr_l = (UINT8)(address&&0xFF);
	addr_h = (UINT8)((address>>8)&&0xFF);

	I2CTransmitData(0x30,0xA0);

	I2CTransmitData(0x31,addr_h);

	I2CTransmitData(0x31,addr_l);
	
	for(i=0;i<64;i++)
	{
		I2CTransmitData(0x31,*(pData+i));
	}

	I2CGenerateStop();

	I2CBusStatCheck();
}

/***************************************************\
*函数名称：SequentialRead
*函数功能：24LC128完成写连续读取bytelen字节
*输入参数：
*			1、UINT16 address；待读取数据的源地址
*			2、UINT8 *pData；待读取数据的目的地址
*			3、UINT8 bytelen；待读取数据的长度
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void SequentialRead(UINT8 *pData,UINT16 address,UINT8 bytelen)
{
	UINT8 addr_l=0x0;
	UINT8 addr_h=0x0;
	UINT8 datatmp=0x0;
	UINT8 i=0x0;
	
	addr_l = (UINT8)(address&&0xFF);
	addr_h = (UINT8)((address>>8)&&0xFF);

	I2CTransmitData(0x30,0xA0);

	I2CTransmitData(0x31,addr_h);

	I2CTransmitData(0x31,addr_l);

	I2CTransmitData(0x25,0xA1);

	for(i=0;i<bytelen;i++)
	{
		datatmp = I2CReceiveData(0x21);
		*(pData+i) = datatmp;
		datatmp = 0x0;
	}

	I2CGenerateStop();

	I2CBusStatCheck();
}
