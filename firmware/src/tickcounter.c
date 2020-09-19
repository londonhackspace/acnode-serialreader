/******************************************************************************
* ACNodeReader Firmware - 1ms timer                                           *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/
#include "tickcounter.h"

#include <avr/io.h>
#include <limits.h>
#include <util/atomic.h>

static unsigned long int tickcounter = 0;

unsigned long int tickcounter_get()
{
    unsigned long int local_tickcounter;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        local_tickcounter = tickcounter;
    }
    return local_tickcounter;
}

void lights_set(int,int,int);

ISR(TIMER2_COMPA_vect)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        ++tickcounter;
    }
}

void tickcounter_init()
{
    // set to clear on match, without output to a pin
    TCCR2A = (1 << WGM21);

    // set /64 prescaler
    TCCR2B = (1 << CS22);

    // Set compare register to fire once every 1ms
    OCR2A = F_CPU/64000;

    // enable interrupts
    TIMSK2 = (1 << OCIE2A);
}

unsigned long int compare_timer_values(unsigned long int a, unsigned long int b)
{
    unsigned long int retval = 0;
    if(b > a)
    {
        retval = ULONG_MAX-b;
        b = 0;
    }
    return retval+(a-b);
}