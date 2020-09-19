###############################################################################
# Makefile for ACNodeReader Firmware - Source file list                       #
#                                                                             #
# (c) 2019 London Hackspace                                                   #
# Released under a 3-clause BSD license. See included LICENSE file.           #
#                                                                             #
###############################################################################

SOURCES=src/main.c \
		src/lights.c \
		src/i2c.c \
		src/pn532.c \
		src/serial.c \
		src/log.c \
		src/commsprotocol.c \
		src/tickcounter.c \
		$(TARGET_SOURCES)