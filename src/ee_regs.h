//------------------------------------------------------------------------
// File:   ee_regs.h
// Author: Tony Saveski, tony@ui.com.au
//------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//------------------------------------------------------------------------
// This software (hereafter, "Software") is the property of Unicorn
// Interactive Pty Ltd (hereafter, "Unicorn"). The following conditions
// apply:
//
// * Unicorn grants you (hereafter, "Licensee") a license to use the
//   Software for academic, research and non-commercial purposes only,
//   without a fee. Licensees may distribute unmodified versions of the
//   binary and source code of the Software to third parties under the
//   terms of this license but must ensure that such distribution is under
//   the terms of this license and this license is distributed along with
//   the binaries and source.
//
// * Unicorn imposes the following restrictions on any code developed
//   using the Software:
//   - Unicorn retains a non-exclusive royalty-free license, including the
//     right of redistribution, to any modifications to the Software made
//     by the licensee.
//   - You may not distribute modified versions of the Software.
//
// * Any Licensee wishing to make commercial use of the Software should
//   contact Unicorn to negotiate an appropriate license for such
//   commercial use. Commercial use includes but is not limited to:
//   - integration of all or part of the source code into a product for
//     sale or commercial license by or on behalf of Licensee to third
//     parties, or
//   - distribution of the binary code or source code to third parties
//     that need it to utilize a commercial product sold or licensed by or
//     on behalf of Licensee, or
//   - use in an internal operational environment.
//
//   Please email info@ui.com.au for details.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT
// LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// IN NO EVENT SHALL UNICORN INTERACTIVE PTY LTD BE LIABLE FOR ANY SPECIAL,
// INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY
// DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY
// THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THE SOFTWARE.
//
// Unicorn welcome comments and bug fixes related to the Software.
// Please address any queries, comments or bug fixes to the address below:
//
//   E-Mail: info@ui.com.au
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
