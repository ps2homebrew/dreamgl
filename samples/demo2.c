//------------------------------------------------------------------------
// File:   demo2.c
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
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

extern void swap_buffers(void);


GLfloat cube_v[][3] = {
	 { -1.0f,  1.0f,  1.0f }
	,{  1.0f,  1.0f,  1.0f }
	,{  1.0f, -1.0f,  1.0f }
	,{ -1.0f, -1.0f,  1.0f }
	,{ -1.0f,  1.0f, -1.0f }
	,{  1.0f,  1.0f, -1.0f }
	,{  1.0f, -1.0f, -1.0f }
	,{ -1.0f, -1.0f, -1.0f }
};

//------------------------------------------------------------------------
void demo_init(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 11.0f);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------
void demo_end(void)
{
}

//------------------------------------------------------------------------
void demo_tick(void)
{
static GLfloat rot = 0.0f;

	rot += 2.0f;
	if(rot >= 360.0f) rot = 0.0f;

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotatef(rot, 1.0f, 0.5f, 0.5f);

	glBegin(GL_TRIANGLES);

		// front face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(cube_v[2]);
		glVertex3fv(cube_v[1]);
		glVertex3fv(cube_v[0]);

		glVertex3fv(cube_v[2]);
		glVertex3fv(cube_v[0]);
		glVertex3fv(cube_v[3]);

		// back face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3fv(cube_v[6]);
		glVertex3fv(cube_v[5]);
		glVertex3fv(cube_v[4]);

		glVertex3fv(cube_v[6]);
		glVertex3fv(cube_v[4]);
		glVertex3fv(cube_v[7]);

		// left face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(cube_v[7]);
		glVertex3fv(cube_v[3]);
		glVertex3fv(cube_v[0]);

		glVertex3fv(cube_v[7]);
		glVertex3fv(cube_v[0]);
		glVertex3fv(cube_v[4]);

		// right face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3fv(cube_v[2]);
		glVertex3fv(cube_v[6]);
		glVertex3fv(cube_v[5]);

		glVertex3fv(cube_v[2]);
		glVertex3fv(cube_v[5]);
		glVertex3fv(cube_v[1]);

		// top face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3fv(cube_v[1]);
		glVertex3fv(cube_v[5]);
		glVertex3fv(cube_v[4]);

		glVertex3fv(cube_v[1]);
		glVertex3fv(cube_v[4]);
		glVertex3fv(cube_v[0]);

		// bottom face
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3fv(cube_v[6]);
		glVertex3fv(cube_v[2]);
		glVertex3fv(cube_v[3]);

		glVertex3fv(cube_v[6]);
		glVertex3fv(cube_v[3]);
		glVertex3fv(cube_v[7]);

	glEnd();

	glFlush();
	swap_buffers();
}
