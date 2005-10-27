//------------------------------------------------------------------------
// File:   gl_texcoord.c
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

#define DEF_S	(0.0f)
#define DEF_T	(0.0f)
#define DEF_R	(0.0f)
#define DEF_Q	(1.0f)

//------------------------------------------------------------------------
void glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
	g_ctx->glCurrentTextureCoords[TEXCOORD_S] = s;
	g_ctx->glCurrentTextureCoords[TEXCOORD_T] = t;
	g_ctx->glCurrentTextureCoords[TEXCOORD_R] = r;
	g_ctx->glCurrentTextureCoords[TEXCOORD_Q] = q;
}

//------------------------------------------------------------------------
void glTexCoord4fv(const GLfloat *v)
{
	glTexCoord4f(v[0], v[1], v[2], v[3]);
}

void glTexCoord3f(GLfloat s, GLfloat t, GLfloat r)
{
	glTexCoord4f(s, t, r, DEF_Q);
}

void glTexCoord3fv(const GLfloat *v)
{
	glTexCoord4f(v[0], v[1], v[2], DEF_Q);
}

void glTexCoord2f(GLfloat s, GLfloat t)
{
	glTexCoord4f(s, t, DEF_R, DEF_Q);
}

void glTexCoord2fv(const GLfloat *v)
{
	glTexCoord4f(v[0], v[1], DEF_R, DEF_Q);
}

void glTexCoord1f(GLfloat s)
{
	glTexCoord4f(s, DEF_T, DEF_R, DEF_Q);
}

void glTexCoord1fv(const GLfloat *v)
{
	glTexCoord4f(v[0], DEF_T, DEF_R, DEF_Q);
}

//------------------------------------------------------------------------
void glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
	glTexCoord4f((GLfloat)s, (GLfloat)t, (GLfloat)r, (GLfloat)q);
}

void glTexCoord4dv(const GLdouble *v)
{
	glTexCoord4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), (GLfloat)(v[3]));
}

void glTexCoord3d(GLdouble s, GLdouble t, GLdouble r)
{
	glTexCoord4f((GLfloat)s, (GLfloat)t, (GLfloat)r, DEF_Q);
}

void glTexCoord3dv(const GLdouble *v)
{
	glTexCoord4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), DEF_Q);
}

void glTexCoord2d(GLdouble s, GLdouble t)
{
	glTexCoord4f((GLfloat)s, (GLfloat)t, DEF_R, DEF_Q);
}

void glTexCoord2dv(const GLdouble *v)
{
	glTexCoord4f((GLfloat)(v[0]), (GLfloat)(v[1]), DEF_R, DEF_Q);
}

void glTexCoord1d(GLdouble s)
{
	glTexCoord4f((GLfloat)s, DEF_T, DEF_R, DEF_Q);
}

void glTexCoord1dv(const GLdouble *v)
{
	glTexCoord4f((GLfloat)(v[0]), DEF_T, DEF_R, DEF_Q);
}

//------------------------------------------------------------------------
void glTexCoord4i(GLint s, GLint t, GLint r, GLint q)
{
	glTexCoord4f((GLfloat)s, (GLfloat)t, (GLfloat)r, (GLfloat)q);
}

void glTexCoord4iv(const GLint *v)
{
	glTexCoord4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), (GLfloat)(v[3]));
}

void glTexCoord3i(GLint s, GLint t, GLint r)
{
	glTexCoord4f((GLfloat)s, (GLfloat)t, (GLfloat)r, DEF_Q);
}

void glTexCoord3iv(const GLint *v)
{
	glTexCoord4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), DEF_Q);
}

void glTexCoord2i(GLint s, GLint t)
{
	glTexCoord4f((GLfloat)s, (GLfloat)t, DEF_R, DEF_Q);
}

void glTexCoord2iv(const GLint *v)
{
	glTexCoord4f((GLfloat)(v[0]), (GLfloat)(v[1]), DEF_R, DEF_Q);
}

void glTexCoord1i(GLint s)
{
	glTexCoord4f((GLfloat)s, DEF_T, DEF_R, DEF_Q);
}

void glTexCoord1iv(const GLint *v)
{
	glTexCoord4f((GLfloat)(v[0]), DEF_T, DEF_R, DEF_Q);
}

//------------------------------------------------------------------------
void glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q)
{
	glTexCoord4f((GLfloat)s, (GLfloat)t, (GLfloat)r, (GLfloat)q);
}

void glTexCoord4sv(const GLshort *v)
{
	glTexCoord4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), (GLfloat)(v[3]));
}

void glTexCoord3s(GLshort s, GLshort t, GLshort r)
{
	glTexCoord4f((GLfloat)s, (GLfloat)t, (GLfloat)r, DEF_Q);
}

void glTexCoord3sv(const GLshort *v)
{
	glTexCoord4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), DEF_Q);
}

void glTexCoord2s(GLshort s, GLshort t)
{
	glTexCoord4f((GLfloat)s, (GLfloat)t, DEF_R, DEF_Q);
}

void glTexCoord2sv(const GLshort *v)
{
	glTexCoord4f((GLfloat)(v[0]), (GLfloat)(v[1]), DEF_R, DEF_Q);
}

void glTexCoord1s(GLshort s)
{
	glTexCoord4f((GLfloat)s, DEF_T, DEF_R, DEF_Q);
}

void glTexCoord1sv(const GLshort *v)
{
	glTexCoord4f((GLfloat)(v[0]), DEF_T, DEF_R, DEF_Q);
}
