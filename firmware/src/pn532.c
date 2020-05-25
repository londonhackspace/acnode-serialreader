/******************************************************************************
* ACNodeReader Firmware - PN532 Interface                                     *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "pn532.h"
#include "i2c.h"
#include "log.h"
#include "lights.h"

#include <util/delay.h>
#include <string.h>

// This is the 7-bit address, not the 8-bit address given in the docs
static const int pn532_address = 0x24;

static void pn532_set_sam_config(pn532_context_t* context);

static void pn532_send_ack(pn532_context_t* context)
{
    // theoretically, we shouldn't need to add preamble
    // since the spec seems to imply it's optional.
    // Including some anyway though since it doesn't hurt, and
    // might make things a bit more reliable
    context->buffer[0] = 0x00;
    context->buffer[1] = 0x00;
    context->buffer[2] = 0xff;
    context->buffer[3] = 0x00;
    context->buffer[4] = 0xff;
    i2c_write(pn532_address, context->buffer, 5);
}

void pn532_init(pn532_context_t* context)
{
    DEBUG_LOG_LITERAL("Initialising PN532");
    memset(context, 0, sizeof(pn532_context_t));

    // gratuitous ack in case the PN532 is waiting for us
    pn532_send_ack(context);

    // wait for the pn532 to power up
    _delay_ms(100);

    pn532_set_sam_config(context);

}

static void pn532_i2c_recv(pn532_context_t* context, bool ackable, int timeout)
{
    context->buffer_length = 0;
    uint8_t ready = 0;
    int counter = 0;
    while(!(ready & 1))
    {
        if(!i2c_start())
        {
            ERROR_LOG_LITERAL("Failed to start I2C");
            return;
        }
        //DEBUG_LOG_LITERAL("Checking for ready");

        if(!i2c_address(pn532_address, true))
        {
            ERROR_LOG_LITERAL("Failed to address PN532");
            return;
        }
        i2c_recvdata(&ready, false);
        if(!(ready & 1))
        {
            //DEBUG_LOG_LITERAL("Not Ready");
            i2c_stop();
            ++counter;
            _delay_ms(1);
            if(counter > timeout)
            {
                DEBUG_LOG_LITERAL("Timed out");
                return;
            }
        }
    }
    context->buffer_length = i2c_read_raw(context->buffer, 64);

    // TODO: checksum check
    if(ackable)
    {
        pn532_send_ack(context);
    }
}

static void pn532_find_packet_start(pn532_context_t* context)
{
    context->packet_start = 1;
    while(context->packet_start < (pn532_buffer_length-1))
    {
        if(context->buffer[context->packet_start] == 0x00 && 
                context->buffer[context->packet_start+1] == 0xff)
        {
            return;
        }
        ++context->packet_start;
    }
}

static void pn532_i2c_send(pn532_context_t* context)
{
    DEBUG_LOG_BUFFER("I2C Sending", context->buffer, context->buffer_length);
    i2c_write(pn532_address, context->buffer, context->buffer_length);
    // get ack
    //DEBUG_LOG_LITERAL("Sent. Attempting to get ACK");
    // It seems the PN532 needs a bit of time to respond
    _delay_us(500);
    pn532_i2c_recv(context, false, 1000);
    if(context->buffer_length == 0)
    {
        ERROR_LOG_LITERAL("Failed to get ack");
        return;
    }
    pn532_find_packet_start(context);
    if(context->buffer[context->packet_start+2] != 0 || context->buffer[context->packet_start+3] != 0xff)
    {
        ERROR_LOG_LITERAL("Received something not an ack");
    }
    else
    {
        //DEBUG_LOG_LITERAL("Got ack");
    }
}

static void pn532_packet_init(pn532_context_t* context)
{
    // theoretically, we shouldn't need to add preamble
    // since the spec seems to imply it's optional.
    // Including some anyway though since it doesn't hurt, and
    // might make things a bit more reliable
    context->buffer[0] = 0x00;
    context->buffer[1] = 0x00;
    context->buffer[2] = 0xff;
    // 3,4 are length and length checksum - ignore for now
    context->buffer[5] = 0xd4;

    context->buffer_length = 6;
    context->packet_start = 1;
}

static void pn532_packet_finish(pn532_context_t* context)
{
    // length, length checksum
    context->buffer[3] = context->buffer_length-5;
    context->buffer[4] = (0xff-context->buffer[3])+1;

    uint8_t sum = 0;
    for(int i = (4+context->packet_start); i < context->buffer_length; ++i)
    {
        sum += context->buffer[i];
    }
    context->buffer[context->buffer_length++] = (0xff-sum)+1;
    // Postamble because, well, see the notes on preamble
    context->buffer[context->buffer_length++] = 0x00;
}

int pn532_get_firmware_version(pn532_context_t* context)
{
    pn532_packet_init(context);
    context->buffer[context->buffer_length++] = 0x02;
    pn532_packet_finish(context);
    pn532_i2c_send(context);
    DEBUG_LOG_LITERAL("Sent firmware version query");
    // now receive the response
    pn532_i2c_recv(context, true, 1000);
    DEBUG_LOG_LITERAL("Probably got firmware version response");
    pn532_find_packet_start(context);
    DEBUG_LOG_BUFFER("PN532 Firmware Version", context->buffer+context->packet_start+7, 2);
    return 0;
}

static void pn532_set_sam_config(pn532_context_t* context)
{
    // The docs say this mode is the default, but it seems like it might not be
    // since without this, it doesn't ever read a card!
    pn532_packet_init(context);
    context->buffer[context->buffer_length++] = 0x14;
    context->buffer[context->buffer_length++] = 0x01; // normal mode
    context->buffer[context->buffer_length++] = 0x00; // no timeout (SAM - not used)
    context->buffer[context->buffer_length++] = 0x00; // no IRQ pin
    pn532_packet_finish(context);
    pn532_i2c_send(context);   
}

void pn532_close(pn532_context_t* context)
{

}

static void pn532_rfon(pn532_context_t* context)
{
    pn532_packet_init(context);
    context->buffer[context->buffer_length++] = 0x32;
    context->buffer[context->buffer_length++] = 0x01;
    context->buffer[context->buffer_length++] = 0x03;
    pn532_packet_finish(context);
    pn532_i2c_send(context);
}

// This uses the auto poll mechanism rather than the "read id" mechanism used
// by the arduino library
void pn532_poll(pn532_context_t* context)
{
    pn532_rfon(context);

    pn532_packet_init(context);
    context->buffer[context->buffer_length++] = 0x60; // auto poll
    context->buffer[context->buffer_length++] = 0x03; // 3 polls
    context->buffer[context->buffer_length++] = 0x01; // 1*150ms period
    context->buffer[context->buffer_length++] = 0x00; // 106 kbps ISO/IEC14443 type A
    context->buffer[context->buffer_length++] = 0x01; // Passive 106 kbps ISO/IEC14443-4B
    context->buffer[context->buffer_length++] = 0x02; // FeliCa 212 kbps card
    pn532_packet_finish(context);
    pn532_i2c_send(context);
    pn532_i2c_recv(context, true, 5000);
    pn532_find_packet_start(context);
    
    uint8_t cardCount = context->buffer[context->packet_start+6];

    DEBUG_LOG_BUFFER("Cards Found", &cardCount, 1);

    if(cardCount > 0)
    {
        uint8_t cardType = context->buffer[context->packet_start+7];
        uint8_t idLength __attribute__((unused)) = 0;
        uint8_t idOffset __attribute__((unused)) = 0;
        switch(cardType & 0x0f)
        {
            case 0x0:
                DEBUG_LOG_LITERAL("106 kbps ISO/IEC14443-4A");
                idLength = context->buffer[context->packet_start+13];
                idOffset = context->packet_start+14;
                lights_set(0, 255, 0);
                break;
            case 0x1:
                DEBUG_LOG_LITERAL("passive 212 kbps");
                idLength = 8;
                idOffset = context->packet_start+12;
                lights_set(0, 0, 255);
                break;
            case 0x2:
                DEBUG_LOG_LITERAL("passive 424 kbps");
                idLength = 8;
                idOffset = context->packet_start+12;
                lights_set(0, 0, 255);
                break;
            default:
                DEBUG_LOG_LITERAL("Unknown Card Type");
                lights_set(255, 0, 0);
                break;
        };
        DEBUG_LOG_BUFFER("Card type ", &cardType, 1);
        DEBUG_LOG_BUFFER("Data Length ", context->buffer+context->packet_start+8, 1);
        DEBUG_LOG_BUFFER("ID Length ", &idLength, 1);
        DEBUG_LOG_BUFFER("Card ID ", context->buffer+idOffset, idLength);
    }
    else
    {
        lights_set(255, 0, 0);
    }
}

// This behaves much like the Arduino library
/*void pn532_poll(pn532_context_t* context)
{
    //pn532_rfon(context);

    pn532_packet_init(context);
    context->buffer[context->buffer_length++] = 0x4a;
    context->buffer[context->buffer_length++] = 0x01;
    context->buffer[context->buffer_length++] = 0x00;
    pn532_packet_finish(context);
    pn532_i2c_send(context);
    pn532_i2c_recv(context, true, 1000);
    pn532_find_packet_start(context);

    uint8_t cardCount = context->buffer[context->packet_start+6];

    DEBUG_LOG_BUFFER("Cards Found", &cardCount, 1);
}*/
