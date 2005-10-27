//------------------------------------------------------------------------
// File:   dgl.c
// Author: Tony Saveski, tony@ui.com.au
//------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
//------------------------------------------------------------------------
#include <GL/dgl.h>
#include <stdlib.h>
#include "private.h"

DGLcontext *g_ctx=0;	// Pointer to the current process context

//------------------------------------------------------------------------
void SetGLDefaults(void)
{
	//
	// Common DGL Variables
	//
	g_ctx->InsideBeginEnd	= GL_FALSE;

	//
	// GL State Variables
	//
	if(g_ctx->ScreenBuffers == 1)
	{
		g_ctx->glDoublebuffer	= GL_FALSE;
		g_ctx->glDrawBuffer		= GL_FRONT;

		impSetVisibleBuffer(0);
		g_ctx->VisibleBuffer = 0;

		impSetActiveBuffer(0);
		g_ctx->ActiveBuffer = 0;
	}
	else
	{
		g_ctx->glDoublebuffer	= GL_TRUE;

		g_ctx->glDrawBuffer		= GL_BACK;

		impSetVisibleBuffer(0);
		g_ctx->VisibleBuffer = 0;

		impSetActiveBuffer(1);
		g_ctx->ActiveBuffer = 1;
	}

	g_ctx->glError				= GL_NO_ERROR;

	g_ctx->glMatrixMode			= GL_TEXTURE;
	g_ctx->curTextureMatrix		= 0;
	glLoadIdentity();

	g_ctx->glMatrixMode			= GL_PROJECTION;
	g_ctx->curProjectionMatrix	= 0;
	glLoadIdentity();

	g_ctx->glMatrixMode			= GL_MODELVIEW;
	g_ctx->curModelViewMatrix	= 0;
	glLoadIdentity();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord4f(0.0f, 0.0f, 0.0f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, g_ctx->ScreenWidth, g_ctx->ScreenHeight);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	memset(g_ctx->Textures, 0, sizeof(DGLtexture)*DGL_MAX_TEXTURE_ARRAY_ITEMS);
	g_ctx->glTexture2dBinding 	= 0;
	g_ctx->Textures[0].InUse	= GL_TRUE;

	// Server Side GL Capabilities
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

//------------------------------------------------------------------------
int dglInit(DGLcontext *ctx)
{
	if(!ctx) return(DGL_ERROR);
	g_ctx = ctx;

	// Check that all needed context variables are initialized
	if(ctx->ScreenWidth		== 0)						return(DGL_ERROR);
	if(ctx->ScreenHeight	== 0)						return(DGL_ERROR);
	if(ctx->ScreenDepth		== 0)						return(DGL_ERROR);
	if(ctx->ScreenBuffers	== 0)						return(DGL_ERROR);
	if(ctx->ScreenBuffers 	> DGL_MAX_FRAME_BUFFERS)	return(DGL_ERROR);

	// Call the implementation specific Init() function
	if(impDglInit() != DGL_SUCCESS)
	{
		impDglEnd();
		return(DGL_ERROR);
	}

	// Setup all GL and Private Context variables
	SetGLDefaults();

	return(DGL_SUCCESS);
}

//------------------------------------------------------------------------
void dglEnd(void)
{
	impDglEnd();
}

//------------------------------------------------------------------------
void dglSwapBuffers(void)
{
	if(g_ctx->glDoublebuffer == GL_FALSE) return;
	if(g_ctx->VSync == GL_TRUE) impWaitVSync();

	impSetVisibleBuffer(1-g_ctx->VisibleBuffer);
	g_ctx->VisibleBuffer = 1-g_ctx->VisibleBuffer;

	impSetActiveBuffer(1-g_ctx->ActiveBuffer);
	g_ctx->ActiveBuffer = 1-g_ctx->ActiveBuffer;
}
