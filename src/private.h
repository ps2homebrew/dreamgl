//------------------------------------------------------------------------
// File:   private.h
// Author: Tony Saveski, tony@ui.com.au
//------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
//------------------------------------------------------------------------
#ifndef PRIVATE_H
#define PRIVATE_H

#include "defines.h"

//------------------------------------------------------------------------
extern GLfloat dglMaxByte;
extern GLfloat dglMaxUbyte;
extern GLfloat dglMaxShort;
extern GLfloat dglMaxUshort;
extern GLfloat dglMaxInt;
extern GLfloat dglMaxUint;

extern DGLcontext *g_ctx;

//------------------------------------------------------------------------
#define SET_GL_ERROR(e) \
	if(g_ctx->glError == GL_NO_ERROR) g_ctx->glError = (e)

#define CHECK_BEGIN_END() \
	if(g_ctx->InsideBeginEnd == GL_TRUE) { SET_GL_ERROR(GL_INVALID_OPERATION); return; }

#define CLAMP_0(n) \
	if((n) < 0.0f) (n) = 0.0f

#define CLAMP_1(n) \
	if((n) > 1.0f) (n) = 1.0f


//------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

extern int  impDglInit(void);
extern void impDglEnd(void);
extern void impSetActiveBuffer(int buf);
extern void impSetVisibleBuffer(int buf);
extern void impWaitVSync(void);
extern void impClearScreen(GLclampf r, GLclampf g, GLclampf b);
extern void impClearZBuffer(void);
extern void impClearScreenAndZBuffer(GLclampf r, GLclampf g, GLclampf b);
extern void impLoadTexture(uint16 x, uint16 y, uint16 w, uint16 h, uint32 data_adr, uint32 dest_adr);
extern void impSetShadeMode(void);
extern void impSetDepthTest(void);
extern void impSetDepthFunc(void);
extern void impSetTexture2d(void);
extern void impSetTextureEnvMode(void);
extern void impSetTextureMinMag(void);
extern void impSetTextureWrap(void);

#ifdef __cplusplus
}
#endif

#endif // PRIVATE_H
