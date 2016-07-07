
#include "..\inc\IS8U256X.h"

#include "..\inc\IS8U256A_UART.h"

#include "..\inc\IS8U256A_GPIO.h"

unsigned char xdata count=0x0;
unsigned char xdata rx_buff[256]={0x0};
unsigned char xdata rxflag=0x0,txflag=0x0;
unsigned char xdata RxFlag0=0x0;
unsigned char xdata i=0x0;

void main(void)
{
	unsigned int i=0x0;

	CFCR = 0x12;

	GPIOInit();

	GPIOSetOutput(GPIO_PIN_19|GPIO_PIN_20);

	UARTInit();


	while(1)
	{
		if(RxFlag0)
		{
			RxFlag0 = 0x0;

			for(i=0;i<count;i++)
				UARTSendByte(rx_buff[i]);

			count=0x0;

		}
	}
}

void UARTHandler(void) interrupt 13
{
	/*关闭总中断*/
	IEH &= 0x7F;	

	/*处理接收中断*/
	if(UARTSR&0x02)
	{
		/*没有接收错误*/
		if(!(UARTSR&0x38))
		{
			/*读取数据并清除接收中断标志*/
			rx_buff[count]=RX_DATA;

			if(count!=rx_buff[4]+5)
			{
				count++;
			}
			else
			{
				RxFlag0=0xFF;
			}

			if(rxflag)
			{
				rxflag = 0x0;
				GPIOSet(GPIO_PIN_20);
			}
			else
			{
				rxflag = 0xff;
				GPIOReset(GPIO_PIN_20);
			}

		}
		/*数据接收错误*/
		else
		{
			
		}
	}

	/*处理发送中断*/
	if(UARTSR&0x04)
	{
		/*清除发送中断标志*/
		UARTSR &= 0xFB;

		if(txflag)
		{
			txflag = 0x0;
			GPIOSet(GPIO_PIN_19);
		}
		else
		{
			txflag = 0xff;
			GPIOReset(GPIO_PIN_19);
		}
	}

	/*恢复总中断*/
	IEH |= 0x80;
}
