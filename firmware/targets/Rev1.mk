###############################################################################
# Makefile for ACNodeReader Firmware - Rev1 Target with atmega329pb           #
#                                                                             #
# (c) 2019 London Hackspace                                                   #
# Released under a 3-clause BSD license. See included LICENSE file.           #
#                                                                             #
###############################################################################

# The MCU target as used by GCC - it's actually a 328pb but this keeps better software compatibility
MCU=atmega88pb

# The programming target - this needs a trunk version of avrdude (or the avrdude.conf from it anyway)
AVRDUDE_TARGET=m88pb
#AVRDUDE_PROGRAMMER=atmelice_isp
AVRDUDE_PROGRAMMER=usbasp
# slow it down for the first program, at least
#AVRDUDE_EXTRA_OPTS=-B1000 -U lfuse:w:0xce:m -U hfuse:w:0xd9:m -U efuse:w:0xf3:m -C /data/projects/z80-board/z80-board-tools/avr-toolchain/outdir/etc/avrdude.conf
AVRDUDE_EXTRA_OPTS=-U lfuse:w:0xce:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m
#AVRDUDE_EXTRA_OPTS=-U lfuse:w:0xce:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m

# The clock frequency, in Hz of the crystal
FREQUENCY=16000000

# Any extra, target-specific CFLAGS
CFLAGS_TARGET=

# target-specific sources
TARGET_SOURCES= src/lm75.c

fuses:
	avrdude -p ${AVRDUDE_TARGET} -c $(AVRDUDE_PROGRAMMER) $(AVRDUDE_EXTRA_OPTS) -B1000

# rules to enable and disable debugwire protocol - note that once enabled, you need a debugwire
# programmer to disable for normal programming!
debug:
	avrdude -p ${AVRDUDE_TARGET} -c atmelice_isp -U hfuse:w:0x9f:m

undebug:
	avrdude -p ${AVRDUDE_TARGET} -c atmelice_dw -U hfuse:w:0xdf:m	