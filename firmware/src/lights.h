/******************************************************************************
* ACNodeReader Firmware - Lights Control                                      *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef LIGHTS_H
#define LIGHTS_H

void lights_init();
void lights_set(int red, int green, int blue);

#endif
