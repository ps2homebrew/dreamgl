//------------------------------------------------------------------------
// File:   gl_texcoord.c
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
