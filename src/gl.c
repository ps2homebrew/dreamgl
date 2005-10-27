//------------------------------------------------------------------------
// File:   gl.c
// Author: Tony Saveski, tony@ui.com.au
//------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
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
