ACNodeReader Firmware
========

To build for the default platform (assuming avr-gcc is available)
```
make
```
(see? that was easy...)

There are currently 1 target(s) supported: 
* Arduino

There are three levels of debugability available:
* 0 - off
* 1 - logging
* 2 - debug build

Use, for example: `make TARGET=Arduino DEBUG=1`

`make clean` does exactly what you'd imagine

Mostly you probably just need to add files to sources.mk, which just exists to keep the main Makefile
more high level config based, and save you having to dig into it just to add a file.