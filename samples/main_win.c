//------------------------------------------------------------------------
// File:   main_win.c
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
#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <GL/gl.h>

//------------------------------------------------------------------------
extern void demo_init(void);
extern void demo_tick(void);
extern void demo_end(void);

//------------------------------------------------------------------------
HINSTANCE	g_win_instance;
WNDCLASSEX	g_win_class;
ATOM		g_win_atom;
HWND		g_win_h;
char		g_win_class_name[64];
char		g_str[256];

int			g_full_screen	= 0;
int			g_screen_width	= 512;
int			g_screen_height	= 256;
int			g_screen_bpp	= 32;
int			g_zbuf_bpp		= 32;

HDC						gl_hdc;
HGLRC					gl_hrc;
PIXELFORMATDESCRIPTOR	gl_pfd;
DEVMODE					g_old_mode;
int						g_full_screen_set;

//------------------------------------------------------------------------
void swap_buffers(void)
{
	SwapBuffers(gl_hdc);
}

//------------------------------------------------------------------------
int end(void)
{
	if(gl_hrc)
	{
		wglDeleteContext(gl_hrc);
		gl_hrc = NULL;
	}

	if(gl_hdc)
	{
		ReleaseDC(g_win_h, gl_hdc);
		gl_hdc = NULL;
	}

	if(g_full_screen_set)
	{
		if(ChangeDisplaySettings(&g_old_mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) return(0);
	}

	return(1);
}

//------------------------------------------------------------------------
int init(void)
{
int		pf_id;
DEVMODE	dev_mode;

	if(g_full_screen)
	{
		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &g_old_mode);

		dev_mode.dmSize			= sizeof(dev_mode);
		dev_mode.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		dev_mode.dmBitsPerPel	= g_screen_bpp;
		dev_mode.dmPelsWidth	= g_screen_width;
		dev_mode.dmPelsHeight	= g_screen_height;
		g_full_screen_set		= 0;
		if(ChangeDisplaySettings(&dev_mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) return(0);
		g_full_screen_set = 1;
	}

	gl_hdc = NULL;
	gl_hrc = NULL;

	memset(&gl_pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	gl_pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
	gl_pfd.nVersion   = 1;
	gl_pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	gl_pfd.iPixelType = PFD_TYPE_RGBA;
	gl_pfd.cColorBits = g_screen_bpp;
	gl_pfd.cDepthBits = g_zbuf_bpp;
	gl_pfd.iLayerType = PFD_MAIN_PLANE;

	gl_hdc = GetDC(g_win_h);
	if(!gl_hdc) goto ERR_init;

	pf_id = ChoosePixelFormat(gl_hdc, &gl_pfd);
	if(!pf_id) goto ERR_init;

//	if(g_screen_bpp != gl_pfd.cColorBits)
//		log_print("WARNING: init(): g_screen_bpp of %d requested, but could only get %d.\n", g_screen_bpp, gl_pfd.cColorBits);

//	if(g_zbuf_bpp != gl_pfd.cDepthBits)
//		log_print("WARNING: init(): g_zbuf_bpp of %d requested, but could only get %d.\n", g_zbuf_bpp, gl_pfd.cDepthBits);

	g_screen_bpp = gl_pfd.cColorBits;
	g_zbuf_bpp   = gl_pfd.cDepthBits;

	if(!SetPixelFormat(gl_hdc, pf_id, &gl_pfd)) goto ERR_init;

	gl_hrc = wglCreateContext(gl_hdc);
	if(!gl_hrc) goto ERR_init;

	if(wglMakeCurrent(gl_hdc, gl_hrc) == FALSE) goto ERR_init;

	return(1);

ERR_init:
	end();
	return(0);
}


//------------------------------------------------------------------------
// WINMAIN and WINPROC FUNCTIONS
//------------------------------------------------------------------------

//------------------------------------------------------------------------
LRESULT WINAPI MainWindowProc(HWND win, UINT msg, WPARAM wparam, LPARAM lparam);

//------------------------------------------------------------------------
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnClose(HWND hwnd);
void OnDestroy(HWND hwnd);

//------------------------------------------------------------------------
int WINAPI WinMain(
	HINSTANCE	instance,
	HINSTANCE	previnst,
	LPSTR		cmdline,
	int			cmdshow)
{
MSG		msg;
DWORD	win_style;
int		win_width;
int		win_height;

	// Setup window stuff
	g_win_instance = instance;
	strcpy(g_win_class_name, "DreamGL_cls");

	memset(&g_win_class, 0, sizeof(g_win_class));
	g_win_class.cbSize        = sizeof(WNDCLASSEX);
	g_win_class.lpfnWndProc   = MainWindowProc;
	g_win_class.style         = CS_HREDRAW | CS_VREDRAW;//CS_CLASSDC;
	g_win_class.cbClsExtra    = 0;
	g_win_class.cbWndExtra    = 0;
	g_win_class.hInstance     = g_win_instance;
	g_win_class.hIcon         = LoadIcon(g_win_instance, MAKEINTRESOURCE(IDI_APPLICATION));
	g_win_class.hIconSm       = g_win_class.hIcon;
	g_win_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
	g_win_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	g_win_class.lpszClassName = g_win_class_name;
	g_win_class.lpszMenuName  = NULL;

	g_win_atom = RegisterClassEx(&g_win_class);
	if(INVALID_ATOM == g_win_atom)
	{
		MessageBox(0, "Invalid ATOM returned by RegisterClassEx()!", "ERROR!", MB_OK);
		return(0);
	}

	win_style = WS_OVERLAPPEDWINDOW;
	if(g_full_screen) win_style = WS_POPUP;

	// In windowed mode, account for window border and caption bar.
	win_width  = g_screen_width;
	win_height = g_screen_height;
	if(!g_full_screen)
	{
		win_width  += (GetSystemMetrics(SM_CXFRAME)*2);
		win_height += (GetSystemMetrics(SM_CYFRAME)*2)+GetSystemMetrics(SM_CYCAPTION);
	}

	g_win_h = CreateWindowEx(
		WS_EX_APPWINDOW,
		MAKEINTATOM(g_win_atom),
		"DreamGL Demo",
		win_style,
		0, 0, win_width, win_height,
		NULL, NULL, g_win_instance, NULL);

	if(!IsWindow(g_win_h))
	{
		MessageBox(0, "Invalid HWND returned by CreateWindowEx()!", "ERROR!", MB_OK);
		return(0);
	}

	ShowWindow(g_win_h, cmdshow);
	UpdateWindow(g_win_h);



	if(!init())
	{
		MessageBox(0, "Failed to initialize OpenGL!", "ERROR!", MB_OK);
		return(0);
	}
	demo_init();

	while(TRUE)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if(WM_QUIT == msg.message)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			demo_tick();
		}
	}

	demo_end();
	end();



	UnregisterClass(MAKEINTATOM(g_win_atom), instance);
	return(msg.wParam);
}

//------------------------------------------------------------------------
LRESULT WINAPI MainWindowProc(
	HWND	hwnd,
	UINT	msg,
	WPARAM	wParam,
	LPARAM	lParam)
{
	switch(msg)
	{
		HANDLE_MSG(hwnd, WM_CREATE,		OnCreate);
		HANDLE_MSG(hwnd, WM_CLOSE,		OnClose);
		HANDLE_MSG(hwnd, WM_DESTROY,	OnDestroy);
	}
	return(DefWindowProc(hwnd, msg, wParam, lParam));
}

//------------------------------------------------------------------------
// MAIN WINDOW MESSAGE HANDLERS
//------------------------------------------------------------------------

//------------------------------------------------------------------------
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	return(TRUE);
}

//------------------------------------------------------------------------
void OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
}

//------------------------------------------------------------------------
void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}
