//---------------------------------------------------------------------------
// File:   gif.h
// Author: Tony Saveski, tony@ui.com.au
//---------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
#ifndef GIF_H
#define GIF_H

#include "ee.h"
#include "dma.h"
#include "gs_regs.h"

//---------------------------------------------------------------------------
#define GIF_AD		0x0e
#define GIF_NOP		0x0f

//---------------------------------------------------------------------------
// GS_PACKET macros
//---------------------------------------------------------------------------

#define DECLARE_GS_PACKET(NAME,ITEMS) \
	uint64 __attribute__((aligned(64))) NAME[ITEMS*2+2]; \
	uint64	NAME##_nloop; 	\
	uint64 	NAME##_cur; 	\
	uint64 	NAME##_dma_size; \
	uint64	NAME##_max_items=ITEMS

#define DECLARE_EXTERN_GS_PACKET(NAME) \
	extern uint64 __attribute__((aligned(64))) NAME[]; \
	extern uint64	NAME##_nloop; 	\
	extern uint64 	NAME##_cur; 	\
	extern uint64	NAME##_dma_size; \
	extern uint64	NAME##_max_items

#define BEGIN_GS_PACKET(NAME) \
	NAME##_nloop = 0; 		\
	NAME##_dma_size = 0;	\
	NAME##_cur = 0

#define GIF_TAG(NAME,EOP,PRE,PRIM,FLG,NREG,REGS) \
	NAME[NAME##_cur++] = \
		((uint64)(EOP)	<< 15)		| 	\
		((uint64)(PRE)	<< 46)		| 	\
		((uint64)(PRIM)	<< 47)		| 	\
		((uint64)(FLG)	<< 58)		| 	\
		((uint64)(NREG)	<< 60);			\
	NAME[NAME##_cur++] = (uint64)REGS; 	\
	NAME##_dma_size++

#define GIF_TAG_AD(NAME,EOP,PRE,PRIM,FLG) \
	GIF_TAG(NAME,EOP,PRE,PRIM,FLG,1,GIF_AD)

#define GIF_TAG_IMG(NAME,QSIZE) \
	GIF_TAG(NAME,1,0,0,2,0,0);	\
	NAME##_nloop = QSIZE; 		\
	NAME##_dma_size = 1

#define GIF_DATA_AD(NAME,REG,DAT) \
	NAME[NAME##_cur++] = (uint64)DAT; 		\
	NAME[NAME##_cur++] = (uint64)REG;		\
	NAME##_dma_size++; 						\
	NAME##_nloop++;							\
	if(NAME##_nloop == NAME##_max_items)	\
	{ 										\
		SEND_GS_PACKET(NAME);				\
		BEGIN_GS_PACKET(NAME);				\
		GIF_TAG_AD(NAME, 1, 0, 0, 0);		\
	}

#define SEND_GS_PACKET(NAME) \
	NAME[0] |= NAME##_nloop;					\
	ee_flush_cache(0);							\
	SET_QWC(GIF_QWC, NAME##_dma_size);			\
	SET_MADR(GIF_MADR, NAME, 0);				\
	SET_CHCR(GIF_CHCR, 1, 0, 0, 0, 0, 1, 0);	\
	DMA_WAIT(GIF_CHCR)

#endif // GIF_H
