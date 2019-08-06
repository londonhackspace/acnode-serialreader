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
    uint8_t buffer[64];
    int buffer_length;
    int packet_start;
} pn532_context_t;

// Pass in an uninitialised context to set it up
void pn532_init(pn532_context_t* context);

// execute any cleanup needed
void pn532_close(pn532_context_t* context);

// Handle any pending actions from the card reader
void pn532_poll(pn532_context_t* context);

// query the firmware version of the device
int pn532_get_firmware_version(pn532_context_t* context);

#endif
