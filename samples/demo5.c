//------------------------------------------------------------------------
// File:   demo5.c
// Author: Tony Saveski, tony@ui.com.au
// Note:   Algorithm & Bitmap by Jan Horn, http://www.sulaco.co.za
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
