//------------------------------------------------------------------------
// File:   gl_color.c
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

#define SCALE_COLOR(c, scale)	\
	(((c)>0) ? (GLfloat)((c)/(scale)) : (GLfloat)((c)/((scale)+1)))

//------------------------------------------------------------------------
void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	g_ctx->glCurrentColor[0] = red;
	g_ctx->glCurrentColor[1] = green;
	g_ctx->glCurrentColor[2] = blue;
	g_ctx->glCurrentColor[3] = alpha;

	g_ctx->curColR = (unsigned char)(red   * 255.0f + 0.5f);
	g_ctx->curColG = (unsigned char)(green * 255.0f + 0.5f);
	g_ctx->curColB = (unsigned char)(blue  * 255.0f + 0.5f);
	g_ctx->curColA = (unsigned char)(alpha * 128.0f + 0.5f);
}

//------------------------------------------------------------------------
void glColor4fv(const GLfloat *v)
{
	glColor4f(v[0], v[1], v[2], v[3]);
}

void glColor3f(GLfloat red, GLfloat green, GLfloat blue)
{
	glColor4f(red, green, blue, 1.0f);
}

void glColor3fv(const GLfloat *v)
{
	glColor4f(v[0], v[1], v[2], 1.0f);
}

//------------------------------------------------------------------------
void glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha)
{
	glColor4f((GLfloat)red, (GLfloat)green, (GLfloat)blue, (GLfloat)alpha);
}

void glColor4dv(const GLdouble *v)
{
	glColor4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), (GLfloat)(v[3]));
}

void glColor3d(GLdouble red, GLdouble green, GLdouble blue)
{
	glColor4f((GLfloat)red, (GLfloat)green, (GLfloat)blue, 1.0f);
}

void glColor3dv(const GLdouble *v)
{
	glColor4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), 1.0f);
}

//------------------------------------------------------------------------
void glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxByte),
		SCALE_COLOR(green, dglMaxByte),
		SCALE_COLOR(blue,  dglMaxByte),
		SCALE_COLOR(alpha, dglMaxByte));
}

void glColor4bv(const GLbyte *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxByte),
		SCALE_COLOR(v[1], dglMaxByte),
		SCALE_COLOR(v[2], dglMaxByte),
		SCALE_COLOR(v[3], dglMaxByte));
}

void glColor3b(GLbyte red, GLbyte green, GLbyte blue)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxByte),
		SCALE_COLOR(green, dglMaxByte),
		SCALE_COLOR(blue,  dglMaxByte),
		1.0f);
}

void glColor3bv(const GLbyte *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxByte),
		SCALE_COLOR(v[1], dglMaxByte),
		SCALE_COLOR(v[2], dglMaxByte),
		1.0f);
}

//------------------------------------------------------------------------
void glColor4i(GLint red, GLint green, GLint blue, GLint alpha)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxInt),
		SCALE_COLOR(green, dglMaxInt),
		SCALE_COLOR(blue,  dglMaxInt),
		SCALE_COLOR(alpha, dglMaxInt));
}

void glColor4iv(const GLint *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxInt),
		SCALE_COLOR(v[1], dglMaxInt),
		SCALE_COLOR(v[2], dglMaxInt),
		SCALE_COLOR(v[3], dglMaxInt));
}

void glColor3i(GLint red, GLint green, GLint blue)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxInt),
		SCALE_COLOR(green, dglMaxInt),
		SCALE_COLOR(blue,  dglMaxInt),
		1.0f);
}

void glColor3iv(const GLint *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxInt),
		SCALE_COLOR(v[1], dglMaxInt),
		SCALE_COLOR(v[2], dglMaxInt),
		1.0f);
}

//------------------------------------------------------------------------
void glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxShort),
		SCALE_COLOR(green, dglMaxShort),
		SCALE_COLOR(blue,  dglMaxShort),
		SCALE_COLOR(alpha, dglMaxShort));
}

void glColor4sv(const GLshort *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxShort),
		SCALE_COLOR(v[1], dglMaxShort),
		SCALE_COLOR(v[2], dglMaxShort),
		SCALE_COLOR(v[3], dglMaxShort));
}

void glColor3s(GLshort red, GLshort green, GLshort blue)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxShort),
		SCALE_COLOR(green, dglMaxShort),
		SCALE_COLOR(blue,  dglMaxShort),
		1.0f);
}

void glColor3sv(const GLshort *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxShort),
		SCALE_COLOR(v[1], dglMaxShort),
		SCALE_COLOR(v[2], dglMaxShort),
		1.0f);
}

//------------------------------------------------------------------------
void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxUbyte),
		SCALE_COLOR(green, dglMaxUbyte),
		SCALE_COLOR(blue,  dglMaxUbyte),
		SCALE_COLOR(alpha, dglMaxUbyte));
}

void glColor4ubv(const GLubyte *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxUbyte),
		SCALE_COLOR(v[1], dglMaxUbyte),
		SCALE_COLOR(v[2], dglMaxUbyte),
		SCALE_COLOR(v[3], dglMaxUbyte));
}

void glColor3ub(GLubyte red, GLubyte green, GLubyte blue)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxUbyte),
		SCALE_COLOR(green, dglMaxUbyte),
		SCALE_COLOR(blue,  dglMaxUbyte),
		1.0f);
}

void glColor3ubv(const GLubyte *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxUbyte),
		SCALE_COLOR(v[1], dglMaxUbyte),
		SCALE_COLOR(v[2], dglMaxUbyte),
		1.0f);
}

//------------------------------------------------------------------------
void glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxUint),
		SCALE_COLOR(green, dglMaxUint),
		SCALE_COLOR(blue,  dglMaxUint),
		SCALE_COLOR(alpha, dglMaxUint));
}

void glColor4uiv(const GLuint *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxUint),
		SCALE_COLOR(v[1], dglMaxUint),
		SCALE_COLOR(v[2], dglMaxUint),
		SCALE_COLOR(v[3], dglMaxUint));
}

void glColor3ui(GLuint red, GLuint green, GLuint blue)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxUint),
		SCALE_COLOR(green, dglMaxUint),
		SCALE_COLOR(blue,  dglMaxUint),
		1.0f);
}

void glColor3uiv(const GLuint *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxUint),
		SCALE_COLOR(v[1], dglMaxUint),
		SCALE_COLOR(v[2], dglMaxUint),
		1.0f);
}

//------------------------------------------------------------------------
void glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxUshort),
		SCALE_COLOR(green, dglMaxUshort),
		SCALE_COLOR(blue,  dglMaxUshort),
		SCALE_COLOR(alpha, dglMaxUshort));
}

void glColor4usv(const GLushort *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxUshort),
		SCALE_COLOR(v[1], dglMaxUshort),
		SCALE_COLOR(v[2], dglMaxUshort),
		SCALE_COLOR(v[3], dglMaxUshort));
}

void glColor3us(GLushort red, GLushort green, GLushort blue)
{
	glColor4f(
		SCALE_COLOR(red,   dglMaxUshort),
		SCALE_COLOR(green, dglMaxUshort),
		SCALE_COLOR(blue,  dglMaxUshort),
		1.0f);
}

void glColor3usv(const GLushort *v)
{
	glColor4f(
		SCALE_COLOR(v[0], dglMaxUshort),
		SCALE_COLOR(v[1], dglMaxUshort),
		SCALE_COLOR(v[2], dglMaxUshort),
		1.0f);
}

