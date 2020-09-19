/******************************************************************************
* ACNodeReader Firmware - Rev1 Pins                                           *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef BOARD_PINS_H
#define BOARD_PINS_H

#ifndef TARGET_SPECIFIC_H
#error Please include target.h instead
#endif

#include <avr/io.h>

static const int LED_RED_PIN = 5;
#define LED_RED_PORT PORTD
#define LED_RED_DDR DDRD
static const int LED_GREEN_PIN = 6;
#define LED_GREEN_PORT PORTD
#define LED_GREEN_DDR DDRD
static const int LED_BLUE_PIN = 1;
#define LED_BLUE_PORT PORTB
#define LED_BLUE_DDR DDRB

#endif
