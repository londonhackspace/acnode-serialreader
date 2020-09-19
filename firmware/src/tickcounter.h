/******************************************************************************
* ACNodeReader Firmware - 1ms timer                                           *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef TICKCOUNTER_H
#define TICKCOUNTER_H

unsigned long int tickcounter_get();
void tickcounter_init();

// returns a-b but accounts for overflows
unsigned long int compare_timer_values(unsigned long int a, unsigned long int b);

#endif
