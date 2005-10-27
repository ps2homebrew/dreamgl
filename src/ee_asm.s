#------------------------------------------------------------------------
# File:   ee_asm.s
# Author: Tony Saveski, tony@ui.com.au
#------------------------------------------------------------------------
# Copyright (c) 2003, Unicorn Interactive Pty Ltd.
# All Rights Reserved.
#------------------------------------------------------------------------
# Licenced under Academic Free License version 2.0
# Read DreamGL LICENSE.txt file for further details.
#------------------------------------------------------------------------

#include "ee_regs.h"

#------------------------------------------------------------------------
.set noreorder

.text
.globl ee_flush_cache

#------------------------------------------------------------------------
# void ee_flush_cache(int); 			Flushes the EE Data Cache.
#------------------------------------------------------------------------
.align 7
.ent ee_flush_cache
ee_flush_cache:
	li	$3,100
	syscall
	jr	$31
	nop
.end ee_flush_cache

