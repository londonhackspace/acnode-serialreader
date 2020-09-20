/******************************************************************************
* ACNodeReader Firmware - Lights Control                                      *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "lights.h"
#include "target.h"

#include <avr/io.h>

void lights_init()
{
    // LED pins are outputs
    LED_RED_DDR |= (1 << LED_RED_PIN);
    LED_GREEN_DDR |= (1 << LED_GREEN_PIN);
    LED_BLUE_DDR |= (1 << LED_BLUE_PIN);

    // zero off LEDs
    LED_RED_PORT &= ~(1 << LED_RED_PIN);
    LED_GREEN_PORT &= ~(1 << LED_GREEN_PIN);
    LED_BLUE_PORT &= ~(1 << LED_BLUE_PIN);

    #ifdef HAS_PWM_LEDS

    // fast PWM on both A and B outputs
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B = (1 << CS02); // prescaler of /256
    OCR0A = 0;
    OCR0B = 0;

    // 8-bit PWM with output on channel A
    TCCR1A = (1 << COM1A1) | (1 << WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS12); // prescaler of 256

    #endif    
}

void lights_set(int red, int green, int blue)
{
    #ifdef LEDS_COMMON_ANODE
    red = 255-red;
    green = 255-green;
    blue = 255-blue;
    #endif

    #ifdef HAS_PWM_LEDS
    OCR0B = red;
    OCR0A = green;
    OCR1AL = blue;
    #else
    if(red)
    {
        LED_RED_PORT |= (1 << LED_RED_PIN);
    }
    else
    {
        LED_RED_PORT &= ~(1 << LED_RED_PIN);
    }

    if(green)
    {
        LED_GREEN_PORT |= (1 << LED_GREEN_PIN);
    }
    else
    {
        LED_GREEN_PORT &= ~(1 << LED_GREEN_PIN);
    }

    if(blue)
    {
        LED_BLUE_PORT |= (1 << LED_BLUE_PIN);
    }
    else 
    {
        LED_BLUE_PORT &= ~(1 << LED_BLUE_PIN);
    }
    #endif
}
