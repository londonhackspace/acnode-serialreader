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
#include <avr/boot.h>
#include <avr/eeprom.h>

comms_context_t comms;
bool bootloaderUsed = false;

void comms_query_reader_version_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    comms_send_reader_version_response(comms, 0, 0, PSTR(LOG_STRINGIFY(BUILD_DATE)), PSTR(LOG_STRINGIFY(GIT_HASH)));
}

void comms_reset_reader_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    wdt_enable(WDTO_15MS);
    // watchdog timer will reboot us
    while(1);
}

void comms_query_bootloader_status_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    if(boot_spm_busy() || !eeprom_is_ready())
    {
        comms_send_bootloader_status_response(comms, BOOTLOADER_STATUS_BUSY);
    }
    else
    {
        comms_send_bootloader_status_response(comms, BOOTLOADER_STATUS_IDLE);
    }
}

void comms_bootloader_write_data_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    bootloaderUsed = true;
    uint16_t address = (payload[0] << 8) + payload[1];
    size_t dataSize = payloadLength-2;

    for(size_t pos = 0; pos < dataSize; pos += 2)
    {
        uint16_t word = (payload[3+pos] << 8) + payload[2+pos];
        boot_page_fill(address+pos, word);
    }

    boot_page_erase (address);
    boot_spm_busy_wait ();
    boot_page_write(address);
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
    while(tickcounter_get()-start < 1000 || bootloaderUsed)
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