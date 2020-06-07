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
#include "commsprotocol.h"

#ifdef HAS_SI7060
#include "si7060.h"
#endif

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <avr/pgmspace.h>
#include <avr/wdt.h>

pn532_context_t pn532_ctx;

comms_context_t comms;

int main()
{
    // disable the watchdog timer so it doesn't interrupt us until we are ready
    MCUSR = 0;
    wdt_disable();

    // interrupts are probably disabled, but to be safe, disable them until we're ready for it
    cli();

    // set up comms early so logging works
    serial_init(115200);
    comms_init(&comms);
    sei();
    comms_set_handlers(&comms, serial_put, serial_get);
    
    lights_init();

    i2c_init();

    INFO_LOG_LITERAL("Hi there...");
    
    // give the pn532 time to start up
    _delay_ms(50);
    wdt_reset();

    pn532_init(&pn532_ctx);

    pn532_get_firmware_version(&pn532_ctx);

    

    // enable the watchdog with a fairly generous 500ms timeout
    wdt_reset();
    wdt_enable(WDTO_500MS);

    while(1)
    {
        wdt_reset();
        pn532_poll(&pn532_ctx);
        comms_poll(&comms);
    }

    return 0;
}
