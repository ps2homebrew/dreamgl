//------------------------------------------------------------------------
// File:   ps2_dgl.c
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

//------------------------------------------------------------------------
GLfloat dglMaxByte		= 127.0f;
GLfloat dglMaxUbyte		= 255.0f;
GLfloat dglMaxShort		= 32767.0f;
GLfloat dglMaxUshort	= 65535.0f;
GLfloat dglMaxInt		= 2147483647.0f;
GLfloat dglMaxUint		= 4294967295.0f;

DECLARE_GS_PACKET(gs_immdma_buf, PS2_IMMDMA_ITEMS);	// "immediate" DMA buffer...might get rid of it at some stage
DECLARE_GS_PACKET(gs_dma_buf, PS2_DMA_ITEMS);		// "geometry" DMA buffer

void ps2_TEST(void);
void ps2_TEX0(void);
void ps2_TEX1(void);
void ps2_CLAMP(void);

//------------------------------------------------------------------------
int impDglInit(void)
{
int i;
uint16 magh;
uint16 pf;	// pixel format

	g_ctx->ps2TextureMapping	= 0;
	g_ctx->ps2ShadeMode			= SHADE_GOURAUD;
	g_ctx->ps2ZTest				= 0;
	g_ctx->ps2ZTestMode			= ZTST_GREATER;
	g_ctx->ps2TextureFunction	= TEX_MODULATE;
	g_ctx->ps2MinFilter			= FILTER_LINEAR;
	g_ctx->ps2MagFilter			= FILTER_LINEAR;
	g_ctx->ps2WrapS				= WRAP_REPEAT;
	g_ctx->ps2WrapT				= WRAP_REPEAT;


	if(g_ctx->ScreenDepth==32)		pf = 0;
	else if(g_ctx->ScreenDepth==24) pf = 1;
	else if(g_ctx->ScreenDepth==16) pf = 2;
	else return(DGL_ERROR);


	if(g_ctx->ZDepth==32)
	{
		g_ctx->ps2Zpsm = 0;
		g_ctx->ps2ZMax = 0xFFFFFFFF;
	}
	else if(g_ctx->ZDepth==24)
	{
		g_ctx->ps2Zpsm = 1;
		g_ctx->ps2ZMax = 0xFFFFFF;
	}
	else if(g_ctx->ZDepth==16)
	{
		g_ctx->ps2Zpsm = 2;
		g_ctx->ps2ZMax = 0xFFFF;
	}
	else return(DGL_ERROR);


	if(g_ctx->ScreenBuffers>2 || g_ctx->ScreenBuffers<1) return(DGL_ERROR);

	g_ctx->ps2OriginX		= 1024;
	g_ctx->ps2OriginY		= 1024;

	g_ctx->ps2GSMemCurrent	= 0;		// nothing allocated yet

	dma_reset();
	GS_RESET();
	__asm__("
		sync.p
		nop
	");

	gs_set_imr();
	gs_set_crtc(g_ctx->ps2VidInterlace, g_ctx->ps2VidType, g_ctx->ps2VidFrame);

	GS_SET_PMODE(
		0,		// ReadCircuit1 OFF
		1,		// ReadCircuit2 ON
		1,		// Use ALP register for Alpha Blending
		1,		// Alpha Value of ReadCircuit2 for output selection
		0,		// Blend Alpha with the output of ReadCircuit2
		0xFF	// Alpha Value = 1.0
	);

	GS_SET_DISPFB2(
		0,						// Frame Buffer base pointer = 0 (Address/8192)
		g_ctx->ScreenWidth/64,	// Buffer Width (Pixels/64)
		pf,						// Pixel Storage Format
		0,						// Upper Left X in Buffer = 0
		0						// Upper Left Y in Buffer = 0
	);

	// Why doesn't (0, 0) equal the very top-left of the TV?
	magh = 2560/g_ctx->ScreenWidth;
	GS_SET_DISPLAY2(
		656,	// X position in the display area (in VCK units)
		36,		// Y position in the display area (in Raster units)
		magh-1,	// Horizontal Magnification - 1
		0,							// Vertical Magnification = 1x
		g_ctx->ScreenWidth*magh-1,	// Display area width  - 1 (in VCK units) (Width*HMag-1)
		g_ctx->ScreenHeight-1		// Display area height - 1 (in pixels)	  (Height-1)
	);

	GS_SET_BGCOLOR(
		0,	// RED
		0,	// GREEN
		0	// BLUE
	);

	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);

	// Use drawing parameters from PRMODE register
	GIF_DATA_AD(gs_immdma_buf, prmodecont, 0);

	// Setup frame buffers. Point to 0 initially.
	GIF_DATA_AD(gs_immdma_buf, frame_1,
		GS_FRAME(
			0,						// FrameBuffer base pointer = 0 (Address/8192)
			g_ctx->ScreenWidth/64,	// Frame buffer width (Pixels/64)
			pf,						// Pixel Storage Format
			0));

	// Save address and advance GS memory pointer by buffer size (in bytes)
	// Do this for both frame buffers.
	for(i=0; i<g_ctx->ScreenBuffers; i++)
	{
		g_ctx->ps2FrameAddr[i] = g_ctx->ps2GSMemCurrent;
		g_ctx->ps2GSMemCurrent += g_ctx->ScreenWidth*g_ctx->ScreenHeight*(g_ctx->ScreenDepth/8);
	}

	// Displacement between Primitive and Window coordinate systems.
	GIF_DATA_AD(gs_immdma_buf, xyoffset_1,
		GS_XYOFFSET(
			g_ctx->ps2OriginX<<4,
			g_ctx->ps2OriginY<<4));

	// Clip to frame buffer.
	GIF_DATA_AD(gs_immdma_buf, scissor_1,
		GS_SCISSOR(
			0, g_ctx->ScreenWidth-1,
			0, g_ctx->ScreenHeight-1));

	// Save z-buffer address and set it up
	g_ctx->ps2ZbufAddr = g_ctx->ps2GSMemCurrent;
	g_ctx->ps2GSMemCurrent += g_ctx->ScreenWidth*g_ctx->ScreenHeight*(g_ctx->ZDepth/8);

	GIF_DATA_AD(gs_immdma_buf, zbuf_1,
		GS_ZBUF(
			g_ctx->ps2ZbufAddr/8192,		// Z Buffer base pointer = Address/8192
			g_ctx->ps2Zpsm, ZMSK_ENABLE));	// Pixel Storage Format, Z Always Enabled

	GIF_DATA_AD(gs_immdma_buf, test_1,
		GS_TEST(
			0, 0, 0, 0, 0, 0,
			g_ctx->ps2ZTest, g_ctx->ps2ZTestMode));

	// No dithering
	GIF_DATA_AD(gs_immdma_buf, dthe, 0);

	// Clamp colors to [0,255]
	GIF_DATA_AD(gs_immdma_buf, colclamp, 1);

	// Save the current address as the start of 'texture memory'
	// NOTE: remember to check if it's properly aligned
	g_ctx->ps2TexbufAddr = g_ctx->ps2GSMemCurrent;

	SEND_GS_PACKET(gs_immdma_buf);

	impSetActiveBuffer(0);
	impClearScreen(0.0f, 0.0f, 0.0f);

	impSetActiveBuffer(1);
	impClearScreen(0.0f, 0.0f, 0.0f);

	impClearZBuffer();

	// Initialize the geometry DMA buffer
	BEGIN_GS_PACKET(gs_dma_buf);
	GIF_TAG_AD(gs_dma_buf, 1, 0, 0, 0);

	return(DGL_SUCCESS);
}

//------------------------------------------------------------------------
void impDglEnd(void)
{
}

//------------------------------------------------------------------------
void impSetActiveBuffer(int buf)
{
uint16 pf;

	if(g_ctx->ScreenDepth==32) 		pf = 0;
	else if(g_ctx->ScreenDepth==24) pf = 1;
	else if(g_ctx->ScreenDepth==16) pf = 2;
	else return;

	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);

	GIF_DATA_AD(gs_immdma_buf, frame_1,
		GS_FRAME(
			g_ctx->ps2FrameAddr[buf]/8192,	// Frame Buffer base pointer = Address/8192
			g_ctx->ScreenWidth/64,			// Buffer Width (Pixels/64)
			pf,								// Pixel Storage Format
			0));

	SEND_GS_PACKET(gs_immdma_buf);
}

//------------------------------------------------------------------------
void impSetVisibleBuffer(int buf)
{
uint16 pf;

	// yeh, i know i could do (4-bpp/8), but i don't wanna.
	if(g_ctx->ScreenDepth==32) 		pf = 0;
	else if(g_ctx->ScreenDepth==24) pf = 1;
	else if(g_ctx->ScreenDepth==16) pf = 2;
	else return;

	GS_SET_DISPFB2(
		g_ctx->ps2FrameAddr[buf]/8192,	// Frame Buffer base pointer = Address/8192
		g_ctx->ScreenWidth/64,			// Buffer Width (Pixels/64)
		pf,								// Pixel Storage Format
		0,								// Upper Left X in Buffer = 0
		0								// Upper Left Y in Buffer = 0
	);
}

//------------------------------------------------------------------------
void impWaitVSync(void)
{
	*CSR = *CSR & 8;
	while(!(*CSR & 8));
}

//------------------------------------------------------------------------
void impClearScreen(GLclampf r, GLclampf g, GLclampf b)
{
int 	x0, y0, x1, y1;
uint8	r8, g8, b8;

	x0 = g_ctx->ps2OriginX;
	y0 = g_ctx->ps2OriginY;
	x1 = g_ctx->ps2OriginX + g_ctx->ScreenWidth - 1;
	y1 = g_ctx->ps2OriginY + g_ctx->ScreenHeight - 1;

	r8 = (uint8)(r*255.0f+0.5f);
	g8 = (uint8)(g*255.0f+0.5f);
	b8 = (uint8)(b*255.0f+0.5f);

	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);

	// Flat Shading, No Texture Mapping
	GIF_DATA_AD(gs_immdma_buf, prmode,
		GS_PRMODE(0, 0, 0, 0, 0, 0, 0, 0));

	// Update only frame buffer
	GIF_DATA_AD(gs_immdma_buf, test_1,
		GS_TEST(1, 0, 0x80, 1, 0, 0, 0, ZTST_ALWAYS));

	// Draw a sprite filling the whole screen
	GIF_DATA_AD(gs_immdma_buf, prim,	GS_PRIM(PRIM_SPRITE, 0, 0, 0, 0, 0, 0, 0, 0));
	GIF_DATA_AD(gs_immdma_buf, rgbaq, GS_RGBAQ(r8, g8, b8, 0x80, 0));
	GIF_DATA_AD(gs_immdma_buf, xyz2,  GS_XYZ2(x0<<4, y0<<4, 0));
	GIF_DATA_AD(gs_immdma_buf, xyz2,  GS_XYZ2((x1+1)<<4, (y1+1)<<4, 0));

	// Restore Z-Buffer Mode
	GIF_DATA_AD(gs_immdma_buf, test_1,
		GS_TEST(0, 0, 0, 0, 0, 0, g_ctx->ps2ZTest, g_ctx->ps2ZTestMode));

	// Restore Shading and Texturing Modes
	GIF_DATA_AD(gs_immdma_buf, prmode,
		GS_PRMODE(g_ctx->ps2ShadeMode, g_ctx->ps2TextureMapping, 0, 0, 0, 0, 0, 0));

	SEND_GS_PACKET(gs_immdma_buf);
}

//------------------------------------------------------------------------
void impClearZBuffer(void)
{
int x0, y0, x1, y1;

	x0 = g_ctx->ps2OriginX;
	y0 = g_ctx->ps2OriginY;
	x1 = g_ctx->ps2OriginX + g_ctx->ScreenWidth - 1;
	y1 = g_ctx->ps2OriginY + g_ctx->ScreenHeight - 1;

	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);

	// Flat Shading, No Texture Mapping
	GIF_DATA_AD(gs_immdma_buf, prmode,
		GS_PRMODE(0, 0, 0, 0, 0, 0, 0, 0));

	// Update only Z buffer
	GIF_DATA_AD(gs_immdma_buf, test_1,
		GS_TEST(1, 0, 0x80, 2, 0, 0, 1, ZTST_ALWAYS));

	// Draw a sprite filling the whole screen
	GIF_DATA_AD(gs_immdma_buf, prim,	GS_PRIM(PRIM_SPRITE, 0, 0, 0, 0, 0, 0, 0, 0));
	GIF_DATA_AD(gs_immdma_buf, rgbaq, GS_RGBAQ(0, 0, 0, 0x80, 0));
	GIF_DATA_AD(gs_immdma_buf, xyz2,  GS_XYZ2(x0<<4, y0<<4, 0));
	GIF_DATA_AD(gs_immdma_buf, xyz2,  GS_XYZ2((x1+1)<<4, (y1+1)<<4, 0));

	// Restore Z-Buffer Mode
	GIF_DATA_AD(gs_immdma_buf, test_1,
		GS_TEST(0, 0, 0, 0, 0, 0, g_ctx->ps2ZTest, g_ctx->ps2ZTestMode));

	// Restore Shading and Texturing Modes
	GIF_DATA_AD(gs_immdma_buf, prmode,
		GS_PRMODE(g_ctx->ps2ShadeMode, g_ctx->ps2TextureMapping, 0, 0, 0, 0, 0, 0));

	SEND_GS_PACKET(gs_immdma_buf);
}

//------------------------------------------------------------------------
void impClearScreenAndZBuffer(GLclampf r, GLclampf g, GLclampf b)
{
int 	x0, y0, x1, y1;
uint8	r8, g8, b8;

	x0 = g_ctx->ps2OriginX;
	y0 = g_ctx->ps2OriginY;
	x1 = g_ctx->ps2OriginX + g_ctx->ScreenWidth - 1;
	y1 = g_ctx->ps2OriginY + g_ctx->ScreenHeight - 1;

	r8 = (uint8)(r*255.0f+0.5f);
	g8 = (uint8)(g*255.0f+0.5f);
	b8 = (uint8)(b*255.0f+0.5f);

	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);

	// Flat Shading, No Texture Mapping
	GIF_DATA_AD(gs_immdma_buf, prmode,
		GS_PRMODE(0, 0, 0, 0, 0, 0, 0, 0));

	// Update both frame and Z buffers
	GIF_DATA_AD(gs_immdma_buf, test_1,
		GS_TEST(0, 0, 0, 0, 0, 0, 1, ZTST_ALWAYS));

	// Draw a sprite filling the whole screen
	GIF_DATA_AD(gs_immdma_buf, prim,	GS_PRIM(PRIM_SPRITE, 0, 0, 0, 0, 0, 0, 0, 0));
	GIF_DATA_AD(gs_immdma_buf, rgbaq, GS_RGBAQ(r8, g8, b8, 0x80, 0));
	GIF_DATA_AD(gs_immdma_buf, xyz2,  GS_XYZ2(x0<<4, y0<<4, 0));
	GIF_DATA_AD(gs_immdma_buf, xyz2,  GS_XYZ2((x1+1)<<4, (y1+1)<<4, 0));

	// Restore Z-Buffer Mode
	GIF_DATA_AD(gs_immdma_buf, test_1,
		GS_TEST(0, 0, 0, 0, 0, 0, g_ctx->ps2ZTest, g_ctx->ps2ZTestMode));

	// Restore Shading and Texturing Modes
	GIF_DATA_AD(gs_immdma_buf, prmode,
		GS_PRMODE(g_ctx->ps2ShadeMode, g_ctx->ps2TextureMapping, 0, 0, 0, 0, 0, 0));

	SEND_GS_PACKET(gs_immdma_buf);
}

//------------------------------------------------------------------------
void impSetShadeMode(void)
{
	if(g_ctx->glShadeModel == GL_FLAT) g_ctx->ps2ShadeMode = SHADE_FLAT;
	else g_ctx->ps2ShadeMode = SHADE_GOURAUD;

	GIF_DATA_AD(gs_dma_buf, prmode,
		GS_PRMODE(g_ctx->ps2ShadeMode, g_ctx->ps2TextureMapping, 0, 0, 0, 0, 0, 0));
}

//------------------------------------------------------------------------
void impSetDepthTest(void)
{
	if(g_ctx->glDepthTest==GL_TRUE && g_ctx->glDepthWriteMask==GL_TRUE) g_ctx->ps2ZTest = 1;
	else g_ctx->ps2ZTest = 0;

	ps2_TEST();
}

//------------------------------------------------------------------------
void impSetDepthFunc(void)
{
	switch(g_ctx->glDepthFunc)
	{
		case GL_NEVER:	g_ctx->ps2ZTestMode = ZTST_NEVER;	break;
		case GL_LESS:	g_ctx->ps2ZTestMode = ZTST_GREATER;	break;
		case GL_LEQUAL:	g_ctx->ps2ZTestMode = ZTST_GEQUAL;	break;
		case GL_ALWAYS:	g_ctx->ps2ZTestMode = ZTST_ALWAYS;	break;
		default:		g_ctx->ps2ZTestMode = ZTST_GREATER;	break;
	}
	ps2_TEST();
}

//------------------------------------------------------------------------
void impSetTexture2d(void)
{
	if(g_ctx->glTexture2d == GL_TRUE) g_ctx->ps2TextureMapping = 1;
	else g_ctx->ps2TextureMapping = 0;

	GIF_DATA_AD(gs_dma_buf, prmode,
		GS_PRMODE(g_ctx->ps2ShadeMode, g_ctx->ps2TextureMapping, 0, 0, 0, 0, 0, 0));
}

//------------------------------------------------------------------------
void impSetTextureEnvMode(void)
{
	if(g_ctx->glTextureEnvMode == GL_DECAL) g_ctx->ps2TextureFunction = TEX_DECAL;
	else g_ctx->ps2TextureFunction = TEX_MODULATE;

	ps2_TEX0();
}

//---------------------------------------------------------------------------
void impSetTextureMinMag(void)
{
DGLtexture *tex;

	tex = &(g_ctx->Textures[g_ctx->glTexture2dBinding]);

	if(tex->MinFilter == GL_LINEAR) g_ctx->ps2MinFilter = FILTER_LINEAR;
	else g_ctx->ps2MinFilter = FILTER_NEAREST;

	if(tex->MagFilter == GL_LINEAR) g_ctx->ps2MagFilter = FILTER_LINEAR;
	else g_ctx->ps2MagFilter = FILTER_NEAREST;

	if(tex->Resident==GL_TRUE)
	{
		ps2_TEX1();
	}
}

//---------------------------------------------------------------------------
void impSetTextureWrap(void)
{
DGLtexture *tex;

	tex = &(g_ctx->Textures[g_ctx->glTexture2dBinding]);

	if(tex->WrapS == GL_REPEAT) g_ctx->ps2WrapS = WRAP_REPEAT;
	else g_ctx->ps2WrapS = WRAP_CLAMP;

	if(tex->WrapT == GL_REPEAT) g_ctx->ps2WrapT = WRAP_REPEAT;
	else g_ctx->ps2WrapT = WRAP_CLAMP;

	if(tex->Resident==GL_TRUE)
	{
		ps2_CLAMP();
	}
}

//---------------------------------------------------------------------------
#define MAX_TRANSFER	16384

uint16 texture_wh(uint16 n)
{
uint16 l=0;

	n--;
	while(n>0) n>>=1, l++;
	return(l);
}

void impLoadTexture(uint16 x, uint16 y, uint16 w, uint16 h, uint32 data_adr, uint32 dest_adr)
{
uint32 i;			// DMA buffer loop counter
uint32 frac;		// flag for whether to run a fractional buffer or not
uint32 current;		// number of pixels to transfer in current DMA
uint32 qtotal;		// total number of qwords of data to transfer
uint16 dest_w;		// width of destination texture buffer

	if(g_ctx->glTexture2d == GL_FALSE) return;

	dest_w = DGL_MAX_TEXTURE_SIZE;

	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);
	GIF_DATA_AD(gs_immdma_buf, bitbltbuf,
		GS_BITBLTBUF(0, 0, 0,
			dest_adr/256,		// frame buffer address
			dest_w/64,			// frame buffer width
			0));
	GIF_DATA_AD(gs_immdma_buf, trxpos,
		GS_TRXPOS(0, 0, x, y, 0));	// left to right/top to bottom
	GIF_DATA_AD(gs_immdma_buf, trxreg, GS_TRXREG(w, h));
	GIF_DATA_AD(gs_immdma_buf, trxdir, GS_TRXDIR(XDIR_EE_GS));
	SEND_GS_PACKET(gs_immdma_buf);

	qtotal = w*h/4;					// total number of quadwords to transfer.
	current = qtotal % MAX_TRANSFER;// work out if a partial buffer transfer is needed.
	frac=1;							// assume yes.
	if(!current)					// if there is no need for partial buffer
	{
		current = MAX_TRANSFER;		// start with a full buffer
		frac=0;						// and don't do extra partial buffer first
	}
	for(i=0; i<(qtotal/MAX_TRANSFER)+frac; i++)
	{
		BEGIN_GS_PACKET(gs_immdma_buf);
		GIF_TAG_IMG(gs_immdma_buf, current);
		SEND_GS_PACKET(gs_immdma_buf);

		SET_QWC(GIF_QWC, current);
		SET_MADR(GIF_MADR, data_adr, 0);
		SET_CHCR(GIF_CHCR, 1, 0, 0, 0, 0, 1, 0);
		DMA_WAIT(GIF_CHCR);

		data_adr += current*16;
		current = MAX_TRANSFER;		// after the first one, all are full buffers
	}

	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);

	// Access the TEXFLUSH register with anything to flush the texture
	GIF_DATA_AD(gs_immdma_buf, texflush, 0x42);

	// Select as current texture and set size etc...
	g_ctx->ps2CurTEX0_TBP	= dest_adr/256;
	g_ctx->ps2CurTEX0_TBW	= dest_w/64;
	g_ctx->ps2CurTEX0_PSM	= 0;
	g_ctx->ps2CurTEX0_TW	= texture_wh(w);
	g_ctx->ps2CurTEX0_TH	= texture_wh(h);
	g_ctx->ps2CurTEX0_TCC	= 1;

	GIF_DATA_AD(gs_immdma_buf, tex0_1,
		GS_TEX0(
			g_ctx->ps2CurTEX0_TBP,
			g_ctx->ps2CurTEX0_TBW,
			g_ctx->ps2CurTEX0_PSM,
			g_ctx->ps2CurTEX0_TW,
			g_ctx->ps2CurTEX0_TH,
			g_ctx->ps2CurTEX0_TCC,
			g_ctx->ps2TextureFunction,
			0,0,0,0,0));

	// Set min/mag filter
	GIF_DATA_AD(gs_immdma_buf, tex1_1,
		GS_TEX1(0, 0, g_ctx->ps2MagFilter, g_ctx->ps2MinFilter, 0, 0, 0));

	// Set texture wrap mode
	GIF_DATA_AD(gs_immdma_buf, clamp_1,
		GS_CLAMP(g_ctx->ps2WrapS, g_ctx->ps2WrapT));

	SEND_GS_PACKET(gs_immdma_buf);
}

//------------------------------------------------------------------------
void ps2_TEST(void)
{
	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);

	GIF_DATA_AD(gs_immdma_buf, test_1,
		GS_TEST(0, 0, 0, 0, 0, 0, g_ctx->ps2ZTest, g_ctx->ps2ZTestMode));

	SEND_GS_PACKET(gs_immdma_buf);
}

//------------------------------------------------------------------------
void ps2_TEX0(void)
{
	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);

	GIF_DATA_AD(gs_immdma_buf, tex0_1,
		GS_TEX0(
			g_ctx->ps2CurTEX0_TBP,
			g_ctx->ps2CurTEX0_TBW,
			g_ctx->ps2CurTEX0_PSM,
			g_ctx->ps2CurTEX0_TW,
			g_ctx->ps2CurTEX0_TH,
			g_ctx->ps2CurTEX0_TCC,
			g_ctx->ps2TextureFunction,
			0,0,0,0,0));

	SEND_GS_PACKET(gs_immdma_buf);
}

//------------------------------------------------------------------------
void ps2_TEX1(void)
{
	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);

	GIF_DATA_AD(gs_immdma_buf, tex1_1,
		GS_TEX1(0, 0, g_ctx->ps2MagFilter, g_ctx->ps2MinFilter, 0, 0, 0));

	SEND_GS_PACKET(gs_immdma_buf);
}

//------------------------------------------------------------------------
void ps2_CLAMP(void)
{
	BEGIN_GS_PACKET(gs_immdma_buf);
	GIF_TAG_AD(gs_immdma_buf, 1, 0, 0, 0);

	GIF_DATA_AD(gs_immdma_buf, clamp_1,
		GS_CLAMP(g_ctx->ps2WrapS, g_ctx->ps2WrapT));

	SEND_GS_PACKET(gs_immdma_buf);
}
