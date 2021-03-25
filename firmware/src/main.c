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

#ifdef HAS_DISPLAY
#include "ssd1306.h"
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
    DEBUG_LOG_LITERAL("Ah, you query my version?");
    comms_send_reader_version_response(comms, 0, 0, PSTR(LOG_STRINGIFY(BUILD_DATE)), PSTR(LOG_STRINGIFY(GIT_HASH)));
}

void comms_query_temperature_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    #ifdef HAS_LM75
    struct lm75_response data = lm75_read_temperature();
    comms_send_temperature_response(comms, data.high, data.low);
    #else
    #ifdef HAS_SI7060
    // this is only on the test hardware, so don't bother with fractions
    comms_send_temperature_response(comms, si7060_read_temperature(), 0);
    #else
    comms_send_temperature_response(comms, 0, 0);
    #endif
    #endif
}

void comms_reset_reader_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    wdt_enable(WDTO_15MS);
    // watchdog timer will reboot us
    while(1);
}

void comms_query_bootloader_status_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    comms_send_bootloader_status_response(comms, BOOTLOADER_STATUS_NOT_BOOTLOADER);
}

void comms_set_led_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    lights_set(payload[0], payload[1], payload[2]);
    //INFO_LOG_LITERAL("LEDs Updated");
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
    lights_set(255, 0, 0);

    i2c_init();

    INFO_LOG_LITERAL("Hi there...");
    
    // give the pn532 time to start up
    _delay_ms(50);
    wdt_reset();

    pn532_init(&pn532_ctx);

#ifdef HAS_DISPLAY
    ssd1306_init(&ssd1306, 0x3c);
#endif

    //pn532_get_firmware_version(&pn532_ctx);

    // enable the watchdog with a fairly generous 500ms timeout
    wdt_reset();
    wdt_enable(WDTO_500MS);

    while(1)
    {
        wdt_reset();
        pn532_poll(&pn532_ctx);
        comms_poll(&comms);

        #ifdef HAS_DISPLAY
        ssd1306_poll(&ssd1306);
        #endif
    }

    return 0;
}
