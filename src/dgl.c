//------------------------------------------------------------------------
// File:   dgl.c
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
