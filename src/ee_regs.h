//------------------------------------------------------------------------
// File:   ee_regs.h
// Author: Tony Saveski, tony@ui.com.au
//------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
//------------------------------------------------------------------------
#ifndef EE_REGS_H
#define EE_REGS_H

// MIPS CPU Registsers
#define zero		$0		// Always 0
#define at			$1		// Assembler temporary
#define v0			$2		// Function return
#define v1			$3		//
#define a0			$4		// Function arguments
#define a1			$5
#define a2			$6
#define a3			$7
#define t0			$8		// Temporaries. No need
#define t1			$9		// to preserve in your
#define t2			$10		// functions.
#define t3			$11
#define t4			$12
#define t5			$13
#define t6			$14
#define t7			$15
#define s0			$16		// Saved Temporaries.
#define s1			$17		// Make sure to restore
#define s2			$18		// to original value
#define s3			$19		// if your function
#define s4			$20		// changes their value.
#define s5			$21
#define s6			$22
#define s7			$23
#define t8			$24		// More Temporaries.
#define t9			$25
#define k0			$26		// Reserved for Kernel
#define k1			$27
#define gp			$28		// Global Pointer
#define sp			$29		// Stack Pointer
#define fp			$30		// Frame Pointer
#define ra			$31		// Function Return Address

// Timer Registers
#define t0_count	0x10000000
#define t0_mode		0x10000010
#define t0_comp		0x10000020
#define t0_hold		0x10000030

#define t1_count	0x10000800
#define t1_mode		0x10000810
#define t1_comp		0x10000820
#define t1_hold		0x10000830

#define t2_count	0x10001000
#define t2_mode		0x10001010
#define t2_comp		0x10001020

#define t3_count	0x10001800
#define t3_mode		0x10001810
#define t3_comp		0x10001820

// Timer Register Macros
#define T_MODE(CLKS,GATE,GATS,GATM,ZRET,CUE,CMPE,OVFE,EQUF,OVFF) \
	(((uint32)(CLKS)	<< 0)	| \
	 ((uint32)(GATE)	<< 2)	| \
	 ((uint32)(GATS)	<< 3)	| \
	 ((uint32)(GATM)	<< 4)	| \
	 ((uint32)(ZRET)	<< 6)	| \
	 ((uint32)(CUE)		<< 7)	| \
	 ((uint32)(CMPE)	<< 8)	| \
	 ((uint32)(OVFE)	<< 9)	| \
	 ((uint32)(EQUF)	<< 10)	| \
	 ((uint32)(OVFF)	<< 11))

#endif // EE_REGS_H
