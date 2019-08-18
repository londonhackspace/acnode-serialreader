/******************************************************************************
* ACNodeReader Firmware - DebugBoard09 Pins                                   *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef BOARD_PINS_H
#define BOARD_PINS_H

#include <avr/io.h>

static const int LED_RED_PIN = 0;
#define LED_RED_PORT PORTC
#define LED_RED_DDR DDRC
static const int LED_GREEN_PIN = 1;
#define LED_GREEN_PORT PORTC
#define LED_GREEN_DDR DDRC
static const int LED_BLUE_PIN = 2;
#define LED_BLUE_PORT PORTC
#define LED_BLUE_DDR DDRC

#endif
