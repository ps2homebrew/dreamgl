//------------------------------------------------------------------------
// File:   private.h
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
