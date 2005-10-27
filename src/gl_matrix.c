//------------------------------------------------------------------------
// File:   gl_matrix.c
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
#include <math.h>
#include "private.h"

//------------------------------------------------------------------------
static GLfloat *GetCurrentMatrix(void)
{
	switch(g_ctx->glMatrixMode)
	{
	case GL_MODELVIEW:
		return(&(g_ctx->matModelView[g_ctx->curModelViewMatrix][0]));
		break;

	case GL_PROJECTION:
		return(&(g_ctx->matProjection[g_ctx->curProjectionMatrix][0]));
		break;

	case GL_TEXTURE:
		return(&(g_ctx->matTexture[g_ctx->curTextureMatrix][0]));
		break;

	default:
		return(NULL);
	}
	return(NULL);
}

//------------------------------------------------------------------------
void glLoadIdentity(void)
{
GLfloat *m;

	CHECK_BEGIN_END();

	m = GetCurrentMatrix();
	memset(m, 0, sizeof(GLfloat)*16);
	m[0]  = 1.0f;
	m[5]  = 1.0f;
	m[10] = 1.0f;
	m[15] = 1.0f;
}

//------------------------------------------------------------------------
void glLoadMatrixd(const GLdouble *m)
{
GLfloat	*cur;
GLdouble *tm;
int i;

	CHECK_BEGIN_END();

	cur = GetCurrentMatrix();
	for(cur=0, i=0, tm=(GLdouble *)m; i<16; i++, cur++, tm++)
		*cur = (GLfloat)(*tm);
}

//------------------------------------------------------------------------
void glLoadMatrixf(const GLfloat *m)
{
GLfloat *cur;

	CHECK_BEGIN_END();

	cur = GetCurrentMatrix();
	memcpy(cur, m, sizeof(GLfloat)*16);
}

//------------------------------------------------------------------------
void glMatrixMode(GLenum mode)
{
//	CHECK_BEGIN_END(); used in renderer... TODO: need to change the way this begin/end error is checked

	// Assign mode or return error
	if(mode==GL_MODELVIEW || mode==GL_PROJECTION || mode==GL_TEXTURE)
		g_ctx->glMatrixMode = mode;
	else
		SET_GL_ERROR(GL_INVALID_ENUM);
}

//------------------------------------------------------------------------
void glMultMatrixd(const GLdouble *m)
{
GLfloat	mf[16];
GLfloat	*pf;
const GLdouble	*pd;
int	i;

	for(i=0, pf=mf, pd=m; i<16; i++, pf++, pd++)
		*pf = (GLfloat)(*pd);

	glMultMatrixf(mf);
}

//------------------------------------------------------------------------
void glMultMatrixf(const GLfloat *m)
{
GLfloat	*cur;
GLfloat	res[16];
GLfloat	a0, a1, a2, a3;
GLfloat m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15;

	cur = GetCurrentMatrix();

	m0  = m[0];
	m1  = m[1];
	m2  = m[2];
	m3  = m[3];
	m4  = m[4];
	m5  = m[5];
	m6  = m[6];
	m7  = m[7];
	m8  = m[8];
	m9  = m[9];
	m10 = m[10];
	m11 = m[11];
	m12 = m[12];
	m13 = m[13];
	m14 = m[14];
	m15 = m[15];

	a0 = cur[0];
	a1 = cur[4];
	a2 = cur[8];
	a3 = cur[12];
	res[0]  = a0*m0  + a1*m1  + a2*m2  + a3*m3;
	res[4]  = a0*m4  + a1*m5  + a2*m6  + a3*m7;
	res[8]  = a0*m8  + a1*m9  + a2*m10 + a3*m11;
	res[12] = a0*m12 + a1*m13 + a2*m14 + a3*m15;

	a0 = cur[1];
	a1 = cur[5];
	a2 = cur[9];
	a3 = cur[13];
	res[1]  = a0*m0  + a1*m1  + a2*m2  + a3*m3;
	res[5]  = a0*m4  + a1*m5  + a2*m6  + a3*m7;
	res[9]  = a0*m8  + a1*m9  + a2*m10 + a3*m11;
	res[13] = a0*m12 + a1*m13 + a2*m14 + a3*m15;

	a0 = cur[2];
	a1 = cur[6];
	a2 = cur[10];
	a3 = cur[14];
	res[2]  = a0*m0  + a1*m1  + a2*m2  + a3*m3;
	res[6]  = a0*m4  + a1*m5  + a2*m6  + a3*m7;
	res[10] = a0*m8  + a1*m9  + a2*m10 + a3*m11;
	res[14] = a0*m12 + a1*m13 + a2*m14 + a3*m15;

	a0 = cur[3];
	a1 = cur[7];
	a2 = cur[11];
	a3 = cur[15];
	res[3]  = a0*m0  + a1*m1  + a2*m2  + a3*m3;
	res[7]  = a0*m4  + a1*m5  + a2*m6  + a3*m7;
	res[11] = a0*m8  + a1*m9  + a2*m10 + a3*m11;
	res[15] = a0*m12 + a1*m13 + a2*m14 + a3*m15;

	glLoadMatrixf(res);
}

//------------------------------------------------------------------------
void glPushMatrix(void)
{
GLfloat *src, *dst;

//	CHECK_BEGIN_END(); used in renderer

	switch(g_ctx->glMatrixMode)
	{
	case GL_MODELVIEW:
		if(g_ctx->curModelViewMatrix == GL_MAX_MODELVIEW_STACK_DEPTH-1)
		{
			SET_GL_ERROR(GL_STACK_OVERFLOW);
			return;
		}
		src = (&(g_ctx->matModelView[g_ctx->curModelViewMatrix][0]));
		dst = src+16;
		memcpy(dst, src, sizeof(GLfloat)*16);
		g_ctx->curModelViewMatrix++;
		break;

	case GL_PROJECTION:
		if(g_ctx->curProjectionMatrix == GL_MAX_PROJECTION_STACK_DEPTH-1)
		{
			SET_GL_ERROR(GL_STACK_OVERFLOW);
			return;
		}
		src = (&(g_ctx->matProjection[g_ctx->curProjectionMatrix][0]));
		dst = src+16;
		memcpy(dst, src, sizeof(GLfloat)*16);
		g_ctx->curProjectionMatrix++;
		break;

	case GL_TEXTURE:
		if(g_ctx->curTextureMatrix == GL_MAX_TEXTURE_STACK_DEPTH-1)
		{
			SET_GL_ERROR(GL_STACK_OVERFLOW);
			return;
		}
		src = (&(g_ctx->matTexture[g_ctx->curTextureMatrix][0]));
		dst = src+16;
		memcpy(dst, src, sizeof(GLfloat)*16);
		g_ctx->curTextureMatrix++;
		break;
	}
}

//------------------------------------------------------------------------
void glPopMatrix(void)
{
//	CHECK_BEGIN_END(); used in renderer

	switch(g_ctx->glMatrixMode)
	{
	case GL_MODELVIEW:
		if(g_ctx->curModelViewMatrix == 0)
		{
			SET_GL_ERROR(GL_STACK_UNDERFLOW);
			return;
		}
		g_ctx->curModelViewMatrix--;
		break;

	case GL_PROJECTION:
		if(g_ctx->curProjectionMatrix == 0)
		{
			SET_GL_ERROR(GL_STACK_UNDERFLOW);
			return;
		}
		g_ctx->curProjectionMatrix--;
		break;

	case GL_TEXTURE:
		if(g_ctx->curTextureMatrix == 0)
		{
			SET_GL_ERROR(GL_STACK_UNDERFLOW);
			return;
		}
		g_ctx->curTextureMatrix--;
		break;
	}
}

//------------------------------------------------------------------------
void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
GLfloat		r[16];
GLfloat		nx, ny, nz, d;
//GLdouble	rad, c, s, c1, xs, ys, zs;
GLfloat		rad, c, s, c1, xs, ys, zs;

	CHECK_BEGIN_END();

	// normalize vector (x, y, z)
	d = sqrt(x*x+y*y+z*z);
	nx = x/d;
	ny = y/d;
	nz = z/d;

	rad = angle / 57.2957795786f;
	c = cos(rad);
	s = sin(rad);
	c1 = 1.0f - c;
	xs = x*s;
	ys = y*s;
	zs = z*s;

	memset(r, 0, sizeof(GLfloat)*16);
	r[0]  = (GLfloat)(nx*nx*c1+c);
	r[1]  = (GLfloat)(ny*nx*c1+zs);
	r[2]  = (GLfloat)(nx*nz*c1-ys);
	r[4]  = (GLfloat)(nx*ny*c1-zs);
	r[5]  = (GLfloat)(ny*ny*c1+c);
	r[6]  = (GLfloat)(ny*nz*c1+xs);
	r[8]  = (GLfloat)(nx*nz*c1+ys);
	r[9]  = (GLfloat)(ny*nz*c1-xs);
	r[10] = (GLfloat)(nz*nz*c1+c);
	r[15] = 1.0f;

	glMultMatrixf(r);
}

//------------------------------------------------------------------------
void glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
	glRotatef((GLfloat)angle, (GLfloat)x, (GLfloat)y, (GLfloat)z);
}

//------------------------------------------------------------------------
void glScalef(GLfloat x, GLfloat y, GLfloat z)
{
GLfloat	s[16];

	CHECK_BEGIN_END();

	memset(s, 0, sizeof(GLfloat)*16);
	s[0]  = x;
	s[5]  = y;
	s[10] = z;
	s[15] = 1.0f;
	glMultMatrixf(s);
}

//------------------------------------------------------------------------
void glScaled(GLdouble x, GLdouble y, GLdouble z)
{
	glScalef((GLfloat)x, (GLfloat)y, (GLfloat)z);
}

//------------------------------------------------------------------------
void glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
GLfloat	t[16];

	CHECK_BEGIN_END();

	memset(t, 0, sizeof(GLfloat)*16);
	t[0]  = 1.0f;
	t[5]  = 1.0f;
	t[10] = 1.0f;
	t[15] = 1.0f;
	t[12] = x;
	t[13] = y;
	t[14] = z;
	glMultMatrixf(t);
}

//------------------------------------------------------------------------
void glTranslated(GLdouble x, GLdouble y, GLdouble z)
{
	glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);
}

//------------------------------------------------------------------------
void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
GLfloat m[16];

	CHECK_BEGIN_END();

	memset(m, 0, sizeof(GLfloat)*16);
	m[0]  = (GLfloat)( 2.0f/(right-left));
	m[5]  = (GLfloat)( 2.0f/(top-bottom));
	m[10] = (GLfloat)(-2.0f/(zFar-zNear));
	m[12] = (GLfloat)(-(right+left)/(right-left));
	m[13] = (GLfloat)(-(top+bottom)/(top-bottom));
	m[14] = (GLfloat)(-(zFar+zNear)/(zFar-zNear));
	m[15] = 1.0f;
	glMultMatrixf(m);
}

//------------------------------------------------------------------------
void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
GLdouble	zNear2;
GLfloat		m[16];

	CHECK_BEGIN_END();
	if(zNear < 0.0 || zFar < 0.0) { SET_GL_ERROR(GL_INVALID_VALUE); return; }

	memset(m, 0, sizeof(GLfloat)*16);
	zNear2 = 2.0*zNear;
	m[0]  = (GLfloat)(zNear2/(right-left));
	m[5]  = (GLfloat)(zNear2/(top-bottom));
	m[8]  = (GLfloat)((right+left)/(right-left));
	m[9]  = (GLfloat)((top+bottom)/(top-bottom));
	m[10] = (GLfloat)(-((zFar+zNear)/(zFar-zNear)));
	m[11] = -1.0f;
	m[14] = (GLfloat)(-((zFar*zNear2)/(zFar-zNear)));
	glMultMatrixf(m);
}

