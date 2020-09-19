/******************************************************************************
* ACNodeReader Firmware - SI7060 Interface                                    *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "si7060.h"
#include "i2c.h"
#include "target.h"

#include <avr/wdt.h>

#ifndef HAS_SI7060
#error Unsupported platform
#endif

const static uint8_t si7060_address = 0x30;

int si7060_read_temperature()
{
    // start a read
    uint8_t data[2] = { 0xc4, 0x04};
    i2c_write(si7060_address, data, 2);

    // now wait for it to do the thing
    do
    {
        i2c_writeread(si7060_address, 0xc4, data, 1);
        wdt_reset();
    } while((data[0] & 0x80) == 0x80);

    i2c_writeread(si7060_address, 0xc1, data, 1);
    i2c_writeread(si7060_address, 0xc2, data+1, 1);

    int rawValue = ((data[0] & 0x3f) << 8) + data[1];

    return 55 + (rawValue-16384)/160;
}