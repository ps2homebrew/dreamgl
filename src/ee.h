//------------------------------------------------------------------------
// File:   ee.h
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
#ifndef EE_H
#define EE_H

#include "defines.h"

typedef unsigned long	uint64;
typedef long			int64;

typedef struct int128
{
	int64 lo, hi;
} int128 __attribute__((aligned(16)));

typedef struct uint128
{
	uint64 lo, hi;
} uint128 __attribute__((aligned(16)));

//typedef int 			int128 __attribute__(( mode(TI), aligned(16) ));
//typedef unsigned int 	uint128 __attribute__(( mode(TI), aligned(16) ));

// Timer resolution constants
#define TIMER_RES_BUS		0		// 2500000 clicks per VBLANK
#define TIMER_RES_BUS16		1		// 1/16th of BUS = 156250 clicks per VBLANK
#define TIMER_RES_BUS256	2		// 1/256th of BUS = 9760 clicks per VBLANK
#define TIMER_RES_HBLNK		3		// 262 clicks per VBLANK

#ifdef __cplusplus
extern "C" {
#endif

extern void 	ee_flush_cache(int blah);

extern void 	ee_timer_init(int timer, int resolution);
extern void 	ee_timer_start(int timer);
extern void 	ee_timer_stop(int timer);
extern uint32	ee_timer_get_ticks(int timer);

#ifdef __cplusplus
}
#endif

#endif // EE_H
