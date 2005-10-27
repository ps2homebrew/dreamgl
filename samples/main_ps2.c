//------------------------------------------------------------------------
// File:   main_ps2.c
// Author: Tony Saveski, tony@ui.com.au
//------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
//------------------------------------------------------------------------
#include <GL/gl.h>
#include <GL/dgl.h>

DGLcontext	ctx;

extern void demo_init(void);
extern void demo_tick(void);
extern void demo_end(void);

//------------------------------------------------------------------------
void swap_buffers(void)
{
	dglSwapBuffers();
}

//------------------------------------------------------------------------
int init(void)
{
	SifInitRpc(0);

	memset(&ctx, 0, sizeof(DGLcontext));

	ctx.ScreenWidth		= 512;
	ctx.ScreenHeight	= 256;
	ctx.ScreenDepth		= 32;
	ctx.ScreenBuffers	= 2;
	ctx.ZDepth			= 32;
	ctx.VSync			= GL_TRUE;

	if(*((char *)0x1FC80000 - 0xAE) == 'E')
		ctx.ps2VidType	= PS2_PAL;
	else
		ctx.ps2VidType	= PS2_NTSC;

	ctx.ps2VidInterlace	= PS2_NONINTERLACED;
	ctx.ps2VidFrame		= PS2_FRAME;

	return(dglInit(&ctx));
}

//------------------------------------------------------------------------
int end(void)
{
	return(DGL_SUCCESS);
}

//------------------------------------------------------------------------
int main(void)
{
	init();

	demo_init();
	while(1) { demo_tick(); }
	demo_end();

	end();
	return(0);
}
