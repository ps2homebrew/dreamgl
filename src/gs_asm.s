#------------------------------------------------------------------------
# File:   gs_asm.s
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
#include "gs_regs.h"

#------------------------------------------------------------------------
.set noreorder

.text
.globl gs_set_imr
.globl gs_set_crtc

#------------------------------------------------------------------------
# void gs_set_imr(void);
#------------------------------------------------------------------------
.align 7
.ent gs_set_imr
gs_set_imr:
	li		a0,0x0000FF00
	ld		v0,csr
	dsrl	v0,16
	andi	v0,0xFF
	li		v1,0x71
	nop
	syscall
	nop

	daddu	v0,zero,zero	# return 0
	jr		ra
	nop
.end gs_set_imr

#------------------------------------------------------------------------
# void gs_set_crtc(uint8 int_mode, uint8 ntsc_pal, uint8 field_mode);
#------------------------------------------------------------------------
.align 7
.ent gs_set_crtc
gs_set_crtc:
	li		v1,0x02			# call SetGsCrt
	syscall
	nop

	daddu	v0,zero,zero	# return 0
	jr		ra
	nop
.end gs_set_crtc

