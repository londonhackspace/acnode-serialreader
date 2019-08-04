/******************************************************************************
* ACNodeReader Firmware - PN532 Interface                                     *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef PN532_H
#define PN532_H

static const int pn532_address = 0x48;

typedef struct pn532_context_struct pn532_context_t;

// Pass in an uninitialised context to set it up
void pn532_init(pn532_context_t* context);

// execute any cleanup needed
void pn532_close(pn532_context_t* context);

// Handle any pending actions from the card reader
void pn532_poll(pn532_context_t* context);



#endif
