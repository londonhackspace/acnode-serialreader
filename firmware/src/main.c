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
#include "pn532.h"
#include "log.h"

#include <util/delay.h>
#include <avr/io.h>

pn532_context_t pn532_ctx;

void temp()
{
    i2c_init();
    i2c_write(0x24, (uint8_t*)"\0\0\0\0\0",5);

    while(1);
}

int main()
{
    //temp();

    lights_init();
    i2c_init();
    serial_init(115200);
    INFO_LOG_LITERAL("Hi there...");

    pn532_init(&pn532_ctx);

    pn532_get_firmware_version(&pn532_ctx);

    while(1)
    {
        lights_set(255, 0, 0);
        _delay_ms(500);
        lights_set(0, 255, 0);
        _delay_ms(500);
        lights_set(0, 0, 255);
        _delay_ms(500);
        pn532_poll(&pn532_ctx);
    }

    return 0;
}
