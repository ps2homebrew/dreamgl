#ifndef GL_H
#define GL_H

// GL data types
typedef unsigned char				GLboolean;
typedef signed char					GLbyte;
typedef unsigned int				GLbitfield;
typedef float						GLclampf;
typedef double						GLclampd;
typedef double						GLdouble;
typedef unsigned int				GLenum;
typedef float						GLfloat;
typedef int							GLint;
typedef short						GLshort;
typedef int							GLsizei;
typedef unsigned char				GLubyte;
typedef unsigned int				GLuint;
typedef unsigned short				GLushort;
typedef void						GLvoid;

// Boolean values
#define GL_FALSE					0
#define GL_TRUE						1

// GL error codes
#define GL_NO_ERROR					0x0000
#define GL_INVALID_ENUM				0x0500
#define GL_INVALID_VALUE			0x0501
#define GL_INVALID_OPERATION		0x0502
#define GL_STACK_OVERFLOW			0x0503
#define GL_STACK_UNDERFLOW			0x0504
#define GL_OUT_OF_MEMORY			0x0505

// Drawing buffers
#define GL_FRONT					0x0404
#define GL_BACK						0x0405

// Depth Buffer
#define GL_DEPTH_TEST				0x0b71

// Depth Func
#define GL_NEVER					0x0200
#define GL_LESS						0x0201
#define GL_LEQUAL					0x0203
#define GL_ALWAYS					0x0207

// glClear bits
#define GL_DEPTH_BUFFER_BIT			0x00000100
#define GL_COLOR_BUFFER_BIT			0x00004000
#define GL_ALL_ATTRIB_BITS			0x000fffff

// glMatrixMode
#define GL_MODELVIEW				0x1700
#define GL_PROJECTION				0x1701
#define GL_TEXTURE					0x1702

// Begin/End Modes
#define GL_POINTS					0x0000
#define GL_LINES					0x0001
#define GL_LINE_LOOP				0x0002
#define GL_LINE_STRIP				0x0003
#define GL_TRIANGLES				0x0004
#define GL_TRIANGLE_STRIP			0x0005
#define GL_TRIANGLE_FAN				0x0006
//#define GL_QUADS					0x0007
//#define GL_QUAD_STRIP				0x0008
//#define GL_POLYGON				0x0009

// Shading Models
#define GL_FLAT						0x1d00
#define GL_SMOOTH					0x1d01

// Texture Targets
#define GL_TEXTURE_2D				0x0de1

// Texture Parameters
#define GL_TEXTURE_MAG_FILTER		0x2800
#define GL_TEXTURE_MIN_FILTER		0x2801
#define GL_TEXTURE_WRAP_S			0x2802
#define GL_TEXTURE_WRAP_T			0x2803
#define GL_TEXTURE_WIDTH			0x1000
#define GL_TEXTURE_HEIGHT			0x1001
//#define GL_TEXTURE_INTERNAL_FORMAT	0x1003
//#define GL_TEXTURE_COMPONENTS		GL_TEXTURE_INTERNAL_FORMAT
//#define GL_TEXTURE_BORDER_COLOR		0x1004
//#define GL_TEXTURE_BORDER			0x1005
//#define GL_TEXTURE_RED_SIZE		0x805C
//#define GL_TEXTURE_GREEN_SIZE		0x805D
//#define GL_TEXTURE_BLUE_SIZE		0x805E
//#define GL_TEXTURE_ALPHA_SIZE		0x805F
//#define GL_TEXTURE_LUMINANCE_SIZE	0x8060
//#define GL_TEXTURE_INTENSITY_SIZE	0x8061
//#define GL_TEXTURE_PRIORITY			0x8066
#define GL_TEXTURE_RESIDENT			0x8067

// Texture Mag Filter
#define GL_NEAREST					0x2600
#define GL_LINEAR					0x2601

// Texture Wrap Mode
#define GL_CLAMP					0x2900
#define GL_REPEAT					0x2901

// Texture Env
#define GL_TEXTURE_ENV				0x2300
#define GL_TEXTURE_ENV_MODE			0x2200

// Texture Env Modes
#define GL_MODULATE					0x2100
#define GL_DECAL					0x2101

// Texture Pixel Formats
//#define GL_RGB					0x1907
#define GL_RGBA						0x1908

// Pixel Data Types
#define GL_UNSIGNED_BYTE			0x1401

// GL functions
extern void		glBegin(GLenum mode);
extern void		glBindTexture(GLenum target, GLuint texture);
extern void		glClear(GLbitfield mask);
extern void		glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
extern void		glColor3b(GLbyte red, GLbyte green, GLbyte blue);
extern void		glColor3bv(const GLbyte *v);
extern void		glColor3d(GLdouble red, GLdouble green, GLdouble blue);
extern void		glColor3dv(const GLdouble *v);
extern void		glColor3f(GLfloat red, GLfloat green, GLfloat blue);
extern void		glColor3fv(const GLfloat *v);
extern void		glColor3i(GLint red, GLint green, GLint blue);
extern void		glColor3iv(const GLint *v);
extern void		glColor3s(GLshort red, GLshort green, GLshort blue);
extern void		glColor3sv(const GLshort *v);
extern void		glColor3ub(GLubyte red, GLubyte green, GLubyte blue);
extern void		glColor3ubv(const GLubyte *v);
extern void		glColor3ui(GLuint red, GLuint green, GLuint blue);
extern void		glColor3uiv(const GLuint *v);
extern void		glColor3us(GLushort red, GLushort green, GLushort blue);
extern void		glColor3usv(const GLushort *v);
extern void		glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
extern void		glColor4bv(const GLbyte *v);
extern void		glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
extern void		glColor4dv(const GLdouble *v);
extern void		glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern void		glColor4fv(const GLfloat *v);
extern void		glColor4i(GLint red, GLint green, GLint blue, GLint alpha);
extern void		glColor4iv(const GLint *v);
extern void		glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha);
extern void		glColor4sv(const GLshort *v);
extern void		glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
extern void		glColor4ubv(const GLubyte *v);
extern void		glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha);
extern void		glColor4uiv(const GLuint *v);
extern void		glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha);
extern void		glColor4usv(const GLushort *v);
extern void		glDeleteTextures(GLsizei n, const GLuint *textures);
extern void		glDepthFunc(GLenum func);
extern void		glDepthMask(GLboolean flag);
extern void		glDisable(GLenum cap);
extern void		glDrawBuffer(GLenum mode);
extern void		glEnable(GLenum cap);
extern void		glEnd(void);
extern void		glFinish(void);
extern void		glFlush(void);
extern void		glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern void		glGenTextures(GLsizei n, GLuint *textures);
extern GLenum	glGetError(void);
extern void		glGetTexEnvfv(GLenum target, GLenum pname, GLfloat *params);
extern void		glGetTexEnviv(GLenum target, GLenum pname, GLint *params);
extern GLboolean glIsEnabled(GLenum cap);
extern GLboolean glIsTexture(GLuint texture);
extern void		glLoadIdentity(void);
extern void		glLoadMatrixd(const GLdouble *m);
extern void		glLoadMatrixf(const GLfloat *m);
extern void		glMatrixMode(GLenum mode);
extern void		glMultMatrixd(const GLdouble *m);
extern void		glMultMatrixf(const GLfloat *m);
extern void		glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern void		glPushMatrix(void);
extern void		glPopMatrix(void);
extern void		glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
extern void		glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
extern void		glScaled(GLdouble x, GLdouble y, GLdouble z);
extern void		glScalef(GLfloat x, GLfloat y, GLfloat z);
extern void		glShadeModel(GLenum mode);
extern void		glTexCoord1d(GLdouble s);
extern void		glTexCoord1dv(const GLdouble *v);
extern void		glTexCoord1f(GLfloat s);
extern void		glTexCoord1fv(const GLfloat *v);
extern void		glTexCoord1i(GLint s);
extern void		glTexCoord1iv(const GLint *v);
extern void		glTexCoord1s(GLshort s);
extern void		glTexCoord1sv(const GLshort *v);
extern void		glTexCoord2d(GLdouble s, GLdouble t);
extern void		glTexCoord2dv(const GLdouble *v);
extern void		glTexCoord2f(GLfloat s, GLfloat t);
extern void		glTexCoord2fv(const GLfloat *v);
extern void		glTexCoord2i(GLint s, GLint t);
extern void		glTexCoord2iv(const GLint *v);
extern void		glTexCoord2s(GLshort s, GLshort t);
extern void		glTexCoord2sv(const GLshort *v);
extern void		glTexCoord3d(GLdouble s, GLdouble t, GLdouble r);
extern void		glTexCoord3dv(const GLdouble *v);
extern void		glTexCoord3f(GLfloat s, GLfloat t, GLfloat r);
extern void		glTexCoord3fv(const GLfloat *v);
extern void		glTexCoord3i(GLint s, GLint t, GLint r);
extern void		glTexCoord3iv(const GLint *v);
extern void		glTexCoord3s(GLshort s, GLshort t, GLshort r);
extern void		glTexCoord3sv(const GLshort *v);
extern void		glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
extern void		glTexCoord4dv(const GLdouble *v);
extern void		glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
extern void		glTexCoord4fv(const GLfloat *v);
extern void		glTexCoord4i(GLint s, GLint t, GLint r, GLint q);
extern void		glTexCoord4iv(const GLint *v);
extern void		glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q);
extern void		glTexCoord4sv(const GLshort *v);
extern void		glTexEnvf(GLenum target, GLenum pname, GLfloat param);
extern void		glTexEnvfv(GLenum target, GLenum pname, const GLfloat *params);
extern void		glTexEnvi(GLenum target, GLenum pname, GLint param);
extern void		glTexEnviv(GLenum target, GLenum pname, const GLint *params);
extern void		glTexImage2D(GLenum target, GLint level, GLint components, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
extern void		glTexParameterf(GLenum target, GLenum pname, GLfloat param);
extern void		glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params);
extern void		glTexParameteri(GLenum target, GLenum pname, GLint param);
extern void		glTexParameteriv(GLenum target, GLenum pname, const GLint *params);
extern void		glTranslated(GLdouble x, GLdouble y, GLdouble z);
extern void		glTranslatef(GLfloat x, GLfloat y, GLfloat z);
extern void		glVertex2d(GLdouble x, GLdouble y);
extern void		glVertex2dv(const GLdouble *v);
extern void		glVertex2f(GLfloat x, GLfloat y);
extern void		glVertex2fv(const GLfloat *v);
extern void		glVertex2i(GLint x, GLint y);
extern void		glVertex2iv(const GLint *v);
extern void		glVertex2s(GLshort x, GLshort y);
extern void		glVertex2sv(const GLshort *v);
extern void		glVertex3d(GLdouble x, GLdouble y, GLdouble z);
extern void		glVertex3dv(const GLdouble *v);
extern void		glVertex3f(GLfloat x, GLfloat y, GLfloat z);
extern void		glVertex3fv(const GLfloat *v);
extern void		glVertex3i(GLint x, GLint y, GLint z);
extern void		glVertex3iv(const GLint *v);
extern void		glVertex3s(GLshort x, GLshort y, GLshort z);
extern void		glVertex3sv(const GLshort *v);
extern void		glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern void		glVertex4dv(const GLdouble *v);
extern void		glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void		glVertex4fv(const GLfloat *v);
extern void		glVertex4i(GLint x, GLint y, GLint z, GLint w);
extern void		glVertex4iv(const GLint *v);
extern void		glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w);
extern void		glVertex4sv(const GLshort *v);
extern void		glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

#endif // GL_H
