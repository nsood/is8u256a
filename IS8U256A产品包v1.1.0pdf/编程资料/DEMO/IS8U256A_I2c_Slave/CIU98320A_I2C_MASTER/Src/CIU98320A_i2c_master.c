/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*文件名称：CIU98320A_i2c_master.c
*作    者：李宪法
*版    本：V1.0.0
*日    期：2012.09.14
*功能描述：
*			CIU98320A主模式下的I2C通信
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
#include "ciu98320a.h"
#include "ciu98320a_typesmacro.h"
#include "ciu98320a_gpio.h"

#define I2C_SLAVE_FLAG					((UINT32)0x01<<21)

void I2CCtrlInit(unsigned long scl_hcnt,unsigned long scl_lcnt)
{
	UINT32 regtmp=0x0;

	// Enable GPIO-module
	regtmp = u32READ(SYS_CLK_EN);
	regtmp |= (1<<19);
	u32WRITE(SYS_CLK_EN,regtmp);
	regtmp = 0x0;

	// Enable I2C-module
	regtmp = u32READ(SYS_CLK_EN);
	regtmp |= (1<<23);
	u32WRITE(SYS_CLK_EN,regtmp);
	regtmp = 0x0;

	// GP15、16 --- I2C
	regtmp = u32READ(SYS_COMCON);
	regtmp |= (1<<3);
	u32WRITE(SYS_COMCON,regtmp);
	regtmp = 0x0;

//	u32WRITE(I2C_SCL_HCNT,scl_hcnt);
//	u32WRITE(I2C_SCL_LCNT,scl_lcnt);
	
//	u32WRITE(SYS_CLK_CFG,0x30);

//	u32WRITE(SYS_CLK_PLLEN,0x41);

}

/***************************************************\
*函数名称：I2CGenerateStart
*函数功能：I2C发送start信号，占用总线
*输入参数：无
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void I2CGenerateStart(unsigned char controlbyte)
{
	unsigned long regtmp=0x0;

	/*等待总线空闲*/
	while((((unsigned long)0x20)&(u32READ(I2C_STAT))));

	/*发送控制字节*/
	u32WRITE(I2C_TX_DATA,(unsigned long)controlbyte);

	/*配置后续数据传输方向*/
	regtmp = u32READ(I2C_CTRL);
	regtmp &= 0xFFFFFFEF;
	if(0x0==(0x01&controlbyte))
		regtmp |= (unsigned long)0x10;

	/*产生Start信号*/
	regtmp |= (unsigned long)0x20;

	/*等待I2C_SLAVE设备准备就绪*/
	while(0x0==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

	u32WRITE(I2C_CTRL,regtmp);

	/*等待本次传输完成*/
	while(0x0==(((unsigned long)0x80)&(u32READ(I2C_STAT))));

	/*等待I2C_SLAVE设备准备就绪*/
	while(I2C_SLAVE_FLAG==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

}

/***************************************************\
*函数名称：I2CGenerateReStart
*函数功能：I2C发送ReStart信号，占用总线
*输入参数：无
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void I2CGenerateReStart(unsigned char controlbyte)
{
	UINT32 regtmp=0x0;

	/*写入控制字节*/
	u32WRITE(I2C_TX_DATA,(unsigned long)controlbyte);

	/*配置后续字节方向*/
	regtmp = u32READ(I2C_CTRL);
	regtmp &= 0xFFFFFFEF;
	if(0x0==(0x01&controlbyte))
		regtmp |= (unsigned long)0x10;

	/*产生ReStart信号*/
	regtmp |= (unsigned long)0x04;

	/*启动本次传输*/
	regtmp |= (unsigned long)0x01;

	/*等待I2C_SLAVE设备准备就绪*/
	while(0x0==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

	u32WRITE(I2C_CTRL,regtmp);

	/*等待本次传输完成*/
	while(0x0==(((unsigned long)0x80)&(u32READ(I2C_STAT))));

	/*清除ReStart产生位*/
	regtmp = u32READ(I2C_CTRL);
	regtmp &= 0xFFFFFFFB;
	u32WRITE(I2C_CTRL,regtmp);

	/*等待I2C_SLAVE设备准备就绪*/
	while(I2C_SLAVE_FLAG==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));
}

/***************************************************\
*函数名称：I2CGenerateStop
*函数功能：I2C发送Stop信号，释放总线
*输入参数：无
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void I2CGenerateStop(void)
{
	unsigned long regtmp;

	regtmp = u32READ(I2C_CTRL);

	/*产生Stop信号*/
	regtmp &= 0xFFFFFFDF;

	/*启动传输位*/
	regtmp |= (unsigned long)0x01;

	u32WRITE(I2C_CTRL,regtmp);

}

/***************************************************\
*函数名称：I2CTransmitData
*函数功能：发送数据
*输入参数：
*		   1、UINT8 ctrl,I2C控制字节
*		   2、UINT8 data,待发送数据
*输出参数：无
*返 回 值：无
*其它说明：
\***************************************************/
void I2CSendByte(unsigned char data)
{
	unsigned long regtmp;

	u32WRITE(I2C_TX_DATA,data);

	/*启动传输*/
	regtmp = u32READ(I2C_CTRL);
	regtmp |= (unsigned long)0x01;

	/*等待I2C_SLAVE设备准备就绪*/
	while(0x0==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

	u32WRITE(I2C_CTRL,regtmp);

	/*等待本次传输完成*/
	while(0x0==(((unsigned long)0x80)&(u32READ(I2C_STAT))));

	/*等待I2C_SLAVE设备准备就绪*/
	while(I2C_SLAVE_FLAG==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));
}

/***************************************************\
*函数名称：I2CReceiveData
*函数功能：接收数据
*输入参数：
*		   1、UINT8 ctrl,I2C控制字节
*输出参数：无
*返 回 值：UINT8 datatmp,接收的数据
*其它说明：
\***************************************************/
UINT8 I2CReceByteWithACK(void)
{
	unsigned long regtmp;

	regtmp = u32READ(I2C_CTRL);

	/*设置Master-Receive模式下，返回ACK*/
	regtmp &= 0xFFFFFFF7;

	/*启动本次传输*/
	regtmp |= (unsigned long)0x01;

	/*等待I2C_SLAVE设备准备就绪*/
	while(0x0==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

	u32WRITE(I2C_CTRL,regtmp);

	/*等待本次传输完成*/
	while(0x0==(((unsigned long)0x80)&(u32READ(I2C_STAT))));

	/*等待I2C_SLAVE设备准备就绪*/
	while(I2C_SLAVE_FLAG==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));
	
	regtmp = u32READ(I2C_RX_DATA);

	return (unsigned char)regtmp;
}

UINT8 I2CReceByteWithNAK(void)
{
	unsigned long regtmp;

	regtmp = u32READ(I2C_CTRL);

	/*设置Master-Receive模式下，返回ACK*/
	regtmp |= (unsigned long)0x08;

	/*启动本次传输*/
	regtmp |= (unsigned long)0x01;

	/*等待I2C_SLAVE设备准备就绪*/
	while(0x0==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

	u32WRITE(I2C_CTRL,regtmp);

	/*等待本次传输完成*/
	while(0x0==(((unsigned long)0x80)&(u32READ(I2C_STAT))));

	/*等待I2C_SLAVE设备准备就绪*/
	while(I2C_SLAVE_FLAG==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));
	
	regtmp = u32READ(I2C_RX_DATA);

	return (unsigned char)regtmp;
}
