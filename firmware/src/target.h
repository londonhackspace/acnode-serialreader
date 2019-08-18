/******************************************************************************
* ACNodeReader Firmware - Target-specific stuff                               *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
* (Yes, this one was repurposed from another of my own projects)              *
******************************************************************************/

#ifndef TARGET_SPECIFIC_H
#define TARGET_SPECIFIC_H

#include <board_pins.h>
#include <board_features.h>

#ifndef LED_RED_PORT
#error Please define LED_RED_PORT
#endif

#ifndef LED_GREEN_PORT
#error Please define LED_GREEN_PORT
#endif

#ifndef LED_BLUE_PORT
#error Please define LED_BLUE_PORT
#endif

#ifndef LED_RED_DDR
#error Please define LED_RED_DDR
#endif

#ifndef LED_GREEN_DDR
#error Please define LED_GREEN_DDR
#endif

#ifndef LED_BLUE_DDR
#error Please define LED_BLUE_DDR
#endif

#endif
