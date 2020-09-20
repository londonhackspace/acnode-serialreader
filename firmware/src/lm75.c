/******************************************************************************
* ACNodeReader Firmware - LM75 Interface                                      *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "lm75.h"
#include "i2c.h"

// Address, assuming all address lines tied to ground
const static uint8_t lm75_address = 0x48;

int lm75_read_temperature()
{
	uint8_t data[2];
	i2c_writeread(lm75_address, 0x00, data, 2);

	return data[0];
}