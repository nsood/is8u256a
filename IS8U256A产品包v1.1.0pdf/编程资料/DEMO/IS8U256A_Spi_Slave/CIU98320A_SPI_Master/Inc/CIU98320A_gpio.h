/************************************************************/
/*				Copy Right (C) HED.Inc						*/
/*				All Right Reserved							*/
/*文件名称：CIU96S320A_gpio.h								*/
/*作    者：												*/
/*当前版本：V1.0.0											*/
/*日    期：2012-08-26										*/
/*功能描述：	   											*/
/*		                                                    */
/*修改内容：初版做成										*/
/************************************************************/

#ifndef _CIU98320A_GPIO_H__
#define _CIU98320A_GPIO_H__

#ifndef GPIO

#define GPIO1		(1<<0)
#define GPIO2       (1<<1)
#define GPIO3		(1<<2)
#define GPIO4		(1<<3)
#define GPIO5       (1<<4)
#define GPIO6		(1<<5)
#define GPIO7		(1<<6)
#define GPIO8       (1<<7)
#define GPIO9		(1<<8)
#define GPIO10		(1<<9)
#define GPIO11      (1<<10)
#define GPIO12		(1<<11)
#define GPIO13		(1<<12)
#define GPIO14      (1<<13)
#define GPIO15		(1<<14)
#define GPIO16		(1<<15)
#define GPIO17      (1<<16)
#define GPIO18		(1<<17)
#define GPIO19		(1<<18)
#define GPIO20      (1<<19)
#define GPIO21		(1<<20)
#define GPIO22		(1<<21)
#define GPIO23      (1<<22)
#define GPIO24		(1<<23)
#define GPIO25		(1<<24)
#define GPIO26      (1<<25)
#define GPIO27		(1<<26)
#define GPIO28		(1<<27)
#define GPIO29      (1<<28)
#define GPIO30		(1<<29)
#define GPIO31		(1<<30)
#define GPIO32      ((unsigned int)1<<31)

#endif

#ifndef GPIO_GLOBAL
#define GPIO_EXT extern
#else
#define GPIO_EXT
#endif

GPIO_EXT void GpioInit(void);
GPIO_EXT void SetGpioXOut(UINT32 GPIOX);
GPIO_EXT void SetGpioXIn(UINT32 GPIOX);
GPIO_EXT void SetGpioXHigh(UINT32 GPIOX);
GPIO_EXT void SetGpioXLow(UINT32 GPIOX);

#endif
