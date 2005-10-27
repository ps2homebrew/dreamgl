//------------------------------------------------------------------------
// File:   gl_texture.c
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
void glGenTextures(GLsizei n, GLuint *textures)
{
int dtex;
int allocated;

	CHECK_BEGIN_END();
	if(n<0) { SET_GL_ERROR(GL_INVALID_VALUE); return; }

	allocated=0;
	for(dtex=1; dtex<DGL_MAX_TEXTURE_ARRAY_ITEMS; dtex++)
	{
		if(g_ctx->Textures[dtex].InUse == GL_FALSE)
		{
			g_ctx->Textures[dtex].InUse 	= GL_TRUE;
			g_ctx->Textures[dtex].MinFilter	= GL_LINEAR;
			g_ctx->Textures[dtex].MagFilter	= GL_LINEAR;
			g_ctx->Textures[dtex].WrapS		= GL_REPEAT;
			g_ctx->Textures[dtex].WrapT		= GL_REPEAT;
			g_ctx->Textures[dtex].Resident	= GL_FALSE;

			textures[allocated] = dtex;
			allocated++;
			if(allocated==n) return;
		}
	}

	// if we get to here then there weren't enough unused texture slots available
	SET_GL_ERROR(GL_OUT_OF_MEMORY);
}

//------------------------------------------------------------------------
void glDeleteTextures(GLsizei n, const GLuint *textures)
{
int i;

	CHECK_BEGIN_END();
	if(n<0) { SET_GL_ERROR(GL_INVALID_VALUE); return; }

	for(i=0; i<n; i++)
	{
		if(textures[i] < DGL_MAX_TEXTURE_ARRAY_ITEMS)
		{
			if(g_ctx->glTexture2dBinding == textures[i]) g_ctx->glTexture2dBinding = 0;
			memset(&(g_ctx->Textures[textures[i]]), 0, sizeof(DGLtexture));
		}
	}
}

//------------------------------------------------------------------------
GLboolean glIsTexture(GLuint texture)
{
	if(g_ctx->InsideBeginEnd == GL_TRUE) { SET_GL_ERROR(GL_INVALID_OPERATION); return(GL_FALSE); }

	if(texture==0 || texture>=DGL_MAX_TEXTURE_ARRAY_ITEMS) return(GL_FALSE);
	if(g_ctx->Textures[texture].InUse == GL_TRUE) return(GL_TRUE);
	return(GL_FALSE);
}

//------------------------------------------------------------------------
void glBindTexture(GLenum target, GLuint texture)
{
DGLtexture	*tex;
GLuint		old_2d_binding;

	CHECK_BEGIN_END();
//	if(g_ctx->glTexture2d == GL_FALSE) return;
	if(target!=GL_TEXTURE_2D) 					{ SET_GL_ERROR(GL_INVALID_ENUM); return; }
	if(texture>=DGL_MAX_TEXTURE_ARRAY_ITEMS) 	{ SET_GL_ERROR(GL_INVALID_VALUE); return; }

	// Check if it's texture 0 being bound
	if(texture!=0)
	{
		// If texture is not already allocated then allocate it
		if(glIsTexture(texture)==GL_FALSE) g_ctx->Textures[texture].InUse = GL_TRUE;

		// If texture is being bound for the first time, it takes on dimensionality of target -
		// If texture has already been bound before, then it must be the same dim as target.
		if(g_ctx->Textures[texture].Dim == 0) g_ctx->Textures[texture].Dim = target;
		else if(g_ctx->Textures[texture].Dim != target) { SET_GL_ERROR(GL_INVALID_OPERATION); return; }
	}
	else
	{
		// TODO: handling for texture 0
	}

	// Let's set the binding
	old_2d_binding = g_ctx->glTexture2dBinding;
	if(old_2d_binding == texture) return;

	// Old texture will no longer be resident
	g_ctx->Textures[old_2d_binding].Resident = GL_FALSE;

	g_ctx->glTexture2dBinding = texture;

	tex = &(g_ctx->Textures[texture]);
	if(texture!=0 && tex->Pixels && tex->Resident==GL_FALSE)
	{
		// Load the texture into video memory and mark it as resident
		impLoadTexture(0, 0, tex->Width, tex->Height, (uint32)(tex->Pixels), g_ctx->ps2TexbufAddr);
		tex->Resident = GL_TRUE;
	}
}

//------------------------------------------------------------------------
void glTexImage2D(GLenum target, GLint level, GLint components, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
DGLtexture *tex;

	CHECK_BEGIN_END();
//	if(g_ctx->glTexture2d == GL_FALSE) return;
	if(target!=GL_TEXTURE_2D)					{ SET_GL_ERROR(GL_INVALID_ENUM); return; }
	if(level!=0)								{ SET_GL_ERROR(GL_INVALID_VALUE); return; }
	if(components<1 || components>4)			{ SET_GL_ERROR(GL_INVALID_VALUE); return; }
	if(width<0 || width>DGL_MAX_TEXTURE_SIZE)	{ SET_GL_ERROR(GL_INVALID_VALUE); return; }
	if(height<0 || height>DGL_MAX_TEXTURE_SIZE)	{ SET_GL_ERROR(GL_INVALID_VALUE); return; }
	if(border!=0 && border!=1) 					{ SET_GL_ERROR(GL_INVALID_VALUE); return; }
	if(format!=GL_RGBA) 						{ SET_GL_ERROR(GL_INVALID_ENUM); return; }
	if(type!=GL_UNSIGNED_BYTE) 					{ SET_GL_ERROR(GL_INVALID_ENUM); return; }

	if(g_ctx->glTexture2dBinding==0) return;

	tex = &(g_ctx->Textures[g_ctx->glTexture2dBinding]);

	// TODO: This must be malloc'd and copied I think...check spec
	tex->Pixels		= (GLvoid *)pixels;
	tex->Width		= width;
	tex->Height		= height;

	// Load the texture into video memory and mark it as resident
	impLoadTexture(0, 0, tex->Width, tex->Height, (uint32)(tex->Pixels), g_ctx->ps2TexbufAddr);
	tex->Resident = GL_TRUE;
}

//------------------------------------------------------------------------
void glTexEnvf(GLenum target, GLenum pname, GLfloat param)
{
	glTexEnvi(target, pname, (GLint)param);
}

//------------------------------------------------------------------------
void glTexEnvi(GLenum target, GLenum pname, GLint param)
{
	CHECK_BEGIN_END();
	if(target!=GL_TEXTURE_ENV)					{ SET_GL_ERROR(GL_INVALID_ENUM); return; }
	if(pname!=GL_TEXTURE_ENV_MODE)				{ SET_GL_ERROR(GL_INVALID_ENUM); return; }
	if(param!=GL_DECAL && param!=GL_MODULATE)	{ SET_GL_ERROR(GL_INVALID_ENUM); return; }

	g_ctx->glTextureEnvMode = param;
	impSetTextureEnvMode();
}

//------------------------------------------------------------------------
void glTexEnvfv(GLenum target, GLenum pname, const GLfloat *params)
{
	glTexEnvi(target, pname, (GLint)(*params));
}

//------------------------------------------------------------------------
void glTexEnviv(GLenum target, GLenum pname, const GLint *params)
{
	glTexEnvi(target, pname, *params);
}

//------------------------------------------------------------------------
void glGetTexEnvfv(GLenum target, GLenum pname, GLfloat *params)
{
	CHECK_BEGIN_END();
	if(target==GL_TEXTURE_ENV && pname!=GL_TEXTURE_ENV_MODE)
	{
		*params = (GLfloat)(g_ctx->glTextureEnvMode);
		return;
	}

	SET_GL_ERROR(GL_INVALID_ENUM);
}

//------------------------------------------------------------------------
void glGetTexEnviv(GLenum target, GLenum pname, GLint *params)
{
	CHECK_BEGIN_END();
	if(target==GL_TEXTURE_ENV && pname==GL_TEXTURE_ENV_MODE)
	{
		*params = g_ctx->glTextureEnvMode;
		return;
	}

	SET_GL_ERROR(GL_INVALID_ENUM);
}

/*
//------------------------------------------------------------------------
void glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
}

//------------------------------------------------------------------------
void glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params)
{
}
*/
//------------------------------------------------------------------------
void glTexParameteri(GLenum target, GLenum pname, GLint param)
{
DGLtexture *tex;

	CHECK_BEGIN_END();
	if(target!=GL_TEXTURE_2D)	{ SET_GL_ERROR(GL_INVALID_ENUM); return; }

	// GL_TEXTURE_2D
	tex = &(g_ctx->Textures[g_ctx->glTexture2dBinding]);

	if(pname==GL_TEXTURE_MIN_FILTER)	{ tex->MinFilter = param; impSetTextureMinMag(); return; }
	if(pname==GL_TEXTURE_MAG_FILTER)	{ tex->MagFilter = param; impSetTextureMinMag(); return; }
	if(pname==GL_TEXTURE_WRAP_S)		{ tex->WrapS = param; impSetTextureWrap(); return; }
	if(pname==GL_TEXTURE_WRAP_T)		{ tex->WrapT = param; impSetTextureWrap(); return; }

	SET_GL_ERROR(GL_INVALID_ENUM);
}
/*
//------------------------------------------------------------------------
void glTexParameteriv(GLenum target, GLenum pname, const GLint *params)
{
}
*/
