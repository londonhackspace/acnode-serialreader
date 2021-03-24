###############################################################################
# Makefile for ACNodeReader Firmware - Test rules                             #
#                                                                             #
# (c) 2020 London Hackspace                                                   #
# Released under a 3-clause BSD license. See included LICENSE file.           #
#                                                                             #
###############################################################################

build/tests/%.o : %.c
	mkdir -p `dirname $@`
	${CC} -c -ggdb -O0 -MMD $< -D__AVR__ -DCOMMS_HOST_MODE -DF_CPU=${FREQUENCY}UL -I`pwd`/tests -o $@

build/tests/%.o : %.cpp
	mkdir -p `dirname $@`
	${CXX} -c -ggdb -O0 -MMD $< -D__AVR__ -DCOMMS_HOST_MODE -DF_CPU=${FREQUENCY}UL -I`pwd`/tests -o $@

build/test_comms: build/tests/tests/test_comms.o build/tests/src/commsprotocol.o build/tests/src/tickcounter.o
	${CXX} -O2 $^ -o $@

test: build/test_comms
	build/test_comms