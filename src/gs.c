//---------------------------------------------------------------------------
// File:   gs.c
// Author: Tony Saveski, tony@ui.com.au
//---------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//---------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
//---------------------------------------------------------------------------
#include "ee.h"
#include "gs.h"
#include "gif.h"
#include "dma.h"

//---------------------------------------------------------------------------
DECLARE_EXTERN_GS_PACKET(gs_dma_buf);

//---------------------------------------------------------------------------
uint8 gs_is_ntsc(void)
{
	if(*((char *)0x1FC80000 - 0xAE) != 'E') return(1);
	return(0);
}

//---------------------------------------------------------------------------
uint8 gs_is_pal(void)
{
	if(*((char *)0x1FC80000 - 0xAE) == 'E') return(1);
	return(0);
}

//---------------------------------------------------------------------------
void gs_wait_hsync(void)
{
	*CSR = *CSR & 4;
	while(!(*CSR & 4));
}

