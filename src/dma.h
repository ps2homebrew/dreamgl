//---------------------------------------------------------------------------
// File:   dma.h
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
#ifndef DMA_H
#define DMA_H

#include "ee.h"
#include "dma_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void dma_reset(void);

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
// CHCR Register - Channel Control Register
//---------------------------------------------------------------------------
#define GIF_CHCR		((volatile uint32 *)(gif_chcr))

#define SET_CHCR(WHICH,DIR,MOD,ASP,TTE,TIE,STR,TAG) \
	*WHICH = \
	((uint32)(DIR)	<< 0)		| \
	((uint32)(MOD)	<< 2)		| \
	((uint32)(ASP)	<< 4)		| \
	((uint32)(TTE)	<< 6)		| \
	((uint32)(TIE)	<< 7)		| \
	((uint32)(STR)	<< 8)		| \
	((uint32)(TAG)	<< 16)

#define DMA_WAIT(WHICH) \
	while((*WHICH) & (1<<8))

//---------------------------------------------------------------------------
// MADR Register - Transfer Address Register
//---------------------------------------------------------------------------
#define GIF_MADR		((volatile uint32 *)(gif_madr))

#define SET_MADR(WHICH,ADDR,SPR) \
	*WHICH = \
	((uint32)(ADDR)	<< 0)		| \
	((uint32)(SPR)	<< 31)

//---------------------------------------------------------------------------
// TADR Register - Tag Address Register
//---------------------------------------------------------------------------
#define GIF_TADR		((volatile uint32 *)(gif_tadr))

#define SET_TADR(WHICH,ADDR,SPR) \
	*WHICH = \
	((uint32)(ADDR)	<< 0)		| \
	((uint32)(SPR)	<< 31)

//---------------------------------------------------------------------------
// QWC Register - Transfer Data Size Register
//---------------------------------------------------------------------------
#define GIF_QWC		((volatile uint32 *)(gif_qwc))

#define SET_QWC(WHICH,SIZE) \
	*WHICH = (uint32)(SIZE)

#endif // DMA_H

