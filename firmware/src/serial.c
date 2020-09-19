/******************************************************************************
* ACNodeReader Firmware - Serial Port                                         *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
* (Yes, this one was repurposed from another of my own projects)              *
******************************************************************************/


#include "serial.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include <string.h>

#ifndef F_CPU
#error F_CPU must be defined for this to work
#endif

#include <avr/pgmspace.h>

#define SERIAL_BUFFER_SIZE 64
#define SERIAL_BUFFER_HIGH_MARK 58
char serialBuffer[SERIAL_BUFFER_SIZE];

// volatile since it's written to from an ISR
volatile short bufferpointer = 0;
short readbufferpointer = 0;
bool bufferfull = false;

int serial_countSerialBufferSize()
{
    if(readbufferpointer == bufferpointer)
    {
        return 0;
    }
    else if(readbufferpointer < bufferpointer)
    {
        return bufferpointer-readbufferpointer;
    }
    else
    {
        return (SERIAL_BUFFER_SIZE-readbufferpointer+bufferpointer);
    }
}

bool serial_data_available()
{
    return serial_countSerialBufferSize() > 0;
}

ISR(USART_RX_vect)
{
    // overflow? discard.
    if(serial_countSerialBufferSize() == SERIAL_BUFFER_SIZE)
    {
        static const char overflow[] PROGMEM =
            "Serial buffer overflow!!!!!!\n";
        serial_put_P((unsigned const char*)overflow, sizeof(overflow));
        return;
    }

    char c = UDR;
    serialBuffer[bufferpointer++] = c;
    //serial_putchar(c);

    if(bufferpointer >= SERIAL_BUFFER_SIZE)
    {
        bufferpointer = 0;
    }

    // nearly overflowing?
    if(serial_countSerialBufferSize() >= SERIAL_BUFFER_HIGH_MARK)
    {
        //send xoff
        serial_putchar(0x13);
        bufferfull = true;
    }
}

ISR(USART_UDRE_vect)
{

}

void serial_init(long baud)
{
    // store interrupt state
    unsigned char stored_sreg = SREG;
    cli();
    // set up baud rate
    const long ubrr = (F_CPU/(8*baud))-1;
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)(ubrr);

    //enable double clock rate
    UCSRA = (1 << U2X);

    //enable TX and RX (8 bit), and TX/RX interrupts
    UCSRB = (1 << RXCIE) | /*(1 << UDRIE) |*/ (1 << RXEN) | (1 << TXEN);
    // 8,N,1
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

    SREG = stored_sreg;
}

char serial_getchar()
{
    unsigned char stored_sreg = SREG;
    if(bufferpointer == readbufferpointer)
    {
        // enable interrupts so we get some characters
        sei();
        while(bufferpointer == readbufferpointer) wdt_reset();
    }

    cli();
    char result = serialBuffer[readbufferpointer++];
    SREG = stored_sreg;

    if(readbufferpointer >= SERIAL_BUFFER_SIZE)
    {
        readbufferpointer = 0;
    }

    // if we were in danger of filling up, but now have space, send XON
    if(serial_countSerialBufferSize() < SERIAL_BUFFER_HIGH_MARK && bufferfull)
    {
        //send xoff
        serial_putchar(0x11);
        bufferfull = false;
    }

    return result;
}

void serial_putchar(unsigned char c)
{
    // wait for any previous character to be sent
    while(!(UCSRA & (1 << UDRE))) wdt_reset();
    UDR = c;
}

unsigned int serial_get(unsigned char* buffer, unsigned int size)
{
    unsigned char stored_sreg = SREG;
    cli();
    unsigned int received = 0;

    if(bufferpointer < readbufferpointer)
    {
        memcpy(buffer, serialBuffer+readbufferpointer,SERIAL_BUFFER_SIZE-readbufferpointer);
        readbufferpointer = 0;
        received = SERIAL_BUFFER_SIZE-readbufferpointer;
    }

    if(readbufferpointer < bufferpointer)
    {
        memcpy(buffer+received, serialBuffer+readbufferpointer, bufferpointer-readbufferpointer);
        received += bufferpointer-readbufferpointer;
        readbufferpointer = bufferpointer;
    }

    SREG = stored_sreg;
    return received;
}

void serial_put(const unsigned char* buffer, unsigned int size)
{
    for(unsigned int i = 0; i < size; ++i)
    {
        wdt_reset();
        serial_putchar(buffer[i]);
    }
}

void serial_putz(const char* buffer)
{
    for(unsigned int i = 0; buffer[i] != '\0'; ++i)
    {
        wdt_reset();
        serial_putchar(buffer[i]);
    }
}

void serial_put_P(const unsigned char* buffer, unsigned int size)
{
    for(unsigned int i = 0; i < size; ++i)
    {
        char c = pgm_read_byte(buffer + i);
        serial_putchar(c);
        wdt_reset();
    }
}

void serial_putz_P(const char* buffer)
{
    while(1)
    {
        wdt_reset();
        char c = pgm_read_byte(buffer++);
        if(c == '\0')
        {
            break;
        }
        serial_putchar(c);
        wdt_reset();
    }
}