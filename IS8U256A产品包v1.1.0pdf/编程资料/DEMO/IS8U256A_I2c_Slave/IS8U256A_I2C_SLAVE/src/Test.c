
#include <string.h>

#include "..\inc\IS8U256X.h"

#include "..\inc\IS8U256A_GPIO.h"

#include "..\inc\IS8U256A_I2CSlave.h"

#define BUFF_LENGTH		64

unsigned char xdata Buff1_for_Test[BUFF_LENGTH] _at_ 0x1000;
unsigned char xdata Buff2_for_Test[BUFF_LENGTH] _at_ 0x1080;

void main(void)
{
	unsigned char xdata i=0x0;
	unsigned char xdata bytelen;
	unsigned int xdata j;

	CFCR = 0x0;

	GPIOInit();

	GPIOSetOutput(GPIO_PIN_20);

	GPIOReset(GPIO_PIN_20);

	I2CSlaveInit();

	while(1)
	{
		for(j=0;j<4000;j++);

		if(SLAVE_INPUT==I2CSlavePrepareToTransmit())
		{
			bytelen = 64;
			i = 0x0;
			memset(Buff1_for_Test,0x0,sizeof Buff1_for_Test);
			while(bytelen)
			{
				Buff1_for_Test[i] = I2CSlaveReceByte();

				i++;

				bytelen--;
			}

			for(i=0;i<64;i++)
				if(0xAA!=Buff1_for_Test[i])
					goto Error;
		}

		for(j=0;j<4000;j++);

		if(SLAVE_OUTPUT==I2CSlavePrepareToTransmit())
		{
			bytelen = 64;
			i = 0x0;
			memset(Buff2_for_Test,0xBB,sizeof Buff2_for_Test);
			while(bytelen)
			{
				I2CSlaveSendByte(Buff2_for_Test[i]);

				i++;

				bytelen--;
			}
		}

		for(j=0;j<8000;j++);

	}

Error:
	while(1);
}

