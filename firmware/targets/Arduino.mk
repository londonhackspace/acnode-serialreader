###############################################################################
# Makefile for ACNodeReader Firmware - Arduino Target                         #
#                                                                             #
# (c) 2019 London Hackspace                                                   #
# Released under a 3-clause BSD license. See included LICENSE file.           #
#                                                                             #
###############################################################################

# The MCU target as used by GCC
MCU=atmega328p

ARDUINO_PORT ?= /dev/cu.usbmodem14101

# The programming target
AVRDUDE_TARGET=m328p
AVRDUDE_PROGRAMMER=arduino
AVRDUDE_EXTRA_OPTS=-P${ARDUINO_PORT}

# The clock frequency, in Hz of the crystal
FREQUENCY=16000000

# Any extra, target-specific CFLAGS
CFLAGS_TARGET=

# target-specific sources
TARGET_SOURCES=