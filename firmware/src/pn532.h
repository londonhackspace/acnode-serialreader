/******************************************************************************
* ACNodeReader Firmware - PN532 Interface                                     *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef PN532_H
#define PN532_H

#include <stdint.h>

static const int pn532_buffer_length = 64;

typedef struct
{
    // scratch space
    uint8_t buffer[64];
    int buffer_length;
    int packet_start;

    // state
    int current_state;
    unsigned long int last_transition;

    unsigned long int last_different_state_time;
} pn532_context_t;

// Pass in an uninitialised context to set it up
void pn532_init(pn532_context_t* context);

void pn532_poll(pn532_context_t* context);

#endif
