//---------------------------------------------------------------------------
// File:   defines.h
// Author: Tony Saveski, tony@ui.com.au
//---------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//---------------------------------------------------------------------------
// Licenced under Academic Free License version 2.0
// Read DreamGL LICENSE.txt file for further details.
//---------------------------------------------------------------------------
#ifndef DEFINES_H
#define DEFINES_H

#define SUCCESS		1
#define FAILURE		0

typedef char	int8;
typedef short	int16;
typedef int		int32;

typedef unsigned char	uint8;
typedef unsigned short	uint16;
typedef unsigned int	uint32;

//---------------------------------------------------------------------------
#ifdef WIN32
typedef unsigned __int64	uint64;
typedef __int64				int64;
#define __attribute__(X)
#endif

#endif // DEFINES_H
