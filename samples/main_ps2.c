//------------------------------------------------------------------------
// File:   main_ps2.c
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
#include <GL/gl.h>
#include <GL/dgl.h>

DGLcontext	ctx;

extern void demo_init(void);
extern void demo_tick(void);
extern void demo_end(void);

//------------------------------------------------------------------------
void swap_buffers(void)
{
	dglSwapBuffers();
}

//------------------------------------------------------------------------
int init(void)
{
	sif_rpc_init(0);

	memset(&ctx, 0, sizeof(DGLcontext));

	ctx.ScreenWidth		= 512;
	ctx.ScreenHeight	= 256;
	ctx.ScreenDepth		= 32;
	ctx.ScreenBuffers	= 2;
	ctx.ZDepth			= 32;
	ctx.VSync			= GL_TRUE;

	if(*((char *)0x1FC80000 - 0xAE) == 'E')
		ctx.ps2VidType	= PS2_PAL;
	else
		ctx.ps2VidType	= PS2_NTSC;

	ctx.ps2VidInterlace	= PS2_NONINTERLACED;
	ctx.ps2VidFrame		= PS2_FRAME;

	return(dglInit(&ctx));
}

//------------------------------------------------------------------------
int end(void)
{
	return(DGL_SUCCESS);
}

//------------------------------------------------------------------------
int main(void)
{
	init();

	demo_init();
	while(1) { demo_tick(); }
	demo_end();

	end();
	return(0);
}
