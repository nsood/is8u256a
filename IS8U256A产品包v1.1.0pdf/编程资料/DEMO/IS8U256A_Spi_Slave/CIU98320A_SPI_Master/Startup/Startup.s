;/*****************************************************************************/
;/* STARTUP.S: Startup file for Dhrystone Example                             */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */ 
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2006 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


; *** Startup Code (executed after Reset) ***


; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled


; Internal RAM Address
RAM_Base        EQU     0x000D0000      ; after Ramap
RAM_Base_Boot   EQU     0x000D1000      ; after Reset until Remap 


;// <h> Stack Configuration (Stack Sizes in Bytes)
;//   <o0> Undefined Mode      <0x0-0xFFFFFFFF:8>
;//   <o1> Supervisor Mode     <0x0-0xFFFFFFFF:8>
;//   <o2> Abort Mode          <0x0-0xFFFFFFFF:8>
;//   <o3> Fast Interrupt Mode <0x0-0xFFFFFFFF:8>
;//   <o4> Interrupt Mode      <0x0-0xFFFFFFFF:8>
;//   <o5> User/System Mode    <0x0-0xFFFFFFFF:8>
;// </h>

UND_Stack_Size  EQU     0x00000004
SVC_Stack_Size  EQU     0x00000008
ABT_Stack_Size  EQU     0x00000004
FIQ_Stack_Size  EQU     0x00000080
IRQ_Stack_Size  EQU     0x00000200
USR_Stack_Size  EQU     0x00000200

ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size)

                AREA    STACK, NOINIT, READWRITE, ALIGN=3

;// yulb sett stack start address
;Map        0x40003FFC           
Stack_Mem       SPACE   USR_Stack_Size
__initial_sp    SPACE   ISR_Stack_Size

Stack_Top


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF>
;// </h>

Heap_Size       EQU     0x00001000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8

; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY
                ARM

; Exception Vectors (before Remap)
;  Mapped to Address 0 before Remap Command.
;  Relative addressing mode must be used.

Reset_Vec       B       Reset_Handler
Undef_Vec       B       Undef_Vec
SWI_Vec         B       SWI_Vec
PAbt_Vec        B       PAbt_Handler
DAbt_Vec        B       DAbt_Handler
                NOP
IRQ_Vec         B       IRQ_Handler
FIQ_Vec         B       FIQ_Handler


; Exception Vectors (after Remap)
;  Mapped to Address 0 after Remap Command.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

Vectors         
				LDR     PC, Reset_Addr         
                LDR     PC, Undef_Addr
                LDR     PC, SWI_Addr
                LDR     PC, PAbt_Addr
                LDR     PC, DAbt_Addr
                NOP                            ; Reserved Vector 
                LDR     PC, IRQ_Addr
;                LDR     PC, [PC, #-0xF20]      ; Vector from AIC_IVR 
                LDR     PC, FIQ_Addr
;                LDR     PC, [PC, #-0xF20]      ; Vector from AIC_FVR 

Reset_Addr      DCD     Soft_Reset
Undef_Addr      DCD     Undef_Handler
SWI_Addr        DCD     SWI_Handler_t
PAbt_Addr       DCD     PAbt_Handler_t
DAbt_Addr       DCD     DAbt_Handler_t
                DCD     0                      ; Reserved Address 
IRQ_Addr        DCD     IRQ_Handler_t
FIQ_Addr        DCD     FIQ_Handler_t

Soft_Reset      B       Reset_Handler
Undef_Handler   B       Undef_Handler
SWI_Handler_t     B       SWI_Handler
PAbt_Handler_t    B       PAbt_Handler
DAbt_Handler_t    B       DAbt_Handler
IRQ_Handler_t     B       IRQ_Handler
FIQ_Handler_t     B       FIQ_Handler

			NOP

			;ALIGN	128	;aligned to 64byte address
;interrupt vector entry
Interrupt_Vector_Table
			;EXPORT Interrupt_Vector_Table
ISR0		B		ISR0_Body
ISR1		B		ISR1_Body
ISR2		B		ISR2_Body
ISR3		B		ISR3_Body
ISR4		B		ISR4_Body
ISR5		B		ISR5_Body
ISR6		B		ISR6_Body
ISR7		B		ISR7_Body
ISR8		B		ISR8_Body
ISR9		B		ISR9_Body
ISR10		B		ISR10_Body
ISR11		B		ISR11_Body
ISR12		B		ISR12_Body
ISR13		B		ISR13_Body
ISR14		B		ISR14_Body
ISR15		B		ISR15_Body
ISR16		B		ISR16_Body
ISR17		B		ISR17_Body
ISR18		B		ISR18_Body
ISR19		B		ISR19_Body
ISR20		B		ISR20_Body
ISR21		B		ISR21_Body
ISR22		B		ISR22_Body
ISR23		B		ISR23_Body
ISR24		B		ISR24_Body
ISR25		B		ISR25_Body
ISR26		B		ISR26_Body
ISR27		B		ISR27_Body
ISR28		B		ISR28_Body
ISR29		B		ISR29_Body
ISR30		B		ISR30_Body
ISR31		B		ISR31_Body


				IMPORT Timer1IrqHandler
ISR0_Body		PROC
				EXPORT ISR0_Body
				BL	Timer1IrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Timer2IrqHandler
ISR1_Body		PROC
				EXPORT ISR1_Body
				BL	Timer2IrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT WatchDogIrqHandler
ISR2_Body		PROC
				EXPORT ISR2_Body
				BL	WatchDogIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT FlashIrqHandler
ISR3_Body		PROC
				EXPORT ISR3_Body
				BL	FlashIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT GpioIrqHandler
ISR4_Body		PROC
				EXPORT ISR4_Body
				BL	GpioIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Timer3IrqHandler
ISR5_Body		PROC
				EXPORT ISR5_Body
				BL	Timer3IrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT DmaIrqHandler
ISR6_Body		PROC
				EXPORT ISR6_Body
				BL	DmaIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT PllIrqHandler
ISR7_Body		PROC
				EXPORT ISR7_Body
				BL	PllIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Slave7816RstIrqHandler
ISR8_Body		PROC
				EXPORT ISR8_Body
				BL	Slave7816RstIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Slave7816TxIrqHandler
ISR9_Body		PROC
				EXPORT ISR9_Body
				BL	Slave7816TxIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Slave7816RxIrqHandler
ISR10_Body		PROC
				EXPORT ISR10_Body
				BL	Slave7816RxIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Slave7816OverFlowIrqHandler
ISR11_Body		PROC
				EXPORT ISR11_Body
				BL	Slave7816OverFlowIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				;IMPORT ISR12_Routine
ISR12_Body		PROC
				EXPORT ISR12_Body
				;BL	ISR12_Routine
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT UsbIrqHandler
ISR13_Body		PROC
				EXPORT ISR13_Body
				BL	UsbIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Spi0IrqHandler
ISR14_Body		PROC
				EXPORT ISR14_Body
				BL	Spi0IrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				;IMPORT ISR15_Routine
ISR15_Body		PROC
				EXPORT ISR15_Body
				;BL	ISR15_Routine
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				;IMPORT ISR16_Routine
ISR16_Body		PROC
				EXPORT ISR16_Body
				;BL	ISR16_Routine
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT I2CIrqHandler
ISR17_Body		PROC
				EXPORT ISR17_Body
				BL	I2CIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT UartIrqHandler
ISR18_Body		PROC
				EXPORT ISR18_Body
				BL	UartIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Master7816TxIrqHandler
ISR19_Body		PROC
				EXPORT ISR19_Body
				BL	Master7816TxIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Master7816RxIrqHandler
ISR20_Body		PROC
				EXPORT ISR20_Body
				BL	Master7816RxIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Master7816OverFlowIrqHandler
ISR21_Body		PROC
				EXPORT ISR21_Body
				BL	Master7816OverFlowIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				;IMPORT ISR22_Routine
ISR22_Body		PROC
				EXPORT ISR22_Body
				;BL	ISR22_Routine
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT Spi2IrqHandler
ISR23_Body		PROC
				EXPORT ISR23_Body
				BL	Spi2IrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				;IMPORT ISR24_Routine
ISR24_Body		PROC
				EXPORT ISR24_Body
				;BL	ISR24_Routine
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT PKEIrqHandler
ISR25_Body		PROC
				EXPORT ISR25_Body
				BL	PKEIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				;IMPORT ISR26_Routine
ISR26_Body		PROC
				EXPORT ISR26_Body
				;BL	ISR26_Routine
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				IMPORT SM1IrqHandler
ISR27_Body		PROC
				EXPORT ISR27_Body
				BL	SM1IrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				;IMPORT ISR28_Routine
ISR28_Body		PROC
				EXPORT ISR28_Body
				;BL	ISR28_Routine
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				;IMPORT ISR29_Routine
ISR29_Body		PROC
				EXPORT ISR29_Body
				;BL	ISR29_Routine
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

 				;IMPORT ISR30_Routine
ISR30_Body		PROC
				EXPORT ISR30_Body
				;BL	ISR30_Routine
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP

				;IMPORT ISR31_Routine
ISR31_Body		PROC
				EXPORT ISR31_Body
				;BL	ISR31_Routine
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^
				ENDP


; Reset Handler

                EXPORT  Reset_Handler
Reset_Handler   


; Setup Stack for each mode

                LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
                ;MSR     CPSR_c, #Mode_USR
                ;IF      :DEF:__MICROLIB

                ;EXPORT __initial_sp

                ;ELSE

                ;MOV     SP, R0
                ;SUB     SL, SP, #USR_Stack_Size

                ;ENDIF

; init MPU
				MOV		R1,		#0x0
				MCR p15, 0, R1, c1, c0, 0
				
				;IMPORT 	Interrupt_Vector_Table
;init intc
				MOV		R0,		#0xFF000
				LDR		R1,		=Interrupt_Vector_Table
				STR		R1,		[R0,#0x830];		

; Enter the C code


                IMPORT  __main
                LDR     R0, =__main
                BX      R0


				IMPORT DAbtIrqHandler
DAbt_Handler	PROC
				EXPORT DAbt_Handler
				
				;SUBS	PC,	LR,	#4
				sub		LR,		LR,	#4
				STMFD	SP!,	{LR}
				MRS		R14, 	SPSR
				STMFD	SP!, 	{R0-R12, R14};push into stack    
				bl	DAbtIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^ 

				ENDP

				IMPORT PAbtIrqHandler
PAbt_Handler	PROC
				EXPORT PAbt_Handler
				
				;SUBS	PC,	LR,	#4
				sub		LR,		LR,	#4
				STMFD	SP!,	{LR}
				MRS		R14, 	SPSR
				STMFD	SP!, 	{R0-R12, R14};push into stack    
				bl	PAbtIrqHandler
				LDMFD	SP!,	{R0-R12, R14}
				MSR		SPSR_cxsf,	R14
				LDMFD	SP!,	{pc}^ 

				ENDP

SWI_Handler		PROC
				EXPORT SWI_Handler				
				
				LDMIA     R13!,{R14}
				BX R14    

				ENDP


IRQ_Handler		PROC
				EXPORT IRQ_Handler

				sub		LR,		LR,	#4
				STMFD	SP!,	{LR}
				MRS		R14, 	SPSR
				STMFD	SP!, 	{R0-R12, R14}
				
				LDR		R0,		=0xFF830 ;=VICADDRESS
				LDR		PC,		[R0] 

				ENDP



FIQ_Handler		PROC
				EXPORT FIQ_Handler

				sub		LR,		LR,	#4
				STMFD	SP!,	{LR}
				MRS		R14, 	SPSR
				STMFD	SP!, 	{R0-R12, R14};push into stack
				
				LDR		R0,		=0xFF830 ;=VICADDRESS
				LDR		PC,		[R0]
				 
				ENDP





                
; User Initial Stack & Heap
                AREA    |.text|, CODE, READONLY

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + USR_Stack_Size)
                LDR     R2, = (Heap_Mem +      Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR


                END
