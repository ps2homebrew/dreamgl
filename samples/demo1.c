//------------------------------------------------------------------------
// File:   demo1.c
// Author: Tony Saveski, tony@ui.com.au
//------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
//------------------------------------------------------------------------
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

extern void swap_buffers(void);


GLfloat cube_v[][3] = {
	 { -0.5f,  0.5f, -0.5f }
	,{  0.5f,  0.5f, -0.5f }
	,{  0.5f, -0.5f, -0.5f }
	,{ -0.5f, -0.5f, -0.5f }
	,{ -0.5f,  0.5f,  0.5f }
	,{  0.5f,  0.5f,  0.5f }
	,{  0.5f, -0.5f,  0.5f }
	,{ -0.5f, -0.5f,  0.5f }
};

//------------------------------------------------------------------------
void demo_init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	glOrtho(-2.0f, 2.0f, -1.5f, 1.5f, -2.0f, 2.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(30.0f, 0.5f, 1.0f, 0.0f);
}

//------------------------------------------------------------------------
void demo_end(void)
{
}

//------------------------------------------------------------------------
void demo_tick(void)
{
	glBegin(GL_LINES);

		// front face
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3fv(cube_v[0]);
		glVertex3fv(cube_v[1]);

		glVertex3fv(cube_v[1]);
		glVertex3fv(cube_v[2]);

		glVertex3fv(cube_v[2]);
		glVertex3fv(cube_v[3]);

		glVertex3fv(cube_v[3]);
		glVertex3fv(cube_v[0]);

		// back face
		glVertex3fv(cube_v[4]);
		glVertex3fv(cube_v[5]);

		glVertex3fv(cube_v[5]);
		glVertex3fv(cube_v[6]);

		glVertex3fv(cube_v[6]);
		glVertex3fv(cube_v[7]);

		glVertex3fv(cube_v[7]);
		glVertex3fv(cube_v[4]);

		// joining lines
		glVertex3fv(cube_v[0]);
		glVertex3fv(cube_v[4]);

		glVertex3fv(cube_v[1]);
		glVertex3fv(cube_v[5]);

		glVertex3fv(cube_v[2]);
		glVertex3fv(cube_v[6]);

		glVertex3fv(cube_v[3]);
		glVertex3fv(cube_v[7]);

	glEnd();

	// co-ordinate axes
	glBegin(GL_LINES);
		glColor3f(0.5f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f( 1.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);
		glVertex3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.0f,  0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f,  0.0f, 0.0f);
		glVertex3f(0.0f,  1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 0.5f);
		glVertex3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 0.0f,  0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f,  0.0f);
		glVertex3f(0.0f, 0.0f,  1.0f);
	glEnd();

	glFlush();
	swap_buffers();
}
