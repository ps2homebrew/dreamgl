#------------------------------------------------------------------------
# File:   dma_asm.s
# Author: Tony Saveski, tony@ui.com.au
#------------------------------------------------------------------------
# Copyright (c) 2003, Unicorn Interactive Pty Ltd.
# All Rights Reserved.
#------------------------------------------------------------------------
# This software (hereafter, "Software") is the property of Unicorn
# Interactive Pty Ltd (hereafter, "Unicorn"). The following conditions
# apply:
#
# * Unicorn grants you (hereafter, "Licensee") a license to use the
#   Software for academic, research and non-commercial purposes only,
#   without a fee. Licensees may distribute unmodified versions of the
#   binary and source code of the Software to third parties under the
#   terms of this license but must ensure that such distribution is under
#   the terms of this license and this license is distributed along with
#   the binaries and source.
#
# * Unicorn imposes the following restrictions on any code developed
#   using the Software:
#   - Unicorn retains a non-exclusive royalty-free license, including the
#     right of redistribution, to any modifications to the Software made
#     by the licensee.
#   - You may not distribute modified versions of the Software.
#
# * Any Licensee wishing to make commercial use of the Software should
#   contact Unicorn to negotiate an appropriate license for such
#   commercial use. Commercial use includes but is not limited to:
#   - integration of all or part of the source code into a product for
#     sale or commercial license by or on behalf of Licensee to third
#     parties, or
#   - distribution of the binary code or source code to third parties
#     that need it to utilize a commercial product sold or licensed by or
#     on behalf of Licensee, or
#   - use in an internal operational environment.
#
#   Please email info@ui.com.au for details.
#
# THIS SOFTWARE IS BEING PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT
# LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# IN NO EVENT SHALL UNICORN INTERACTIVE PTY LTD BE LIABLE FOR ANY SPECIAL,
# INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY
# DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY
# THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THE SOFTWARE.
#
# Unicorn welcome comments and bug fixes related to the Software.
# Please address any queries, comments or bug fixes to the address below:
#
#   E-Mail: info@ui.com.au
#------------------------------------------------------------------------

#include "ee_regs.h"

#------------------------------------------------------------------------
.set noreorder

.text
.globl dma_reset

#------------------------------------------------------------------------
# void dma_reset();
#------------------------------------------------------------------------
# Ripped straight from 3stars or something. Will 'clean up later'.
#------------------------------------------------------------------------
.align 7
.ent dma_reset
dma_reset:
	li	$2,0x1000A000
	nop
	sw	$0,0x80($2)
	sw	$0,0($2)
	sw	$0,0x30($2)
	sw	$0,0x10($2)
	sw	$0,0x50($2)
	sw	$0,0x40($2)
	li	$2,0xFF1F
	sw	$2,0x1000E010
	lw	$2,0x1000E010
	li	$3,0xFF1F
	and	$2,$3
	sw	$2,0x1000E010
	sw	$0,0x1000E000
	sw	$0,0x1000E020
	sw	$0,0x1000E030
	sw	$0,0x1000E050
	sw	$0,0x1000E040
	li	$3,1
	lw	$2,0x1000E000
	ori	$3,$2,1
	nop
	sw	$3,0x1000E000
	nop

	daddu	v0,zero,zero	# return 0
	jr		ra
	nop
.end dma_reset

