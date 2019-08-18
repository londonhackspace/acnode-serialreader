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
#include "target.h"

#ifdef HAS_SI7060
#include "si7060.h"
#endif

#include <util/delay.h>
#include <avr/io.h>

pn532_context_t pn532_ctx;

int main()
{
    lights_init();
    i2c_init();
    serial_init(115200);
    INFO_LOG_LITERAL("Hi there...");

    pn532_init(&pn532_ctx);

    pn532_get_firmware_version(&pn532_ctx);

    while(1)
    {
        pn532_poll(&pn532_ctx);
        #ifdef HAS_SI7060
        uint8_t temperature __attribute__((unused)) = si7060_read_temperature();
        DEBUG_LOG_BUFFER("Temperature is ", &temperature, 1);
        #endif
    }

    return 0;
}
