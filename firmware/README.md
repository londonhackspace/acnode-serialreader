ACNodeReader Firmware
========

To build for the default platform (assuming avr-gcc is available)
```
make
```
(see? that was easy...)

There are currently 3 target(s) supported: 
* DebugBoard09 - Debug board (first hardware revision)
* Rev1 - V1.0 hardware (first in final form factor)
* Rev1-328 - V1.0 hardware but with ATmega328PB fitted

There are three levels of debugability available:
* 0 - off
* 1 - logging
* 2 - debug build

Use, for example: `make TARGET=Arduino DEBUG=1`

`make clean` does exactly what you'd imagine

Mostly you probably just need to add files to sources.mk, which just exists to keep the main Makefile
more high level config based, and save you having to dig into it just to add a file.

Flashing
----
The first time, you probably want to set the fuses first. This is because the factory default chip speed is too slow for the default avrdude upload speed, so we need to slow it down and set the fuses to the external clock.

use a USBASP programmer, for example:
`make fuses TARGET=Rev1`

use a USBASP programmer, for example:
`make flash TARGET=Rev1 DEBUG=2`
