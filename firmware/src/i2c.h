/******************************************************************************
* ACNodeReader Firmware - I2C Control                                         *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
* (Yes, this one was repurposed from another of my own projects)              *
******************************************************************************/

#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>

void i2c_init();

int i2c_read(uint8_t address, uint8_t* buffer, uint8_t length);

uint8_t i2c_readbyte(uint8_t addr);

bool i2c_write(uint8_t address, uint8_t* data, uint8_t length);

// used when you need to send a byte then read the response
int i2c_writeread(uint8_t address, uint8_t data, uint8_t* buffer, uint8_t length);

// check if an address responds
bool i2c_polladdress(uint8_t addr);

/////////////////////
// Low level commands
// PN532 needs some fairly careful handling
/////////////////////

// start communications
bool i2c_start();

// set the address
bool i2c_address(uint8_t address, bool read);

// raw read, assumes address already set and started
int i2c_read_raw(uint8_t* buffer, uint8_t length);

// read a single byte without resetting state
bool i2c_recvdata(uint8_t* data, bool last);

// force an i2c stop
void i2c_stop();

#endif
