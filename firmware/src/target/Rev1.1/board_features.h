/******************************************************************************
* ACNodeReader Firmware - Rev1.1 (w/328pb) Features                             *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef BOARD_FEATURES_H
#define BOARD_FEATURES_H

#ifndef TARGET_SPECIFIC_H
#error Please include target.h instead
#endif

// SI7060 not available
// Display not available (not enough RAM!)
#define HAS_PWM_LEDS 1
#define LEDS_COMMON_ANODE 1
#define HAS_LM75 1

#endif
