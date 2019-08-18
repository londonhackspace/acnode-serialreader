###############################################################################
# Makefile for ACNodeReader Firmware - DebugBoard09 Target                    #
#                                                                             #
# (c) 2019 London Hackspace                                                   #
# Released under a 3-clause BSD license. See included LICENSE file.           #
#                                                                             #
###############################################################################

# The MCU target as used by GCC
MCU=atmega88pa

# The programming target
AVRDUDE_TARGET=m88p
AVRDUDE_PROGRAMMER=usbasp
# slow it down for the first program, at least
#AVRDUDE_EXTRA_OPTS=-B1000 -U lfuse:w:0xce:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m
AVRDUDE_EXTRA_OPTS=-U lfuse:w:0xce:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m

# The clock frequency, in Hz of the crystal
FREQUENCY=16000000

# Any extra, target-specific CFLAGS
CFLAGS_TARGET=

# target-specific sources
TARGET_SOURCES=