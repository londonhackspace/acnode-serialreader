/******************************************************************************
* ACNodeReader Firmware - I2C Control                                         *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
* (Yes, this one was repurposed from another of my own projects)              *
******************************************************************************/

#include "i2c.h"
#include "log.h"
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include <stdbool.h>

#define I2C_PORT PORTC
#define I2C_PIN_SDA 4
#define I2C_PIN_SCL 5

void i2c_init()
{
    // enable pullups on I2C pins
    I2C_PORT |= (1 << I2C_PIN_SDA) | (1 << I2C_PIN_SCL);

    // set bitrate scaler
    TWBR = 18;
    TWSR = 1; // prescaler 4
    // -> 100KHz clock

    // enable TWI
    TWCR = (1 << TWEN);
}

// returns true on success
bool i2c_start()
{
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    // wait twint
    while (!(TWCR & (1<<TWINT))) wdt_reset();
    // check twi status
    return ((TWSR & 0xF8) == 0x08) || ((TWSR & 0xF8) == 0x10);
}

void i2c_stop()
{
    //DEBUG_LOG_LITERAL("Sending i2c Stop");
    TWCR = (1<<TWINT)| (1<<TWEN) | (1<<TWSTO);
}

bool i2c_address(uint8_t address, bool read)
{
    TWDR = address << 1 | (read ? 1 : 0);
    TWCR = (1<<TWINT) | (1<<TWEN);
    // wait twint
    while (!(TWCR & (1<<TWINT))) wdt_reset();
    // check twi status
    return ((TWSR & 0xF8) == 0x18) || ((TWSR & 0xF8) == 0x40);
}

static bool i2c_senddata(uint8_t data)
{
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    // wait twint
    while (!(TWCR & (1<<TWINT))) wdt_reset();
    return ((TWSR & 0xF8) == 0x28);
}

bool i2c_recvdata(uint8_t* data, bool last)
{
    TWCR = (1<<TWINT) | (last ? 0 : (1 << TWEA)) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    // Disable interupts, since they seem to corrupt the register access
    // (or maybe it just fixes this code by timing but...)
    // This works around TWSR reading as 0 sometimes
    unsigned char stored_sreg = SREG;
    cli();

    if((!last && (TWSR & 0xF8) == 0x50) ||
        (last && (TWSR & 0xF8) == 0x58))
    {
        *data = TWDR;
        SREG = stored_sreg;
        return true;
    }
    SREG = stored_sreg;
    return false;
}

int i2c_read_raw(uint8_t* buffer, uint8_t length)
{
    uint8_t counter = 0;

    while(length)
    {
        wdt_reset();
        //DEBUG_LOG_VAL("Receiving remaining", length);
        if(!i2c_recvdata(buffer, length == 1))
        {
            i2c_stop();
            return counter;
        }

        --length;
        ++counter;
        ++buffer;
    }

    i2c_stop();

    return counter;
}

int i2c_read(uint8_t address, uint8_t* buffer, uint8_t length)
{
    if(!i2c_start()) { return 0; }
    if(!i2c_address(address, true))
    {
        i2c_stop();
        return 0;
    }
    
    return i2c_read_raw(buffer, length);
}

bool i2c_polladdress(uint8_t addr)
{
    if(!i2c_start())
    {
        return false;
    }

    bool retval = i2c_address(addr, false);

    i2c_stop();

    return retval;
}

void i2c_write(uint8_t address, uint8_t* data, uint8_t length)
{
    if(!i2c_start()) { return; }
    //send address + W
    int tries = 0;
    while(!i2c_address(address, false) && tries++ <5)
    {
        wdt_reset();
        WARN_LOG_LITERAL("Failed to address device - retrying");
        i2c_stop();
        i2c_start();
    }
    if(tries >= 5)
    {
        ERROR_LOG_LITERAL("Giving up");
        return;
    }
    // send data
    while(length)
    {
        wdt_reset();
        if(!i2c_senddata(data[0]))
        {
            ERROR_LOG_LITERAL("Failed to send data");
            i2c_stop(); return;
        }
        --length;
        ++data;
    }
    // send stop
    i2c_stop();
}

int i2c_writeread(uint8_t address, uint8_t data, uint8_t* buffer, uint8_t length)
{
    if(!i2c_start()) { return 0; }
    //send address + W
    if(!i2c_address(address, false))
    {
        ERROR_LOG_LITERAL("Failed to address device");
        i2c_stop();
        return 0;
    }
    // send byte
    if(!i2c_senddata(data))
    {
        ERROR_LOG_LITERAL("Failed to send byte");
        i2c_stop();
        return 0;
    }
    // restart in read mode
    i2c_start();
    if(!i2c_address(address, true))
    {
        ERROR_LOG_LITERAL("Failed to address device");
        i2c_stop();
        return 0;
    }
    // now receive
    return i2c_read_raw(buffer, length);
}

uint8_t i2c_readbyte(uint8_t address)
{
    if(!i2c_start())
    {
        ERROR_LOG_LITERAL("Failed to start");
        return 0;
    }

    if(!i2c_address(address, true))
    {
        ERROR_LOG_LITERAL("Failed to address device");
        i2c_stop();
        return 0;
    }
    uint8_t b;
    i2c_read_raw(&b, 1);
    return b;
}
