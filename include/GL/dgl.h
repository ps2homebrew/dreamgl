//------------------------------------------------------------------------
// File:   dgl.h
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
#ifndef DGL_H
#define DGL_H

#include <GL/gl.h>

//------------------------------------------------------------------------
#define GL_MAX_MODELVIEW_STACK_DEPTH 	32
#define GL_MAX_PROJECTION_STACK_DEPTH 	8
#define GL_MAX_TEXTURE_STACK_DEPTH 		8
#define GL_MAX_TEXTURE_SIZE 			512
#define DGL_MAX_TEXTURE_ARRAY_ITEMS 	1000
#define DGL_MAX_TEXTURE_SIZE 			512
#define DGL_MAX_FRAME_BUFFERS 			2
#define PS2_DMA_ITEMS 					1000
#define PS2_IMMDMA_ITEMS 				20

//------------------------------------------------------------------------
#define DGL_ERROR		0
#define DGL_SUCCESS		1

#define COORD_X			0
#define COORD_Y			1
#define COORD_Z			2
#define COORD_W			3
#define COORD_WIDTH		2
#define COORD_HEIGHT	3

#define COLOR_R			0
#define COLOR_G			1
#define COLOR_B			2
#define COLOR_A			3

#define TEXCOORD_S		0
#define TEXCOORD_T		1
#define TEXCOORD_R		2
#define TEXCOORD_Q		3

#ifdef DGL_PS2
 enum DGLvideotype	{ PS2_NTSC = 2, PS2_PAL };
 enum DGLinterlace	{ PS2_NONINTERLACED = 0, PS2_INTERLACED };
 enum DGLframe		{ PS2_FRAME = 1, PS2_FIELD };
#endif

typedef	union
{
	GLboolean	glBoolean;
	GLbyte		glByte;
	GLbitfield	glBitfield;
	GLclampf	glClampf;
	GLclampd	glClampd;
	GLdouble	glDouble;
	GLenum		glEnum;
	GLfloat		glFloat;
	GLint		glInt;
	GLshort		glShort;
	GLsizei		glSizei;
	GLubyte		glUbyte;
	GLuint		glUint;
	GLushort	glUshort;
	GLfloat		*glFloatPtr;
} DGLvar;

typedef	struct
{
	GLboolean	InUse;
	GLuint		Dim;		// GL_TEXTURE_1D or GL_TEXTURE_2D
	GLuint		MagFilter;
	GLuint		MinFilter;
	GLuint		WrapS;
	GLuint		WrapT;
	GLsizei		Width;
	GLsizei		Height;
//GLint		InternalFormat;
//BorderColor;
//Border;
//RedSize;
//GreenSize;
//BlueSize;
//AlphaSize;
//LuminanceSize;
//IntensitySize;
//Priority;
	GLboolean	Resident;
	GLvoid		*Pixels;
} DGLtexture;

typedef struct
{
	//
	// Required Input Parameters - Common
	//
	GLint		ScreenWidth;	// Screen Width in Pixels
	GLint		ScreenHeight;	// Screen Height in Pixels
	GLint		ScreenDepth;	// Screen Depth or Bits-Per-Pixel
	GLint		ScreenBuffers;	// Number of screen buffers
	GLint		ZDepth;			// Z-Buffer Depth
	GLboolean	VSync;			// Whether to wait for VSync before swapping buffers

	//
	// GL State Variables - Common
	//
	GLclampf	glColorClearValue[4];		// r, g, b, a
	GLclampf	glCurrentColor[4];			// r, g, b, a
	GLfloat		glCurrentTextureCoords[4];	// s, t, r, q
	GLboolean	glDepthTest;
	GLboolean	glDepthWriteMask;
	GLenum		glDepthFunc;
	GLboolean	glDoublebuffer;
	GLenum		glDrawBuffer;
	GLenum		glError;
	GLenum		glMatrixMode;
	GLenum		glShadeModel;
	GLint		glViewport[4];				// x, y, w, h
	GLboolean	glTexture2d;
	GLuint		glTexture2dBinding;
	GLint		glTextureEnvMode;

	//
	// Private Variables - Common
	//
	int			ActiveBuffer;
	int			VisibleBuffer;
	GLboolean	InsideBeginEnd;
	DGLtexture 	Textures[DGL_MAX_TEXTURE_ARRAY_ITEMS];

	int			curModelViewMatrix;
	int			curProjectionMatrix;
	int			curTextureMatrix;
	GLfloat		matModelView[GL_MAX_MODELVIEW_STACK_DEPTH][16];
	GLfloat		matProjection[GL_MAX_PROJECTION_STACK_DEPTH][16];
	GLfloat		matTexture[GL_MAX_TEXTURE_STACK_DEPTH][16];

	//
	// Private Playstation2 Parameters - PS2CPU & PS2VU
	//
#ifdef DGL_PS2
	enum DGLinterlace	ps2VidInterlace;
	enum DGLvideotype	ps2VidType;
	enum DGLframe		ps2VidFrame;

	unsigned char	curColR;			// glCurrentColor as used by PS2
	unsigned char	curColG;
	unsigned char	curColB;
	unsigned char	curColA;

	unsigned int	ps2GSMemCurrent;	// points to current GS memory allocation point
	unsigned int	ps2FrameAddr[DGL_MAX_FRAME_BUFFERS]; // address of both frame buffers in GS memory
	unsigned int	ps2ZbufAddr;		// address of z-buffer in GS memory
	unsigned int	ps2TexbufAddr;		// address of texture buffer in GS memory
	unsigned int	ps2OriginX;			// used for mapping Primitive to Window coordinate systems
	unsigned int	ps2OriginY;
	unsigned int	ps2ZTest;			// ZTest on/off
	unsigned int	ps2ZTestMode;		// ZTest mode
	unsigned long	ps2ZMax;			// maximum Z value (min=0)
	unsigned int	ps2Zpsm;			// Z Pixel Storage Mode
	unsigned int	ps2ShadeMode;		// SHADE_FLAT or SHADE_GOURAUD
	unsigned int	ps2TextureMapping;	// 0=off, 1=on
	unsigned int	ps2TextureFunction;	// TEX_MODULATE or TEX_DECAL
	unsigned int	ps2CurTEX0_TBP;
	unsigned int	ps2CurTEX0_TBW;
	unsigned int	ps2CurTEX0_PSM;
	unsigned int	ps2CurTEX0_TW;
	unsigned int	ps2CurTEX0_TH;
	unsigned int	ps2CurTEX0_TCC;
	unsigned int	ps2MinFilter;
	unsigned int	ps2MagFilter;
	unsigned int	ps2WrapS;
	unsigned int	ps2WrapT;
#endif

} DGLcontext;


#ifdef __cplusplus
extern "C" {
#endif

extern int  dglInit(DGLcontext *cfg);
extern void dglEnd(void);
extern void dglSwapBuffers(void);

#ifdef __cplusplus
}
#endif

#endif // DGL_H
