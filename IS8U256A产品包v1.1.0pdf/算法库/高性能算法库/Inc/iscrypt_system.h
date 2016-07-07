/****************************************************************\
* Copyright (C) 2005-2014 Beijing HuaDa InfoSec Tech. Co., Ltd
* All Rights Reserved
* File Name:	iscrypt_system.h
* Author:		PeiChao        
* Version:		1.0.0.0        
* Date:			2013.11.21  
* Description:    
* 				1. Special Registers Definitions of the Chip
*				2. Some Macro Definitions about Operations 
*				   of Registers
*														  	
* Others:		None         
* Function List:                
*   			1. None
* History:        
*                 
*   1. Date:
*      Author:
*      Modification:
*   2. ......
\****************************************************************/
#ifndef __IS_SYSTEM_H__
#define __IS_SYSTEM_H__

/* Sepcial functional registers definitions */
sfr rSP		=	0x81;
sfr rDPL0	=	0x82;
sfr rDPH0	=	0x83;
sfr rDPL1	=	0x84;
sfr rDPH1	=	0x85;
sfr rDPS	=	0x86;

sfr rCFCR	=	0x8E;


sfr rCRCDATA	=	0x91;

sfr rCRCIV		=	0x9F;

sfr rROMBANK	=	0x93;

sfr rPCON1		=	0x96;

sfr rPCON2		=	0x9D;

sfr rSAFECON0	=	0xA2;
sfr rSAFECON1	=	0xA3;
sfr rSAFECON2	=	0xA4;

//-- DMA ---------------------------------------------
sfr rDMAMODE	=	0xB8;
sfr rDMACON		=	0xB9;
sfr rDMASRC		=	0xBA;
sfr rDMADST		=	0xBB;
sfr rDMALEN		=	0xBC;

sfr rPSW		=	0xD0;

sfr rPCON0		=	0xEA;


//-- DRNG ---------------------------------------------
sfr rRNGCON		=	0xF3;
sfr rRNGOUT		=	0xF4;
sfr rRNGIN		=	0xF5;
sfr rTRNGTST	=	0xF6;
sfr rTRNGD		=	0xF7;


//-- DES ---------------------------------------------
sfr rDESCON		=	0xF8;
sfr rDESDATA	=	0xF9;

sfr rDESKEY		=	0xFB;

//-- PKU ---------------------------------------------
sfr rPKUCMD		=	0xF8;
sfr rPKUMC		=	0xF9;

sfr rPKUSEGN	=	0xFB;
sfr rPKUEREG	=	0xFC;
sfr rPKUINT		=	0xFD;

//-- CRYPT ---------------------------------------------
sfr rCRYPTCON	=	0xF8;
sfr rCRYPTSET0	=	0xF9;

sfr rCRYPTSET1	=	0xFB;
sfr rCRYPTREM	=	0xFC;
sfr rCRYPTQUOT	=	0xFD;


//-- XXX ---------------------------------------------
sfr rACC	=	0xE0;

sfr	rB		=	0xF0;

sfr	rSASEL	=	0xF1;

//-------------------------------------------------------------------- 

/* Switch of functional register */
#define	ISCRYPTEN			0x02
#define	PKUEN				0x10
#define	DESEN				0x40
#define	CRCEN				0x80

#define	MRNGEN				0x01
#define	TRNGEN				0x02
#define	TIMEREN				0x04
#define	GPIOEN				0x08
#define	SPIEN				0x10
#define	DMAEN				0x20

//--------------------------------------------------------------------
#define	ISCRYPTDN			~ISCRYPTEN
#define	PKUDN				~PKUEN
#define	DESDN				~DESEN
#define	CRCDN				~CRCEN

#define	MRNGDN				~MRNGEN
#define	TRNGDN				~TRNGEN
#define	TIMERDN				~TIMEREN
#define	GPIODN				~GPIOEN
#define	SPIDN				~SPIEN
#define	DMADN				~DMAEN


#define	SFR_DES_SEL			0x00
#define	SFR_PKU_SEL			0x03
#define	SFR_ISCRYPT_SEL		0x06
#define	SFR_DIVSFT_SEL		0x06


/* DMA_TYPE */
//#define DMA_SRC_ROM_ALL_INC			0xA0
#define DMA_SRC_ROM_ALL_INC			0x00
//#define DMA_SRC_FLASH_ALL_INC		0x00

/* */
#define PKU_RAM0		((unsigned char xdata *)0x1800)
#define PKU_RAM1		((unsigned char xdata *)0x1820)
#define PKU_RAM2		((unsigned char xdata *)0x1840)
#define PKU_RAM3		((unsigned char xdata *)0x1860)
#define PKU_RAM4		((unsigned char xdata *)0x1880)
#define PKU_RAM5		((unsigned char xdata *)0x18A0)
#define PKU_RAM6    	((unsigned char xdata *)0x18C0)
#define PKU_RAM7		((unsigned char xdata *)0x18E0)
#define PKU_RAM10		((unsigned char xdata *)0x1900)
#define PKU_RAM11		((unsigned char xdata *)0x1920)
#define PKU_RAM12		((unsigned char xdata *)0x1940)
#define PKU_RAM13		((unsigned char xdata *)0x1960)
#define PKU_RAM14		((unsigned char xdata *)0x1980)
#define PKU_RAM15		((unsigned char xdata *)0x19A0)
#define PKU_RAM16		((unsigned char xdata *)0x19C0)
#define PKU_RAM17		((unsigned char xdata *)0x19E0)
#define PKU_RAM20		((unsigned char xdata *)0x1A00)
#define PKU_RAM21		((unsigned char xdata *)0x1A20)
#define PKU_RAM22		((unsigned char xdata *)0x1A40)
#define PKU_RAM23		((unsigned char xdata *)0x1A60)
#define PKU_RAM24		((unsigned char xdata *)0x1A80)
#define PKU_RAM25		((unsigned char xdata *)0x1AA0)
#define PKU_RAM26		((unsigned char xdata *)0x1AC0)
#define PKU_RAM27		((unsigned char xdata *)0x1AE0)
#define PKU_RAM30		((unsigned char xdata *)0x1B00)
#define PKU_RAM31		((unsigned char xdata *)0x1B20)
#define PKU_RAM32		((unsigned char xdata *)0x1B40)
#define PKU_RAM33		((unsigned char xdata *)0x1B60)
#define PKU_RAM34		((unsigned char xdata *)0x1B80)
#define PKU_RAM35		((unsigned char xdata *)0x1BA0)
#define PKU_RAM36		((unsigned char xdata *)0x1BC0)
#define PKU_RAM37		((unsigned char xdata *)0x1BE0)

/* DEFINITIONS OF COMMAND ABOUT PKU */
#define PKU_HALT		0x00
#define PKU_MOD_MUL		0x01
#define PKU_MOD_ADD		0x02
#define PKU_MOD_SUB		0x04
#define PKU_ADD_JA		0x08
#define PKU_DBL_J		0x10
#define PKU_MOD_EXP		0x20


#endif