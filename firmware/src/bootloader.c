/******************************************************************************
* ACNodeReader Bootloader                                                     *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "target.h"
#include "commsprotocol.h"
#include "serial.h"
#include "tickcounter.h"
#include "lights.h"
#include "log.h"

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

comms_context_t comms;

void comms_reset_reader_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    wdt_enable(WDTO_15MS);
    // watchdog timer will reboot us
    while(1);
}

int main()
{
    // disable the watchdog timer so it doesn't interrupt us until we are ready
    MCUSR = 0;
    wdt_disable();

    cli();

    lights_init();

    // make interrupts work in bootloader space
    MCUCR = (1<<IVCE);
    MCUCR = (1<<IVSEL);

    serial_init(115200);
    comms_init(&comms);
    sei();
    comms_set_handlers(&comms, serial_put, serial_get);

    tickcounter_init();

    wdt_reset();
    wdt_enable(WDTO_500MS);

    lights_set(255,0,0);
    unsigned int start = tickcounter_get();
    while(tickcounter_get()-start < 1000)
    {
        wdt_reset();
        comms_poll(&comms);
    }

    //lights_set(255,127,0);

    // run main code
    wdt_disable();
    cli();

    // Put interrupts back in app land
    MCUCR = (1<<IVCE);
    MCUCR = 0;
    void (*go)() = 0x00;
    go();
}