/******************************************************************************
* ACNodeReader Firmware                                                       *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "lights.h"
#include "i2c.h"
#include "serial.h"

#include <util/delay.h>
#include <avr/io.h>

int main()
{
    lights_init();
    i2c_init();
    serial_init(115200);
    serial_putz("Hello...\n");
    while(1)
    {
        lights_set(255, 0, 0);
        _delay_ms(500);
        lights_set(0, 255, 0);
        _delay_ms(500);
        lights_set(0, 0, 255);
        _delay_ms(500);
    }

    return 0;
}
