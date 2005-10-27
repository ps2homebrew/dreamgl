//------------------------------------------------------------------------
// File:   ee.c
// Author: Tony Saveski, tony@ui.com.au
//------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
//------------------------------------------------------------------------
#include "ee.h"
#include "ee_regs.h"

// TODO: wow...just looked in here for the first time since writing it. What a mess!
//       Will clean up for version 0.3 ... maybe :)

static uint32 t_count[4] = { t0_count, t1_count, t2_count, t3_count };
static uint32 t_mode[4]  = { t0_mode,  t1_mode,  t2_mode,  t3_mode  };
static uint32 t_cres[4]  = { 0, 0, 0, 0 }; 		// current clock resolution

//static uint32 t_ticks[4] = { 2500000, 156250, 9760, 262 };	// ticks per VBLANK for each resolution
static uint32 t_v_per_sec=0;

//------------------------------------------------------------------------
void ee_timer_init(int timer, int resolution)
{
//	if(timer<0 || timer>3) return;
	t_cres[timer] = resolution;
	*((volatile uint32 *)(t_mode[timer])) = T_MODE(t_cres[timer], 0, 0, 0, 0, 0, 0, 0, 0, 0);

	if(*((char *)0x1FC80000 - 0xAE) == 'E')
		t_v_per_sec = 50; // PAL
	else
		t_v_per_sec = 60; // NTSC
}

//------------------------------------------------------------------------
void ee_timer_start(int timer)
{
//	if(timer<0 || timer>3) return;
	*((volatile uint32 *)(t_count[timer])) = 0;
	*((volatile uint32 *)(t_mode[timer])) = T_MODE(t_cres[timer], 0, 0, 0, 0, 1, 0, 0, 0, 0);
}

//------------------------------------------------------------------------
void ee_timer_stop(int timer)
{
//	if(timer<0 || timer>3) return;
	*((volatile uint32 *)(t_mode[timer])) = T_MODE(t_cres[timer], 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

//------------------------------------------------------------------------
uint32 ee_timer_get_ticks(int timer)
{
//	if(timer<0 || timer>3) return(0);
	return *((volatile uint32 *)(t_count[timer]));
}
/*
//------------------------------------------------------------------------
uint32 ee_timer_get_msec(int timer)
{
	return(ee_timer_get_ticks(timer)/((t_ticks[t_cres[timer]]*t_v_per_sec)/1000));
}
*/
