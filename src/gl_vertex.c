//------------------------------------------------------------------------
// File:   gl_vertex.c
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

#define DEF_Z	(0.0f)
#define DEF_W	(1.0f)

//------------------------------------------------------------------------
// Don't want to optimize anything yet...
//------------------------------------------------------------------------
void glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
GLfloat ex, ey, ez, ew;	// Eye-space vertex coordinates
GLfloat cx, cy, cz, cw;	// Clip-space vertex coordinates
GLfloat dx, dy, dz, dw;	// Normalized Device vertex coordinates
GLfloat ts, tt, tr, tq;	// Perspective Correct texture coordinates
GLint	wx, wy;			// Window x & Y
uint32	wz;				// Window z

GLfloat *mv_mat;		// Current ModelView Matrix
GLfloat *p_mat;			// Current Projection Matrix

GLint *vp;				// viewport[4]

	// Get Current Matrices
	mv_mat = &(g_ctx->matModelView[g_ctx->curModelViewMatrix][0]);
	p_mat  = &(g_ctx->matProjection[g_ctx->curProjectionMatrix][0]);

	// Get Current Viewport
	vp = &(g_ctx->glViewport[0]);

	// Model to Eye
	ex = mv_mat[0]*x + mv_mat[4]*y + mv_mat[8 ]*z + mv_mat[12]*w;
	ey = mv_mat[1]*x + mv_mat[5]*y + mv_mat[9 ]*z + mv_mat[13]*w;
	ez = mv_mat[2]*x + mv_mat[6]*y + mv_mat[10]*z + mv_mat[14]*w;
	ew = mv_mat[3]*x + mv_mat[7]*y + mv_mat[11]*z + mv_mat[15]*w;

	// Eye to Clip
	cx = p_mat[0]*ex + p_mat[4]*ey + p_mat[8 ]*ez + p_mat[12]*ew;
	cy = p_mat[1]*ex + p_mat[5]*ey + p_mat[9 ]*ez + p_mat[13]*ew;
	cz = p_mat[2]*ex + p_mat[6]*ey + p_mat[10]*ez + p_mat[14]*ew;
	cw = p_mat[3]*ex + p_mat[7]*ey + p_mat[11]*ez + p_mat[15]*ew;

	// Clip to Normalized Device
	dx = cx / cw;
	dy = cy / cw;
	dz = cz / cw;
	dw = 1.0f;

	// Normalized Device to Window Coordinates
	wx = (GLint)(((dx + 1.0f) * (vp[COORD_WIDTH]>>1) + vp[COORD_X]) + 0.5f);
	wy = (g_ctx->ScreenHeight) - (GLint)(((dy + 1.0f) * (vp[COORD_HEIGHT]>>1) + vp[COORD_Y]) + 0.5f);
	wz = (uint32)(g_ctx->ps2ZMax - (uint32)(dz * g_ctx->ps2ZMax + 0.5f));

//wy = (GLint)(((dy+1.0f)*(vp[3]>>1)+vp[1])+0.5f);
// TODO: get rid of this crap as soon as clipping is implemented
wx += g_ctx->ps2OriginX;
wy += g_ctx->ps2OriginY;

	// Texture Perspective
	ts = g_ctx->glCurrentTextureCoords[TEXCOORD_S] / cw;
	tt = g_ctx->glCurrentTextureCoords[TEXCOORD_T] / cw;
	tr = g_ctx->glCurrentTextureCoords[TEXCOORD_R] / cw;
	tq = g_ctx->glCurrentTextureCoords[TEXCOORD_Q] / cw;

	// Pack into DMA buffer
	GIF_DATA_AD(gs_dma_buf, st,    GS_ST( *(uint32 *)(&ts), *(uint32 *)(&tt) ));
	GIF_DATA_AD(gs_dma_buf, rgbaq, GS_RGBAQ( g_ctx->curColR, g_ctx->curColG, g_ctx->curColB, g_ctx->curColA, *(uint32 *)(&tq) ))
	GIF_DATA_AD(gs_dma_buf, xyz2,  GS_XYZ2(wx<<4, wy<<4, wz));
}

//------------------------------------------------------------------------
void glVertex4fv(const GLfloat *v)
{
	glVertex4f(v[0], v[1], v[2], v[3]);
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
	glVertex4f(x, y, z, DEF_W);
}

void glVertex3fv(const GLfloat *v)
{
	glVertex4f(v[0], v[1], v[2], DEF_W);
}

void glVertex2f(GLfloat x, GLfloat y)
{
	glVertex4f(x, y, DEF_Z, DEF_W);
}

void glVertex2fv(const GLfloat *v)
{
	glVertex4f(v[0], v[1], DEF_Z, DEF_W);
}

//------------------------------------------------------------------------
void glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	glVertex4f((GLfloat)x, (GLfloat)y, (GLfloat)z, (GLfloat)w);
}

void glVertex4dv(const GLdouble *v)
{
	glVertex4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), (GLfloat)(v[3]));
}

void glVertex3d(GLdouble x, GLdouble y, GLdouble z)
{
	glVertex4f((GLfloat)x, (GLfloat)y, (GLfloat)z, DEF_W);
}

void glVertex3dv(const GLdouble *v)
{
	glVertex4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), DEF_W);
}

void glVertex2d(GLdouble x, GLdouble y)
{
	glVertex4f((GLfloat)x, (GLfloat)y, DEF_Z, DEF_W);
}

void glVertex2dv(const GLdouble *v)
{
	glVertex4f((GLfloat)(v[0]), (GLfloat)(v[1]), DEF_Z, DEF_W);
}

//------------------------------------------------------------------------
void glVertex4i(GLint x, GLint y, GLint z, GLint w)
{
	glVertex4f((GLfloat)x, (GLfloat)y, (GLfloat)z, (GLfloat)w);
}

void glVertex4iv(const GLint *v)
{
	glVertex4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), (GLfloat)(v[3]));
}

void glVertex3i(GLint x, GLint y, GLint z)
{
	glVertex4f((GLfloat)x, (GLfloat)y, (GLfloat)z, DEF_W);
}

void glVertex3iv(const GLint *v)
{
	glVertex4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), DEF_W);
}

void glVertex2i(GLint x, GLint y)
{
	glVertex4f((GLfloat)x, (GLfloat)y, DEF_Z, DEF_W);
}

void glVertex2iv(const GLint *v)
{
	glVertex4f((GLfloat)(v[0]), (GLfloat)(v[1]), DEF_Z, DEF_W);
}

//------------------------------------------------------------------------
void glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w)
{
	glVertex4f((GLfloat)x, (GLfloat)y, (GLfloat)z, (GLfloat)w);
}

void glVertex4sv(const GLshort *v)
{
	glVertex4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), (GLfloat)(v[3]));
}

void glVertex3s(GLshort x, GLshort y, GLshort z)
{
	glVertex4f((GLfloat)x, (GLfloat)y, (GLfloat)z, DEF_W);
}

void glVertex3sv(const GLshort *v)
{
	glVertex4f((GLfloat)(v[0]), (GLfloat)(v[1]), (GLfloat)(v[2]), DEF_W);
}

void glVertex2s(GLshort x, GLshort y)
{
	glVertex4f((GLfloat)x, (GLfloat)y, DEF_Z, DEF_W);
}

void glVertex2sv(const GLshort *v)
{
	glVertex4f((GLfloat)(v[0]), (GLfloat)(v[1]), DEF_Z, DEF_W);
}
