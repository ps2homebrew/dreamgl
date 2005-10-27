#----------------------------------------------------------------------------
# File:		Makefile for PS2CPU Version
# Author:	Tony Saveski, tony@ui.com.au
#----------------------------------------------------------------------------
# Copyright (c) 2003, Unicorn Interactive Pty Ltd.
# All Rights Reserved.
#----------------------------------------------------------------------------
# Licenced under Academic Free License version 2.0
# Read DreamGL LICENSE.txt file for further details.
#----------------------------------------------------------------------------
CC=ee-gcc
AS=ee-as
LD=ee-ld
AR=ee-ar

#PS2SDK=/usr/local/ps2dev
#PS2SDK=/usr/local/ps2lib-2.0beta

DIR_BIN=bin
DIR_LIB=lib
DIR_INC=include
DIR_SRC_PS2CPU=src
DIR_SRC_SAMPLES=samples

LIB_DREAMGL=$(DIR_LIB)/libdreamgl.a

STD_LIBS=-lm -lc -lkernel -lc -lgcc
DEMO_LIBS= -ldreamgl -lps2Perf -L$(PS2DEV)/ps2Perf/lib $(STD_LIBS) 

CFLAGS= \
	-Wall -W -EL -G0 -O3 -mips3 -nostdlib \
	-I$(PS2DEV)/ps2Perf/include \
	-I$(DIR_INC) \
	-I$(DIR_SRC_PS2CPU) \
	-I$(DIR_SRC_PS2CPU) \
	-I$(PS2SDK)/common/include \
	-I$(PS2SDK)/ee/include \
	-L$(PS2SDK)/ee/lib \
	-L$(DIR_LIB) \
	-DDGL_PS2

LINKFILE=$(PS2SDK)/ee/startup/linkfile
CRTFILE=$(PS2SDK)/ee/startup/crt0.o

CSRC = \
	$(DIR_SRC_PS2CPU)/ee.c \
	$(DIR_SRC_PS2CPU)/gs.c \
	$(DIR_SRC_PS2CPU)/gl.c \
	$(DIR_SRC_PS2CPU)/dgl.c \
	$(DIR_SRC_PS2CPU)/ps2_dgl.c \
	$(DIR_SRC_PS2CPU)/gl_color.c \
	$(DIR_SRC_PS2CPU)/gl_enable.c \
	$(DIR_SRC_PS2CPU)/gl_matrix.c \
	$(DIR_SRC_PS2CPU)/gl_texcoord.c \
	$(DIR_SRC_PS2CPU)/gl_texture.c \
	$(DIR_SRC_PS2CPU)/gl_vertex.c

SSRC = \
	$(DIR_SRC_PS2CPU)/ee_asm.s \
	$(DIR_SRC_PS2CPU)/dma_asm.s \
	$(DIR_SRC_PS2CPU)/gs_asm.s

COBJ=$(CSRC:.c=.o)
SOBJ=$(SSRC:.s=.o)
OBJ=$(COBJ) $(SOBJ)


all: $(DIR_BIN) $(DIR_LIB) $(LIB_DREAMGL) $(DIR_BIN)/demo1.elf $(DIR_BIN)/demo2.elf $(DIR_BIN)/demo3.elf $(DIR_BIN)/demo4.elf $(DIR_BIN)/demo5.elf

$(DIR_BIN):
	mkdir -p $(DIR_BIN)

$(DIR_LIB):
	mkdir -p $(DIR_LIB)

$(LIB_DREAMGL): $(OBJ)
	@echo "-------------------------------------------------"
	$(AR) -cr $(LIB_DREAMGL) $(OBJ)

$(DIR_BIN)/demo1.elf: $(LIB_DREAMGL) $(DIR_SRC_SAMPLES)/main_ps2.o $(DIR_SRC_SAMPLES)/demo1.o
	@echo "-------------------------------------------------"
	$(CC) $(CFLAGS) -T$(LINKFILE) -o $(DIR_BIN)/demo1.elf $(DIR_SRC_SAMPLES)/main_ps2.o $(DIR_SRC_SAMPLES)/demo1.o $(CRTFILE) $(DEMO_LIBS)

$(DIR_BIN)/demo2.elf: $(LIB_DREAMGL) $(DIR_SRC_SAMPLES)/main_ps2.o $(DIR_SRC_SAMPLES)/demo2.o
	@echo "-------------------------------------------------"
	$(CC) $(CFLAGS) -T$(LINKFILE) -o $(DIR_BIN)/demo2.elf $(DIR_SRC_SAMPLES)/main_ps2.o $(DIR_SRC_SAMPLES)/demo2.o $(CRTFILE) $(DEMO_LIBS)

$(DIR_BIN)/demo3.elf: $(LIB_DREAMGL) $(DIR_SRC_SAMPLES)/main_ps2.o $(DIR_SRC_SAMPLES)/demo3.o
	@echo "-------------------------------------------------"
	$(CC) $(CFLAGS) -T$(LINKFILE) -o $(DIR_BIN)/demo3.elf $(DIR_SRC_SAMPLES)/main_ps2.o $(DIR_SRC_SAMPLES)/demo3.o $(CRTFILE) $(DEMO_LIBS)

$(DIR_BIN)/demo4.elf: $(LIB_DREAMGL) $(DIR_SRC_SAMPLES)/main_ps2.o $(DIR_SRC_SAMPLES)/demo4.o $(DIR_SRC_SAMPLES)/testbmp.o
	@echo "-------------------------------------------------"
	$(CC) $(CFLAGS) -T$(LINKFILE) -o $(DIR_BIN)/demo4.elf $(DIR_SRC_SAMPLES)/main_ps2.o $(DIR_SRC_SAMPLES)/demo4.o $(DIR_SRC_SAMPLES)/testbmp.o $(CRTFILE) $(DEMO_LIBS)

$(DIR_BIN)/demo5.elf: $(LIB_DREAMGL) $(DIR_SRC_SAMPLES)/main_ps2.o $(DIR_SRC_SAMPLES)/demo5.o $(DIR_SRC_SAMPLES)/tunnel.o
	@echo "-------------------------------------------------"
	$(CC) $(CFLAGS) -T$(LINKFILE) -o $(DIR_BIN)/demo5.elf $(DIR_SRC_SAMPLES)/main_ps2.o $(DIR_SRC_SAMPLES)/demo5.o $(DIR_SRC_SAMPLES)/tunnel.o $(CRTFILE) $(DEMO_LIBS)



%.o: %.c
	@echo "-------------------------------------------------"
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.s
	@echo "-------------------------------------------------"
	$(CC) -xassembler-with-cpp -c $(CFLAGS) $< -o $@

install: all
	mkdir -p $(PS2DEV)/dreamgl/include/GL
	mkdir -p $(PS2DEV)/dreamgl/lib
	cp -f $(LIB_DREAMGL) $(PS2DEV)/dreamgl/lib
	cp -f include/GL/*.h $(PS2DEV)/dreamgl/include/GL


clean:
	rm -f $(OBJ) $(DIR_SRC_SAMPLES)/*.o $(DIR_BIN)/*.elf $(LIB_DREAMGL)

d2u:
	dos2unix Makefile LICENSE.txt README.txt CHANGES.txt
	dos2unix $(DIR_SRC_PS2CPU)/*.c $(DIR_SRC_PS2CPU)/*.h $(DIR_SRC_PS2CPU)/*.s
	dos2unix $(DIR_SRC_SAMPLES)/*.c

