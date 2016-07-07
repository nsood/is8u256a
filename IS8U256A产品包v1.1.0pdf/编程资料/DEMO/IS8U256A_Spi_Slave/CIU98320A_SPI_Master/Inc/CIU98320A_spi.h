/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*文件名称：CIU98320A_spi.h
*作    者：李宪法
*版    本：V1.0.0
*日    期：2012.09.03
*功能描述:
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
#ifndef __CIU98320A_SPI_H__
#define __CIU98320A_SPI_H__

#include "CIU98320A_typesmacro.h"

typedef struct
{
	UINT32 spi_interface_mode;
	UINT32 spi_data_format;
	UINT32 spi_cpol;		//从模式无效
	UINT32 spi_chap;		//从模式无效
	UINT32 spi_mode;

	UINT32 spi_data_len;

	UINT32 spi_mdiv_en;
	UINT32 spi_div;

	UINT32 spi_ovrf_int_en;
	UINT32 spi_done_int_en;
		
}SPICtrlInitTypes;

#define NORMAL_MODE			((UINT32)0x00)
#define DUALINPUT_MODE		((UINT32)0x10)
#define DUALOUTPUT_MODE		((UINT32)0x20)
#define QUADINPUT_MODE		((UINT32)0x30)
#define QUADOUTPUT_MODE		((UINT32)0x40)

#define SPI_DATA_MSB		((UINT32)0x00)
#define SPI_DATA_LSB		((UINT32)0x08)

#define SPI_CPOL_LOW		((UINT32)0x00)
#define SPI_CPOL_HIGHT		((UINT32)0x04)

#define SPI_CPAH_EVEN		((UINT32)0x00)
#define SPI_CPAH_ODD		((UINT32)0x02)

#define SPI_MODE_SLAVE		((UINT32)0x00)
#define SPI_MODE_MASTER		((UINT32)0x01)

#define SPI_DATA_1B			((UINT32)0x00)
#define SPI_DATA_2B			((UINT32)0x01)
#define SPI_DATA_3B			((UINT32)0x02)
#define SPI_DATA_4B			((UINT32)0x03)
#define SPI_DATA_5B			((UINT32)0x04)
#define SPI_DATA_6B			((UINT32)0x05)
#define SPI_DATA_7B			((UINT32)0x06)
#define SPI_DATA_8B			((UINT32)0x07)
#define SPI_DATA_9B			((UINT32)0x08)
#define SPI_DATA_10B		((UINT32)0x09)
#define SPI_DATA_11B		((UINT32)0x0A)
#define SPI_DATA_12B		((UINT32)0x0B)
#define SPI_DATA_13B		((UINT32)0x0C)
#define SPI_DATA_14B		((UINT32)0x0D)
#define SPI_DATA_15B		((UINT32)0x0E)
#define SPI_DATA_16B		((UINT32)0x0F)

#define SPI_MDIV_EN			((UINT32)0x0100)
#define SPI_MDIV_DIS		((UINT32)0xFEFF)

#define SPI_OVRF_INT_EN		((UINT32)0x02)
#define SPI_OVRF_INT_DIS	((UINT32)0x00)
#define SPI_DONE_INT_EN		((UINT32)0x01)
#define SPI_DONE_INT_DIS	((UINT32)0x00)

 void SPI0CtrlInit(SPICtrlInitTypes *spi_ctrl_struct);

 void SPI0On(void);
 void SPI0Off(void);
 void SPI0TransmitData(
						unsigned char *const ptxbuff,\
						unsigned char *const prxbuff,\
						unsigned int bytelen);

#endif

