/******************************************************************************
* ACNodeReader Firmware - Serial Port                                         *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
* (Yes, this one was repurposed from another of my own projects)              *
******************************************************************************/

#ifndef Z80_BOARD_SERIAL_H
#define Z80_BOARD_SERIAL_H

#include <avr/io.h>
#include <stdbool.h>

void serial_init(long baud);

// This code was originally written for ATMega8515
#ifdef __AVR_ATmega328P__
#define RXC RXC0
#define TXEN TXEN0
#define RXEN RXEN0
#define UBRRH UBRR0H
#define UBRRL UBRR0L
#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UCSRC UCSR0C
#define URSEL UCSZ01
#define UCSZ1 UCSZ01
#define UCSZ0 UCSZ00
#define UDR UDR0
#define UDRE UDRE0
#define MCUCSR MCUCR
#define U2X U2X0
#define RXCIE RXCIE0
#endif

static inline bool serial_data_available()
{
    return (UCSRA & (1 << RXC)) == (1 << RXC);
}

// blocking call - get next available serial character
char serial_getchar();

// send a single character
void serial_putchar(unsigned char c);

// takes a buffer and buffer size.
// Returns the actual amount of data received.
// Does not block if no data is available.
unsigned int serial_get(unsigned char* buffer, unsigned int size);

// send the contents of a buffer
void serial_put(const unsigned char* buffer, unsigned int size);
void serial_putz(const char* buffer);

// like serial_put but where buffer is in flash space
void serial_put_P(const unsigned char* buffer, unsigned int size);

#endif
