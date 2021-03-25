/******************************************************************************
* ACNodeReader Firmware - PN532 Interface                                     *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "pn532.h"
#include "log.h"
#include "tickcounter.h"
#include "i2c.h"

#include <stdbool.h>
#include <string.h>

// This is the 7-bit address, not the 8-bit address given in the docs
static const int pn532_address = 0x24;

// if the PN532 doesn't respond for 5 seconds, restart
static const unsigned long int wait_timeout = 5000;

enum
{
    STATE_INITIAL = 0,
    STATE_WAIT_STARTUP,
    STATE_WAIT_CONFIG_ACK,
    STATE_IDLE,
    STATE_RFON_WAIT_ACK,
    STATE_WAIT_CARDS_ACK,
    STATE_WAIT_CARDS,
};

static void pn532_send_ack(pn532_context_t* context);
static void pn532_state_transition(pn532_context_t* context, int newState);
static void pn532_state_hold(pn532_context_t* context);
static bool pn532_state_expired(pn532_context_t* context, unsigned long int timeout);
static void pn532_packet_init(pn532_context_t* context);
static bool pn532_i2c_recv(pn532_context_t* context, bool ackable);
static bool pn532_set_sam_config(pn532_context_t* context);
static void pn532_packet_finish(pn532_context_t* context);
static bool pn532_i2c_send(pn532_context_t* context);
static bool pn532_get_ack(pn532_context_t* context);
static void pn532_find_packet_start(pn532_context_t* context);
static bool pn532_rfon(pn532_context_t* context);

void pn532_init(pn532_context_t* context)
{
    DEBUG_LOG_LITERAL("Initialising PN532");
    memset(context, 0, sizeof(pn532_context_t));

    context->last_transition = tickcounter_get();
    context->current_state = STATE_INITIAL;
    context->last_different_state_time = tickcounter_get();
}

static void pn532_state_transition(pn532_context_t* context, int newState)
{
    DEBUG_LOG_LITERAL("State Transition");
    context->last_transition = tickcounter_get();

    if(context->current_state != newState)
    {
        context->last_different_state_time = context->last_transition;
    }

    context->current_state = newState;
}

static void pn532_state_hold(pn532_context_t* context)
{
    context->last_transition = tickcounter_get();
}

static bool pn532_state_expired(pn532_context_t* context, unsigned long int timeout)
{
    return compare_timer_values(tickcounter_get(), context->last_transition) >= timeout;
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

static bool pn532_i2c_send(pn532_context_t* context)
{
    DEBUG_LOG_BUFFER("I2C Sending", context->buffer, context->buffer_length);
    return i2c_write(pn532_address, context->buffer, context->buffer_length);
}

static bool pn532_i2c_recv(pn532_context_t* context, bool ackable)
{
    context->buffer_length = 0;
    uint8_t ready = 0;
    
    if(!i2c_start())
    {
        ERROR_LOG_LITERAL("Failed to start I2C");
        return false;
    }

    if(!i2c_address(pn532_address, true))
    {
        ERROR_LOG_LITERAL("Failed to address PN532");
        i2c_stop();
        return false;
    }
    i2c_recvdata(&ready, false);
    if(!(ready & 1))
    {
        //DEBUG_LOG_LITERAL("not Ready");
        i2c_stop();
        return false;
    }

    context->buffer_length = i2c_read_raw(context->buffer, 64);

    // TODO: checksum check
    if(ackable)
    {
        pn532_send_ack(context);
    }

    return true;
}

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

static bool pn532_set_sam_config(pn532_context_t* context)
{
    // The docs say this mode is the default, but it seems like it might not be
    // since without this, it doesn't ever read a card!
    pn532_packet_init(context);
    context->buffer[context->buffer_length++] = 0x14;
    context->buffer[context->buffer_length++] = 0x01; // normal mode
    context->buffer[context->buffer_length++] = 0x00; // no timeout (SAM - not used)
    context->buffer[context->buffer_length++] = 0x00; // no IRQ pin
    pn532_packet_finish(context);
    return pn532_i2c_send(context);   
}

static bool pn532_get_ack(pn532_context_t* context)
{
    pn532_i2c_recv(context, false);
    if(context->buffer_length == 0)
    {
        return false;
    }
    pn532_find_packet_start(context);
    if(context->buffer[context->packet_start+2] != 0 || context->buffer[context->packet_start+3] != 0xff)
    {
        return false;
    }
    
    return true;
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

static bool pn532_rfon(pn532_context_t* context)
{
    pn532_packet_init(context);
    context->buffer[context->buffer_length++] = 0x32;
    context->buffer[context->buffer_length++] = 0x01;
    context->buffer[context->buffer_length++] = 0x03;
    pn532_packet_finish(context);
    return pn532_i2c_send(context);
}

static bool  pn532_check_for_cards(pn532_context_t* context)
{
    pn532_packet_init(context);
    context->buffer[context->buffer_length++] = 0x60; // auto poll
    context->buffer[context->buffer_length++] = 0x03; // 3 polls
    context->buffer[context->buffer_length++] = 0x01; // 1*150ms period
    context->buffer[context->buffer_length++] = 0x00; // 106 kbps ISO/IEC14443 type A
    context->buffer[context->buffer_length++] = 0x01; // Passive 106 kbps ISO/IEC14443-4B
    context->buffer[context->buffer_length++] = 0x02; // FeliCa 212 kbps card
    pn532_packet_finish(context);
    return pn532_i2c_send(context);
}

void pn532_poll(pn532_context_t* context)
{
    switch(context->current_state)
    {
    case STATE_INITIAL:
        {
            // wait 500ms for the reader to start up
            if(pn532_state_expired(context, 500))
            {
                if(!i2c_polladdress(pn532_address))
                {
                    // wait for device to become present
                    pn532_state_hold(context);
                    DEBUG_LOG_LITERAL("PN532 not detected - waiting");
                    break;
                }
                // gratuitous ack in case the PN532 is waiting for us
                pn532_send_ack(context);

                // MOVE -> WAIT_STARTUP
                pn532_state_transition(context, STATE_WAIT_STARTUP);
            }
        } break;
    case STATE_WAIT_STARTUP:
        {
            // wait a further 100ms for the reader to be ready
            if(pn532_state_expired(context, 100))
            {
                if(!pn532_set_sam_config(context))
                {
                    ERROR_LOG_LITERAL("Error setting PN532 config");
                    pn532_state_transition(context, STATE_INITIAL);
                    break;
                }

                pn532_state_transition(context, STATE_WAIT_CONFIG_ACK);
            }
        } break;
    case STATE_WAIT_CONFIG_ACK:
        {
            if(pn532_state_expired(context, 10))
            {
                if(pn532_get_ack(context))
                {
                    // MOVE -> IDLE
                    DEBUG_LOG_LITERAL("Setup Complete");
                    pn532_state_transition(context, STATE_IDLE);
                }
                else
                {
                    // HOLD waiting for ACK
                    pn532_state_hold(context);

                    if((tickcounter_get() - context->last_different_state_time) > wait_timeout)
                    {
                        // We've waited over 5 seconds - something's wrong
                        pn532_state_transition(context, STATE_INITIAL);
                        ERROR_LOG_LITERAL("Timeout waiting for config ack");
                    }
                }
            }
        } break;
    case STATE_IDLE:
        {
            // retry 100ms after the last card probe
            if(pn532_state_expired(context, 100))
            {
                if(!pn532_rfon(context))
                {
                    ERROR_LOG_LITERAL("Error starting RF");
                    pn532_state_transition(context, STATE_INITIAL);
                    break;
                }
                pn532_state_transition(context, STATE_RFON_WAIT_ACK);
            }
        } break;
    case STATE_RFON_WAIT_ACK:
        {
            if(pn532_state_expired(context, 10))
            {
                if(pn532_get_ack(context))
                {
                    // poll for card
                    if(!pn532_check_for_cards(context))
                    {
                        ERROR_LOG_LITERAL("Error checking for cards");
                        pn532_state_transition(context, STATE_INITIAL);
                        break;
                    }
                    pn532_state_transition(context, STATE_WAIT_CARDS_ACK);
                }
                else
                {
                    // HOLD waiting for ACK
                    pn532_state_hold(context);

                    if((tickcounter_get() - context->last_different_state_time) > wait_timeout)
                    {
                        // We've waited over 10 seconds - something's wrong
                        pn532_state_transition(context, STATE_INITIAL);
                        ERROR_LOG_LITERAL("Timeout waiting for rfon ack");
                    }
                }
            }
        } break;
    case STATE_WAIT_CARDS_ACK:
        {
            if(pn532_state_expired(context, 10))
            {
                if(pn532_get_ack(context))
                {
                    pn532_state_transition(context, STATE_WAIT_CARDS);
                }
                else
                {
                    // HOLD waiting for ACK
                    pn532_state_hold(context);

                    if((tickcounter_get() - context->last_different_state_time) > 10000)
                    {
                        // We've waited over 5 seconds - something's wrong
                        pn532_state_transition(context, STATE_INITIAL);
                        ERROR_LOG_LITERAL("Timeout waiting for cards ack");
                    }
                }
            }
        } break;
    case STATE_WAIT_CARDS:
        {
            if(pn532_state_expired(context, 10))
            {
                if(pn532_i2c_recv(context, true))
                {
                    uint8_t cardCount = context->buffer[context->packet_start+6];

                    DEBUG_LOG_BUFFER("Cards Found", &cardCount, 1);

                    if(cardCount > 0)
                    {
                        uint8_t cardType = context->buffer[context->packet_start+7];
                        if(cardType == 0x10 || cardType == 0x20)
                        {
                            uint8_t uidLen = context->buffer[context->packet_start+13];
                            DEBUG_LOG_BUFFER("UID", context->buffer+context->packet_start+14, uidLen);
                            comms_send_card_message(&comms, uidLen, context->buffer+context->packet_start+14);

                        }
                        else if(cardType == 0x11)
                        {
                            // length is 8
                            DEBUG_LOG_BUFFER("UID", context->buffer+context->packet_start+12, 8);
                            comms_send_card_message(&comms, 8, context->buffer+context->packet_start+12);
                        }
                        else
                        {
                            ERROR_LOG_LITERAL("Unknown Card Type");
                            DEBUG_LOG_BUFFER("Unknown card type", &cardType, 1 );
                        }
                        INFO_LOG_LITERAL("Found a card");

                    }
                    else
                    {
                        comms_send_card_message(&comms, 0, NULL);                        
                    }

                    pn532_state_transition(context, STATE_IDLE);
                }
                else
                {
                    // hold waiting for data
                    pn532_state_hold(context);

                    if((tickcounter_get() - context->last_different_state_time) > wait_timeout)
                    {
                        // We've waited over 5 seconds - something's wrong
                        pn532_state_transition(context, STATE_INITIAL);
                        ERROR_LOG_LITERAL("Timeout waiting for cards");
                    }
                }
            }
        } break;
    }
}
