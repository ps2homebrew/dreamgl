//------------------------------------------------------------------------
// File:   demo3.c
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


//------------------------------------------------------------------------
void demo_init(void)
{
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------
void demo_end(void)
{
}

//------------------------------------------------------------------------
void draw(void)
{
	glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);

	glEnd();
}

//------------------------------------------------------------------------
void demo_tick(void)
{
static GLfloat rot = 0.0f;
static int flat = 1;

	rot += 3.0f;
	if(rot >= 360.0f)
	{
		if(flat) { glShadeModel(GL_SMOOTH); flat = 0; }
		else { glShadeModel(GL_FLAT); flat = 1; }
		rot = 0.0f;
	}

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rot, 0.0f, 1.0f, 0.5f);

	glViewport(0,   0,   256, 128); draw();
	glViewport(256, 0,   256, 128); draw();
	glViewport(0,   128, 256, 128); draw();
	glViewport(256, 128, 256, 128); draw();

	glFlush();
	swap_buffers();
}
