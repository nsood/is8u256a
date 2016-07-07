#include <string.h>

#include "..\inc\IS8U256X.h"

#include "..\inc\IS8U256A_SpiSlave.h"

#include "..\inc\IS8U256A_GPIO.h"

unsigned char xdata Buff_for_Test[64] _at_ 0x1000;

#define DATA_LENGTH		16

void main(void)
{
	unsigned char xdata i;

	CFCR = 0x00;

	GPIOInit();

   /*****************************************
	*GPIO_PIN20设置为输出模式后，默认为高电平
	*****************************************/
	GPIOSetOutput(GPIO_PIN_20);
	GPIOReset(GPIO_PIN_20);

	SpiSlaveInit();

	while(1)
	{
		memset(Buff_for_Test,0x0,sizeof Buff_for_Test);

		/*Receive Data*/
		SpiTransmitData((void *)0,Buff_for_Test,DATA_LENGTH);
		for(i=0;i<DATA_LENGTH;i++)
			if(0xAA!=Buff_for_Test[i])
				goto Error;

		/*Send Data*/
		memset(Buff_for_Test,0x88,sizeof Buff_for_Test);
		SpiTransmitData(&Buff_for_Test[0],(void *)0,DATA_LENGTH);

	}

Error:
	while(1);

}
