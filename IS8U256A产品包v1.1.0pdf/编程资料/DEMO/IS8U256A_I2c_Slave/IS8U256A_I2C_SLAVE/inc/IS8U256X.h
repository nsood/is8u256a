/*--------------------------------------------------------------------------
XA1302X51.h

Header File For ISTECC xa1302 Microcontroller.
Copyright (c) Beijing Huada Infosec Technology Co.,Ltd 
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __IS8UX51_H__
#define __IS8UX51_H__

/*  BYTE Registers  */

sfr	SP			 =	0x81;
sfr	DPL0		 =	0x82;
sfr	DPH0		 =	0x83;
sfr	DPL1		 =	0x84;
sfr	DPH1		 =	0x85;
sfr	DPS			 =	0x86;

sfr	TCON		 =	0x88;
sbit  TF1    =  TCON^7;    
sbit  TR1    =  TCON^6;    
sbit  TF0    =  TCON^5;    
sbit  TR0    =  TCON^4;    
sbit  TSEL   =  TCON^3;    
sbit  CT1    =  TCON^2;    
sbit  CT0    =  TCON^0;
sfr	TMOD		 =	0x89;
sfr	T0L 		 =	0x8A;
sfr	T1L 		 =	0x8B;
sfr	T0H 		 =	0x8C;
sfr	T1H 		 =	0x8D;
sfr	RT0L 		 =	0x8A;
sfr	RT1L 		 =	0x8B;
sfr	RT0H 		 =	0x8C;
sfr	RT1H 		 =	0x8D;
sfr	CFCR     	 =	0x8E;
sfr	PMWE     	 =	0x8F;

sfr	CRCCON		 =	0x90; 
sfr	CRCDATA	 	 =	0x91; 
sfr	MPAGE		   =	0x92; 
sfr	ROMBANK  	 =	0x93;
sfr	PLLCON   	 =	0x94;

sfr	PCON1    	   = 0x96;
sfr	SCISCNT		   = 0x97;
sfr	SCISSR	     = 0x98; 
sbit  SSETU      = SCISSR^6;     
sbit  STB        = SCISSR^5;    
sbit  STI        = SCISSR^4;     
sbit  SRB        = SCISSR^3;     
sbit  SRI        = SCISSR^2;    
sbit  SPE        = SCISSR^1;    
sbit  SOE        = SCISSR^0;
sfr	SCISBUF	     =	0x99;
sfr	SCISCON	     =	0x9A;
sfr	INFST	     =	0x9B;
sfr	COMCON   	 =	0x9C;
sfr	PCON2    	 =	0x9D;
sfr	CRCIV    	 =	0x9F;

sfr	SCISTXFCR		=	0xA0;
sbit TX_Full   = SCISTXFCR^1;
sbit Clear_TX_FIFO = SCISTXFCR^0;
sfr	SCISRXFCR		=	0xA1;

sfr	IEL		    =	0xA8;
sbit  ET1     = IEL^6;     
sbit  ET0     = IEL^5;    
sbit  EMSI    = IEL^4;     
sbit  EEI     = IEL^3;     
sbit  EUI     = IEL^2;    
sbit  ESI     = IEL^1; 
sfr	CWATOP		=	0xA9;
sfr	CWABOT		=	0xAA;
sfr	CWBTOP		=	0xAB;
sfr	USBINTEN	=	0xAC;
sfr	USBCMD		=	0xAD;
sfr	USBCON		=	0xAE;
sfr	USBDATA		=	0xAF;

sfr	SPICFG		  	=	0xB0;
sbit  SS_FILTER   = SPICFG^7;
sbit  MSB         = SPICFG^3; 
sbit  CPHA        = SPICFG^2;  
sbit  CPOL        = SPICFG^1; 
sbit  MASTER      = SPICFG^0;
sfr	SPICON		  	=	0xB1;
sfr	SPIMODE		  	=	0xB2;
sfr	SPIINTERVAL		=	0xB3;
sfr	SPISTATUS		=	0xB4;
sfr	SPIINTCLR		=	0xB5;
sfr	SPICLKDIV	  	=	0xB6;
sfr	SPIDATA	    	=	0xB7;

sfr	UARTSR		    =	0xB0;
sbit  RX_BUSY            = UARTSR^6;  
sbit  RX_LOSE_ERR        = UARTSR^5;  
sbit  RX_STOP_ERR        = UARTSR^4;  
sbit  RX_PARITY_ERR      = UARTSR^3; 
sbit  TX_INT             = UARTSR^2;  
sbit  RX_INT             = UARTSR^1; 
sbit  TX_BUSY            = UARTSR^0;
sfr	UARTCON		    =	0xB1;
sfr	UARTPR		   	=	0xB2;
sfr	BAUD_FREQ  		=	0xB3;
sfr	BAUD_LIMIT		=	0xB4;
sfr	RX_DATA			=	0xB5;
sfr	TX_DATA	  		=	0xB6;

sfr	SCIMSSR		=	0xB0;
sbit  MSETU              = SCIMSSR^6;    
sbit  MTB                = SCIMSSR^5;    
sbit  MTI                = SCIMSSR^4;    
sbit  MRB                = SCIMSSR^3;    
sbit  MRDI               = SCIMSSR^2;    
sbit  MPEI               = SCIMSSR^1;    
sbit  MOEI               = SCIMSSR^0; 
sfr	SCIMSBUF	=	0xB1;
sfr	SCIMSCON	=	0xB2;
sfr	SCIMSCNT	=	0xB3;
sfr	SCIMSPR		=	0xB4;
sfr	SCIMSCR		=	0xB5;
sfr	SCIMSCCNT	=	0xB6;
sfr	SCIMSCOMP	=	0xB7;

sfr	I2CSTATUS	=	0xB0;
sbit  TIP                = I2CSTATUS^7;    
sbit  ADDR_MATCH         = I2CSTATUS^6;    
sbit  BUS_BUSY           = I2CSTATUS^5;    
sbit  ARB_LOST           = I2CSTATUS^4;   
sbit  TIMEOUT            = I2CSTATUS^3;    
sbit  SLAVE_RW           = I2CSTATUS^2;   
sbit  INT  							 = I2CSTATUS^1;   
sbit  ACK_STATE          = I2CSTATUS^0;
sfr	I2CCON		=	0xB1;
sfr	I2CRDR		=	0xB2;
sfr	I2CADDR		=	0xB3;
sfr	I2CTDR		=	0xB4;
sfr	I2CTO		=	0xB5;
sfr	I2CPRER		=	0xB6;
sfr	I2CMMR		=	0xB7;

sfr DMACFG		=	0xB8;
sbit  SRC_DEC  		= DMACFG^1;   
sbit  DEST_DEC    = DMACFG^0;
sfr DMACON		=	0xB9;
sfr	DMASADR		=	0xBA;
sfr	DMADADR		=	0xBB;
sfr	DMALEN		=	0xBC;
sfr	WDTLOAD		=	0xBD;
sfr	WDTVALUE	=	0xBE;
sfr	WDTCTRL		=	0xBF;


sfr	GPIOINT		     	=	0xC6;
sfr	GPIODATA		    =	0xC7;
sfr	GPIOCTRL		    =	0xC8;
sbit  GP8OE         = GPIOCTRL^7;    
sbit  GP7OE         = GPIOCTRL^6;    
sbit  GP6OE         = GPIOCTRL^5;    
sbit  GP5OE         = GPIOCTRL^4;   
sbit  GP4OE         = GPIOCTRL^3;    
sbit  GP3OE         = GPIOCTRL^2;   
sbit  GP2OE  			  = GPIOCTRL^1;   
sbit  GP1OE         = GPIOCTRL^0;
sfr	GPIODATA1		    =	0xC9;
sfr	GPIOCTRL1		    =	0xCA;
sfr	GPIODATA2		    =	0xCB;
sfr	GPIOCTRL2		    =	0xCC;
sfr	GPIOPR		      =	0xCD;
sfr	GPIOPR1		      =	0xCE;
sfr	GPIOPR2		      =	0xCF;

sfr	PSW			     =	0xD0;
sbit  CY         =  PSW^7;    
sbit  AC         =  PSW^6;    
sbit  F0         =  PSW^5;    
sbit  RS1        =  PSW^4;   
sbit  RS0        =  PSW^3;    
sbit  OV         =  PSW^2;   
sbit  F1  			 =  PSW^1;   
sbit  P          =  PSW^0;
sfr	GPIOPR3		  	=	0xD1;
sfr	SAFESTATE0		=	0xD3;
sfr	SAFESTATE1		=	0xD4;
sfr	SAFESTATE2		=	0xD5;

sfr	ECNTRL		  	=	0xD8;
sbit  EPEN        = ECNTRL^2;
sfr	IEH		      	=	0xDB;
sfr	RAMBANK		  	=	0xDC;


sfr	ACC			  	=	0xE0;
sfr	RSTSTATE1		=	0xE6;
sfr	LOWPC2			=	0xE7;
sfr	RSTSTATE0		=	0xE8;
sbit  LDRST     = RSTSTATE0^7;    
sbit  COLDRST   = RSTSTATE0^6;    
sbit  SCIRST    = RSTSTATE0^5;    
sbit  USBRST    = RSTSTATE0^4;   
sbit  WDTRST    = RSTSTATE0^3;    
sbit  TDRST     = RSTSTATE0^2;   
sbit  FDRST  		= RSTSTATE0^1;   
sbit  VDERST    = RSTSTATE0^0;
sfr	PCON0		  	=	0xEA;
sfr	RSTCON			=	0xEB;
sfr	LOWPC0			=	0xEC;
sfr	LOWPC1			=	0xED;
sfr	COMSEL			=	0xEE;

sfr	B			    	=	0xF0;
sfr	SASEL		  	=	0xF1;
sfr	RNGCTR			=	0xF3;
sfr	RNGOUT	  	=	0xF4;
sfr	RNGIN	    	=	0xF5;
sfr	TRNGD		  	=	0xF7;


#endif