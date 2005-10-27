//------------------------------------------------------------------------
// File:   demo2.c
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
