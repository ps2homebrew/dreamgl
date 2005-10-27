//---------------------------------------------------------------------------
// File:   gif.h
// Author: Tony Saveski, tony@ui.com.au
//---------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//---------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
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
