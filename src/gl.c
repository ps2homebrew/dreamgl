//------------------------------------------------------------------------
// File:   gl.c
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
#include <GL/dgl.h>
#include "private.h"
#include "gs.h"
#include "gif.h"

DECLARE_EXTERN_GS_PACKET(gs_dma_buf);

//------------------------------------------------------------------------
GLenum glGetError(void)
{
GLenum err;

	if(g_ctx->InsideBeginEnd == GL_TRUE)
	{
		SET_GL_ERROR(GL_INVALID_OPERATION);
		return(0);
	}

	err = g_ctx->glError;
	g_ctx->glError = GL_NO_ERROR;
	return(err);
}

//------------------------------------------------------------------------
void glBegin(GLenum mode)
{
uint8 gs_prim;

	CHECK_BEGIN_END();
	g_ctx->InsideBeginEnd 	= GL_TRUE;

	switch(mode)
	{
		case GL_POINTS:			gs_prim = PRIM_POINT;		break;
		case GL_LINES:			gs_prim = PRIM_LINE;		break;
		case GL_LINE_LOOP:		gs_prim = PRIM_LINE_STRIP;	break;
		case GL_LINE_STRIP:		gs_prim = PRIM_LINE_STRIP;	break;
		case GL_TRIANGLES:		gs_prim = PRIM_TRI;			break;
		case GL_TRIANGLE_STRIP:	gs_prim = PRIM_TRI_STRIP;	break;
		case GL_TRIANGLE_FAN:	gs_prim = PRIM_TRI_FAN;		break;
		default:				gs_prim = PRIM_POINT;		break;
	}
	GIF_DATA_AD(gs_dma_buf, prim, GS_PRIM(gs_prim, 0, 0, 0, 0, 0, 0, 0, 0));
}

//------------------------------------------------------------------------
void glEnd(void)
{
	if(g_ctx->InsideBeginEnd == GL_FALSE) { SET_GL_ERROR(GL_INVALID_OPERATION); return; }
	g_ctx->InsideBeginEnd = GL_FALSE;
}

//------------------------------------------------------------------------
void glClear(GLbitfield mask)
{
	CHECK_BEGIN_END();

	// TODO: GL_INVALID_VALUE if any bits other than 4 supported ones are selected
	// TODO: Check that Scissor region is the only thing cleared.

	// Check ColorBufferBit and DepthBufferBit for fast clear
	if((mask & GL_COLOR_BUFFER_BIT) && (mask & GL_DEPTH_BUFFER_BIT))
	{
		impClearScreenAndZBuffer(
			g_ctx->glColorClearValue[COLOR_R],
			g_ctx->glColorClearValue[COLOR_G],
			g_ctx->glColorClearValue[COLOR_B]);
	}
	else
	{
		// Check ColorBufferBit on its own
		if(mask & GL_COLOR_BUFFER_BIT)
			impClearScreen(
				g_ctx->glColorClearValue[COLOR_R],
				g_ctx->glColorClearValue[COLOR_G],
				g_ctx->glColorClearValue[COLOR_B]);

		// Check DepthBufferBit on its own
		if(mask & GL_DEPTH_BUFFER_BIT)
			impClearZBuffer();
	}
}

//------------------------------------------------------------------------
void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	CHECK_BEGIN_END();

	// Clamp to [0, 1]
	CLAMP_0(red);
	CLAMP_0(green);
	CLAMP_0(blue);
	CLAMP_0(alpha);

	CLAMP_1(red);
	CLAMP_1(green);
	CLAMP_1(blue);
	CLAMP_1(alpha);

	// Assign to GL variable
	g_ctx->glColorClearValue[COLOR_R] = red;
	g_ctx->glColorClearValue[COLOR_G] = green;
	g_ctx->glColorClearValue[COLOR_B] = blue;
	g_ctx->glColorClearValue[COLOR_A] = alpha;
}

//------------------------------------------------------------------------
// NOTE: I'm not going to support drawing to multiple buffers at the
//       same time yet.
//
void glDrawBuffer(GLenum mode)
{
	CHECK_BEGIN_END();

	if(mode != GL_FRONT && mode != GL_BACK)
	{
		SET_GL_ERROR(GL_INVALID_ENUM);
		return;
	}

	if(mode == GL_BACK && g_ctx->glDoublebuffer == GL_FALSE)
	{
		SET_GL_ERROR(GL_INVALID_OPERATION);
		return;
	}

	g_ctx->glDrawBuffer = mode;
	if(mode == GL_FRONT)
	{
		impSetActiveBuffer(g_ctx->VisibleBuffer);
		g_ctx->ActiveBuffer = g_ctx->VisibleBuffer;
	}
	else
	{
		impSetActiveBuffer(1-g_ctx->VisibleBuffer);
		g_ctx->ActiveBuffer = 1-g_ctx->VisibleBuffer;
	}
}

//------------------------------------------------------------------------
void glFinish(void)
{
}

//------------------------------------------------------------------------
void glFlush(void)
{
	CHECK_BEGIN_END();

	// Kick off the DMA transfer to the GS
	SEND_GS_PACKET(gs_dma_buf);

	// Initialize the next DMA buffer
	BEGIN_GS_PACKET(gs_dma_buf);
	GIF_TAG_AD(gs_dma_buf, 1, 0, 0, 0);
}

//------------------------------------------------------------------------
void glShadeModel(GLenum mode)
{
	CHECK_BEGIN_END();
	if(mode!=GL_SMOOTH && mode!=GL_FLAT) { SET_GL_ERROR(GL_INVALID_ENUM); return; }

	g_ctx->glShadeModel = mode;
	impSetShadeMode();
}

//------------------------------------------------------------------------
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	CHECK_BEGIN_END();
	if(width<0 || height<0) { SET_GL_ERROR(GL_INVALID_VALUE); return; }

	g_ctx->glViewport[COORD_X] 		= x;
	g_ctx->glViewport[COORD_Y] 		= y;
	g_ctx->glViewport[COORD_WIDTH] 	= width;
	g_ctx->glViewport[COORD_HEIGHT]	= height;
}

//------------------------------------------------------------------------
void glDepthFunc(GLenum func)
{
	CHECK_BEGIN_END();
	if(func!=GL_NEVER && func!=GL_LESS && func!=GL_LEQUAL && func!=GL_ALWAYS)
	{
		SET_GL_ERROR(GL_INVALID_ENUM);
		return;
	}

	g_ctx->glDepthFunc = func;
	impSetDepthFunc();
}

//------------------------------------------------------------------------
void glDepthMask(GLboolean flag)
{
	CHECK_BEGIN_END();

	g_ctx->glDepthWriteMask = flag;
	impSetDepthTest();
}
