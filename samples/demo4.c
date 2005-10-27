//------------------------------------------------------------------------
// File:   demo4.c
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


extern unsigned int testbmp[];
extern unsigned int testbmp_w;
extern unsigned int testbmp_h;

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

GLfloat cube_t[][2] = {
	 { 0.0f, 0.0f }
	,{ 2.0f, 0.0f }
	,{ 2.0f, 2.0f }
	,{ 0.0f, 2.0f }
};

GLuint	tname;
GLint	texmode;

//------------------------------------------------------------------------
void demo_init(void)
{
	glShadeModel(GL_FLAT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); not implemented yet
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  not implemented yet

	glGenTextures(1, &tname);
	glBindTexture(GL_TEXTURE_2D, tname);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, testbmp_w, testbmp_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, testbmp);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 11.0f);
}

//------------------------------------------------------------------------
void demo_end(void)
{
}

//------------------------------------------------------------------------
void demo_tick(void)
{
static GLfloat rot = 0.0f;

	rot += 0.5f;
	if(rot >= 360.0f)
	{
// Toggle blending every 360 degrees...doesn't look very good but leaving as sample code
//		glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &texmode);
//		if(texmode==GL_DECAL)
//			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//		else
//			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		rot = 0.0f;
	}

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(rot, 0.0f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);

		// front face
		glTexCoord2fv(cube_t[2]); glVertex3fv(cube_v[2]);
		glTexCoord2fv(cube_t[1]); glVertex3fv(cube_v[1]);
		glTexCoord2fv(cube_t[0]); glVertex3fv(cube_v[0]);

		glTexCoord2fv(cube_t[2]); glVertex3fv(cube_v[2]);
		glTexCoord2fv(cube_t[0]); glVertex3fv(cube_v[0]);
		glTexCoord2fv(cube_t[3]); glVertex3fv(cube_v[3]);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);

		// back face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(cube_v[6]);
		glVertex3fv(cube_v[5]);
		glVertex3fv(cube_v[4]);

		glVertex3fv(cube_v[6]);
		glVertex3fv(cube_v[4]);
		glVertex3fv(cube_v[7]);

		// left face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3fv(cube_v[7]);
		glVertex3fv(cube_v[3]);
		glVertex3fv(cube_v[0]);

		glVertex3fv(cube_v[7]);
		glVertex3fv(cube_v[0]);
		glVertex3fv(cube_v[4]);

		// right face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(cube_v[2]);
		glVertex3fv(cube_v[6]);
		glVertex3fv(cube_v[5]);

		glVertex3fv(cube_v[2]);
		glVertex3fv(cube_v[5]);
		glVertex3fv(cube_v[1]);

		// top face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3fv(cube_v[1]);
		glVertex3fv(cube_v[5]);
		glVertex3fv(cube_v[4]);

		glVertex3fv(cube_v[1]);
		glVertex3fv(cube_v[4]);
		glVertex3fv(cube_v[0]);

		// bottom face
		glColor3f(1.0f, 0.0f, 1.0f);
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
