//------------------------------------------------------------------------
// File:   gl_enable.c
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

//------------------------------------------------------------------------
void EnableDisable(GLenum cap, GLboolean op)
{
	switch(cap)
	{
	case GL_DEPTH_TEST:
		g_ctx->glDepthTest = op;
		impSetDepthTest();
		break;
	case GL_TEXTURE_2D:
		g_ctx->glTexture2d = op;
		impSetTexture2d();
		break;
	default:
		SET_GL_ERROR(GL_INVALID_ENUM);
		return;
	}
}

//------------------------------------------------------------------------
void glEnable(GLenum cap)
{
	CHECK_BEGIN_END();
	EnableDisable(cap, GL_TRUE);
}

//------------------------------------------------------------------------
void glDisable(GLenum cap)
{
	CHECK_BEGIN_END();
	EnableDisable(cap, GL_FALSE);
}

//------------------------------------------------------------------------
GLboolean glIsEnabled(GLenum cap)
{
	if(g_ctx->InsideBeginEnd == GL_TRUE) { SET_GL_ERROR(GL_INVALID_OPERATION); return(GL_FALSE); }

	switch(cap)
	{
	case GL_DEPTH_TEST:
		return(g_ctx->glDepthTest);
		break;
	case GL_TEXTURE_2D:
		return(g_ctx->glTexture2d);
		break;
	default:
		SET_GL_ERROR(GL_INVALID_ENUM);
		return(GL_FALSE);
	}
}
