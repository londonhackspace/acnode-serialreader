/******************************************************************************
* ACNodeReader Firmware - PN532 Interface                                     *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "pn532.h"
#include "i2c.h"

#include <string.h>

struct pn532_context_struct
{

};

void pn532_init(pn532_context_t* context)
{
    memset(context, 0, sizeof(pn532_context_t));
}

void pn532_close(pn532_context_t* context)
{

}

void pn532_poll(pn532_context_t* context)
{

}
