//------------------------------------------------------------------------
// File:   gs_regs.h
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
#ifndef GS_REGS_H
#define GS_REGS_H

// Playstation2 GS Privileged Registers
#define pmode		0x12000000	// Setup CRT Controller
#define smode2		0x12000020	// CRTC Video Settings: PAL/NTCS, Interlace, etc.
#define dispfb1		0x12000070	// Setup the CRTC's Read Circuit 1 data source settings
#define display1	0x12000080	// RC1 display output settings
#define dispfb2		0x12000090	// Setup the CRTC's Read Circuit 2 data source settings
#define display2	0x120000a0	// RC2 display output settings
#define extbuf		0x120000b0	// ...
#define extdata		0x120000c0	// ...
#define extwrite	0x120000d0	// ...
#define bgcolor		0x120000e0	// Set CRTC background color
#define csr			0x12001000	// System status and reset
#define imr			0x12001010	// Interrupt Mask Register
#define busdir		0x12001040	// ...
#define siglblid	0x12001080	// ...

// Playstation2 GS General Purpose Registers
#define prim		0x00	// Select and configure current drawing primitive
#define rgbaq		0x01	// Setup current vertex color
#define st			0x02	// ...
#define uv			0x03	// Specify Vertex Texture Coordinates
#define xyzf2		0x04	// Set vertex coordinate
#define xyz2		0x05	// Set vertex coordinate and 'kick' drawing
#define tex0_1		0x06	// Texture Buffer Setup (Context 1)
#define tex0_2		0x07	// Texture Buffer Setup (Context 2)
#define clamp_1		0x08	// ...
#define clamp_2		0x09	// ...
#define fog			0x0a	// ...
#define xyzf3		0x0c	// ...
#define xyz3		0x0d	// ...
#define tex1_1		0x14	// ...
#define tex1_2		0x15	// ...
#define tex2_1		0x16	// ...
#define tex2_2		0x17	// ...
#define xyoffset_1	0x18	// Mapping from Primitive to Window coordinate system (Context 1)
#define xyoffset_2	0x19	// Mapping from Primitive to Window coordinate system (Context 2)
#define prmodecont	0x1a	// Select who sets primitive drawing mode, PRIM or PRMODE.
#define prmode		0x1b	// Primitive Drawing Mode settings
#define texclut		0x1c	// ...
#define scanmsk		0x22	// ...
#define miptbp1_1	0x34	// ...
#define miptbp1_2	0x35	// ...
#define miptbp2_1	0x36	// ...
#define miptbp2_2	0x37	// ...
#define texa		0x3b	// ...
#define fogcol		0x3d	// ...
#define texflush	0x3f	// Write to this register before using newly loaded texture
#define scissor_1	0x40	// Setup clipping rectangle (Context 1)
#define scissor_2	0x41	// Setup clipping rectangle (Context 2)
#define alpha_1		0x42	// Setup Alpha Blending Parameters (Context 1)
#define alpha_2		0x43	// Setup Alpha Blending Parameters (Context 2)
#define dimx		0x44	// ...
#define dthe		0x45	// ...
#define colclamp	0x46	// ...
#define test_1		0x47	// ...
#define test_2		0x48	// ...
#define pabe		0x49	// ...
#define fba_1		0x4a	// ...
#define fba_2		0x4b	// ...
#define frame_1		0x4c	// Frame buffer settings (Context 1)
#define frame_2		0x4d	// Frame buffer settings (Context 2)
#define zbuf_1		0x4e	// ...
#define zbuf_2		0x4f	// ...
#define bitbltbuf	0x50	// Setup Image Transfer Between EE and GS
#define trxpos		0x51	// Setup Image Transfer Coordinates
#define trxreg		0x52	// Setup Image Transfer Size
#define trxdir		0x53	// Set Image Transfer Directon + Start Transfer
#define hwreg		0x54	// ...
#define signal		0x60	// ...
#define finish		0x61	// ...
#define label		0x62	// ...

#endif // GS_REGS_H
