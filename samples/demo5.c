//------------------------------------------------------------------------
// File:   demo5.c
// Author: Tony Saveski, tony@ui.com.au
// Note:   Algorithm & Bitmap by Jan Horn, http://www.sulaco.co.za
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
#include <math.h>

extern void swap_buffers(void);

extern unsigned int tunnel[];
extern unsigned int tunnel_w;
extern unsigned int tunnel_h;

//------------------------------------------------------------------------
#define MY_PI 	3.14159265f
#define MAX_I	32
#define MAX_J	18

typedef struct
{
	GLfloat x, y, z;
} coord_t;

typedef struct
{
	GLfloat u, v;
} texcoord_t;

coord_t		vert[MAX_I+1][MAX_J+1];
texcoord_t	texcoord[MAX_I+1][MAX_J+1];
GLfloat		angle;
GLuint		tname;

//------------------------------------------------------------------------
void create_tunnel(void)
{
int	i, j;

	for(i=0; i<=MAX_I; i++)
	{
		for(j=0; j<=MAX_J; j++)
		{
			vert[i][j].x = (3.0f - j/12.0f)*(float)cos(2.0f*MY_PI/32.0f*i);
			vert[i][j].y = (3.0f - j/12.0f)*(float)sin(2.0f*MY_PI/32.0f*i);
			vert[i][j].z = (float)-j;
		}
	}
	for(i=0; i<=MAX_I; i++)
	{
		for(j=0; j<=MAX_J; j++)
		{
			texcoord[i][j].u = i/32.0f + (float)cos((angle + 8.0f*j)/60.0f)/2.0f;
			texcoord[i][j].v = j/32.0f + (angle + j)/120.0f;
		}
	}
}

//------------------------------------------------------------------------
void demo_init(void)
{
    create_tunnel();
    angle = 0.0f;

	glShadeModel(GL_FLAT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_TEXTURE_2D);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); not implemented yet

	glGenTextures(1, &tname);
	glBindTexture(GL_TEXTURE_2D, tname);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, tunnel_w, tunnel_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tunnel);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f);
}

//------------------------------------------------------------------------
void demo_end(void)
{
}

//------------------------------------------------------------------------
void demo_tick(void)
{
int i, j;
GLfloat c;

	angle += 1.0f;

	for(i=0; i<=MAX_I; i++)
	{
		for(j=0; j<=MAX_J; j++)
		{
			texcoord[i][j].u = i/32.0f + (float)cos((angle + 8.0f*j)/60.0f)/2.0f;
			texcoord[i][j].v = j/32.0f + (angle + j)/120.0f;
		}
	}

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);
	glBindTexture(GL_TEXTURE_2D, tname);

	glBegin(GL_TRIANGLES);
	for(j=0; j<MAX_J; j++)
	{
		if(j>(MAX_J>>1)) c = (GLfloat)(MAX_J-j)/(GLfloat)(MAX_J>>1);
		else c = 1.0f;

		glColor3f(c, c, c);

		for(i=0; i<MAX_I; i++)
		{
			glTexCoord2f(texcoord[i][j].u, texcoord[i][j].v);
			glVertex3f(vert[i][j].x, vert[i][j].y, vert[i][j].z);

			glTexCoord2f(texcoord[i+1][j].u, texcoord[i+1][j].v);
			glVertex3f(vert[i+1][j].x, vert[i+1][j].y, vert[i+1][j].z);

			glTexCoord2f(texcoord[i+1][j+1].u, texcoord[i+1][j+1].v);
			glVertex3f(vert[i+1][j+1].x, vert[i+1][j+1].y, vert[i+1][j+1].z);

			glTexCoord2f(texcoord[i][j].u, texcoord[i][j].v);
			glVertex3f(vert[i][j].x, vert[i][j].y, vert[i][j].z);

			glTexCoord2f(texcoord[i+1][j+1].u, texcoord[i+1][j+1].v);
			glVertex3f(vert[i+1][j+1].x, vert[i+1][j+1].y, vert[i+1][j+1].z);

			glTexCoord2f(texcoord[i][j+1].u, texcoord[i][j+1].v);
			glVertex3f(vert[i][j+1].x, vert[i][j+1].y, vert[i][j+1].z);
		}
	}
	glEnd();
	glFlush();
	swap_buffers();
}
