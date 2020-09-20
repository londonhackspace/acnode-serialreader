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
#include "tickcounter.h"

#ifdef HAS_SI7060
#include "si7060.h"
#endif

#ifdef HAS_LM75
#include "lm75.h"
#endif

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <avr/pgmspace.h>
#include <avr/wdt.h>

pn532_context_t pn532_ctx;

comms_context_t comms;

void comms_query_reader_version_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    comms_send_reader_version_response(comms, 0, 0, PSTR(LOG_STRINGIFY(BUILD_DATE)), PSTR(LOG_STRINGIFY(GIT_HASH)));
}

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

    tickcounter_init();
    
    lights_init();
    lights_set(128,0, 128);

    i2c_init();

    INFO_LOG_LITERAL("Hi there...");
    
    // give the pn532 time to start up
    _delay_ms(50);
    wdt_reset();

    pn532_init(&pn532_ctx);

    #ifdef HAS_LM75
    unsigned char temperature = lm75_read_temperature();
    DEBUG_LOG_BUFFER("Temperature: ", &temperature, 1);
    #endif

    //pn532_get_firmware_version(&pn532_ctx);

    // enable the watchdog with a fairly generous 500ms timeout
    wdt_reset();
    wdt_enable(WDTO_500MS);

    int val = 0;
    int chan = 0;
    unsigned long int lastupdate = tickcounter_get();

    while(1)
    {
        wdt_reset();
        pn532_poll(&pn532_ctx);
        comms_poll(&comms);

        if((tickcounter_get() - lastupdate) >= 12)
        {
            lastupdate = tickcounter_get();
            if(val == 255)
            {
                val = 0;
                ++ chan;
                if(chan > 2)
                {
                    chan = 0;
                }
            }
            else
            {
                ++val;
            }

            unsigned int red = 0;
            unsigned int blue = 0;
            unsigned int green = 0;

            if(chan == 0)
            {
                red = val;
            }
            else if(chan == 1)
            {
                green = val;
            }
            else
            {
                blue = val;
            }
            lights_set(red,green,blue);
        }
    }

    return 0;
}
