//------------------------------------------------------------------------
// File:   ee.h
// Author: Tony Saveski, tony@ui.com.au
//------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
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
