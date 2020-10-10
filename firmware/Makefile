###############################################################################
# Makefile for ACNodeReader Firmware                                          #
#                                                                             #
# (c) 2019 London Hackspace                                                   #
# Released under a 3-clause BSD license. See included LICENSE file.           #
#                                                                             #
###############################################################################

###############################################################################
# Settings
###############################################################################
# TARGET sets the hardware target. It must be one of the following:
# * Arduino - Atmega328p based hardware, for intiial development and testing
# * DebugBoard09 - Debug Board v0.9 hardware

# DEBUG sets the debuggyness of the firmware build.
# Note: Not all targets may have the resources for all levels
# 0 - no debug
# 1 - Production build, but with logging
# 2 - Full debug build

# Set the default in case no one specifies TARGET
ifeq ($(TARGET),)
TARGET=Rev1
endif

# default to no debug
ifeq ($(DEBUG),)
DEBUG=0
endif

PROJECT=ACNodeReader

###############################################################################
# Set up the base variables
###############################################################################

# define a stringified name of debug levels
ifeq ($(DEBUG),0)
DEBUG_STRING=
DEBUG_STRING_SET=1
endif
ifeq ($(DEBUG),1)
DEBUG_STRING=logging
DEBUG_STRING_SET=1
endif
ifeq ($(DEBUG),2)
DEBUG_STRING=debug
DEBUG_STRING_SET=1
endif

ifeq ($(DEBUG_STRING_SET),)
$(error Invalid debug level $(DEBUG))
endif


# used for building the test engine
CC ?= gcc
CXX ?= g++

CROSS_CC=avr-gcc
CROSS_AS=avr-as
OBJDUMP=avr-objdump
OBJCOPY=avr-objcopy

GITHASH=$(shell git rev-parse HEAD)
BUILDDATE=$(shell date)

# check the target file exists, to prevent weird errors later
ifeq (,$(wildcard targets/$(TARGET).mk))
$(error Unknown TARGET or target file not found. Check targets/$(TARGET).mk exists.)
endif

# create the all target up here so it's definitely the first
all: full

# include target-specific variables
include targets/$(TARGET).mk

# Set some variables

DEFINES=\
	-DF_CPU=${FREQUENCY}UL \
	-DDEBUG_STRING=$(DEBUG_STRING) \
	-DDEBUG_LEVEL=$(DEBUG) \
	-DGIT_HASH=$(GITHASH) \
	-DBUILD_DATE="$(BUILDDATE)"

CFLAGS=-mmcu=${MCU} $(DEFINES) -ggdb -O2 -I$(CURDIR)/src/include -Wall -Werror \
		-Wl,--gc-sections -flto -I$(CURDIR)/build $(CFLAGS_TARGET) \
		-I$(CURDIR)/src/target/$(TARGET)

BOOTLOADER_CFLAGS=$(CFLAGS) -Wl,--section-start=.text=$(BOOTSTART)

# build the output filename
OUTPUT_NAME=$(PROJECT)-$(TARGET)
BOOTLOADER_NAME=$(PROJECT)-bootloader-$(TARGET)

ifneq (,$(DEBUG_STRING))
OUTPUT_NAME:=$(OUTPUT_NAME)-$(DEBUG_STRING)
endif

###############################################################################
# Output what we're going to build
###############################################################################
$(info )
$(info ACNodeReader Maker)
$(info -----------)
$(info Target: $(TARGET))
$(info Microcontroller: $(MCU))
$(info Clock Frequency: $(FREQUENCY) Hz)
ifneq (,$(DEBUG_STRING))
$(info Debug Level: $(DEBUG_STRING))
else
$(info Debug Level: none)
endif
$(info Output Name: $(OUTPUT_NAME))
$(info Output will be built to build/$(OUTPUT_NAME).hex)
$(info -----------)
$(info )

###############################################################################
# Now get on with it!
###############################################################################

# include the sources file
include sources.mk
include tests.mk

OBJECTS_C = $(SOURCES:%=build/$(OUTPUT_NAME)/%)
OBJECTS = $(OBJECTS_C:.c=.o)
DEP = $(OBJECTS:%.o=%.d)

BL_OBJECTS_C = $(BOOTLOADER_SOURCES:%=build/$(BOOTLOADER_NAME)/%)
BLOBJECTS = $(BL_OBJECTS_C:.c=.o)
BLDEP = $(OBJECTS:%.o=%.d)

full: build/$(OUTPUT_NAME).hex

bootloader: build/$(BOOTLOADER_NAME).hex

-include $(DEP)
-include $(BLDEP)

build/$(OUTPUT_NAME)/%.o : %.c
	mkdir -p `dirname $@`
	${CROSS_CC} -c ${CFLAGS} -MMD $< -o $@

build/$(OUTPUT_NAME).elf: ${OBJECTS}
	${CROSS_CC} ${CFLAGS} -Wl,-Map,$(@:.elf=.map) $^ -lm -o $@
	avr-size --format=avr --mcu=${MCU} $@ | tee build/$(OUTPUT_NAME)_size.txt

build/$(BOOTLOADER_NAME)/%.o : %.c
	mkdir -p `dirname $@`
	${CROSS_CC} -c ${BOOTLOADER_CFLAGS} -MMD $< -o $@

build/$(BOOTLOADER_NAME).elf: ${BLOBJECTS}
	${CROSS_CC} ${BOOTLOADER_CFLAGS} -Wl,-Map,$(@:.elf=.map) $^ -lm -o $@
	avr-size --format=avr --mcu=${MCU} $@ | tee build/$(BOOTLOADER_NAME)_size.txt

%.hex : %.elf
	${OBJCOPY} -j .text -j .data -O ihex $< $@
	${OBJCOPY} -j .eeprom -O ihex $< ${@:%.hex=%-eeprom.hex}

clean:
	rm -f $(OBJECTS) $(DEP) $(BLOBJECTS) $(BLDEP)
	rm -f build/$(OUTPUT_NAME).elf build/$(BOOTLOADER_NAME).elf
	rm -f build/$(OUTPUT_NAME).hex  build/$(BOOTLOADER_NAME).hex
	rm -f build/$(OUTPUT_NAME)-eeprom.hex  build/$(BOOTLOADER_NAME)-eeprom.hex
	rm -f build/$(OUTPUT_NAME)_size.txt  build/$(BOOTLOADER_NAME)_size.txt
	rm -f build/$(OUTPUT_NAME).map  build/$(BOOTLOADER_NAME).map
	# the directory should now be empty, so no need for -f
	if [ -d build ]; then rm -r build; fi

flash : build/$(OUTPUT_NAME).hex build/$(BOOTLOADER_NAME).hex
	avrdude -p ${AVRDUDE_TARGET} -c $(AVRDUDE_PROGRAMMER) -U flash:w:build/$(BOOTLOADER_NAME).hex $(AVRDUDE_EXTRA_OPTS)
	avrdude -p ${AVRDUDE_TARGET} -c $(AVRDUDE_PROGRAMMER) -U flash:w:build/$(OUTPUT_NAME).hex $(AVRDUDE_EXTRA_OPTS) -D

nobootflash : build/$(OUTPUT_NAME).hex build/$(BOOTLOADER_NAME).hex
	avrdude -p ${AVRDUDE_TARGET} -c $(AVRDUDE_PROGRAMMER) -U flash:w:build/$(OUTPUT_NAME).hex $(AVRDUDE_EXTRA_OPTS)

bootloader_flash : build/$(BOOTLOADER_NAME).hex
	avrdude -p ${AVRDUDE_TARGET} -c $(AVRDUDE_PROGRAMMER) -U flash:w:$< $(AVRDUDE_EXTRA_OPTS)
