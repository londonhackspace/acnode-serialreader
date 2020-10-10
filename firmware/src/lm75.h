/******************************************************************************
* ACNodeReader Firmware - LM75 Interface                                      *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef LM75_H
#define LM75_H

struct lm75_response
{
	unsigned char high;
	unsigned char low;
};

struct lm75_response lm75_read_temperature();

#endif