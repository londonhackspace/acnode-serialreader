/******************************************************************************
* ACNodeReader Firmware - Arduino Pins                                        *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef BOARD_PINS_H
#define BOARD_PINS_H

#ifndef TARGET_SPECIFIC_H
#error Please include target.h instead
#endif

#include <avr/io.h>

static const int LED_RED_PIN = 2;
#define LED_RED_PORT PORTB
#define LED_RED_DDR DDRB
static const int LED_GREEN_PIN = 1;
#define LED_GREEN_PORT PORTB
#define LED_GREEN_DDR DDRB
static const int LED_BLUE_PIN = 0;
#define LED_BLUE_PORT PORTB
#define LED_BLUE_DDR DDRB

#endif
