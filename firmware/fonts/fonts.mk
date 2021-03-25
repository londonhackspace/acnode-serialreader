###############################################################################
# Makefile for ACNodeReader Firmware - Fonts                                  #
#                                                                             #
# Based on mcufont make file mcufont/fonts/Makefile                           #
#                                                                             #
# (c) 2020 London Hackspace                                                   #
# Released under a 3-clause BSD license. See included LICENSE file.           #
#                                                                             #
###############################################################################

MCUFONT = mcufont/encoder/mcufont

$(MCUFONT):
	make -C mcufont/encoder mcufont

CHARS = 0-255 0x2010-0x2015

# Names of fonts to process
FONTS = fixed_7x14
#FONTS = fixed_5x8 fixed_7x14 fixed_10x20

FONT_SOURCES_F = $(FONTS:%=build/fonts/%)
FONT_SOURCES = $(FONT_SOURCES_F:=.c)
FONT_DATS = $(FONT_SOURCES_F:=.dat)

build/fonts/fonts.h: $(FONT_SOURCES)
	mkdir -p `dirname $@`
	/bin/echo -e $(foreach font,$(FONTS),'\n#include "'$(font)'.c"') > $@

build/fonts/%.c: build/fonts/%.dat $(MCUFONT)
	mkdir -p `dirname $@`
	$(MCUFONT) bwfont_export $<

build/fonts/%.bdf: mcufont/fonts/%.bdf
	mkdir -p `dirname $@`
	cp -f $< $@

build/fonts/%.dat: build/fonts/%.bdf
	mkdir -p `dirname $@`
	$(MCUFONT) import_bdf $<
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 50