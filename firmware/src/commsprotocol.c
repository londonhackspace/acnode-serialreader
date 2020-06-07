/******************************************************************************
* ACNodeReader Firmware - Comms Protocol                                      *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "commsprotocol.h"

#include <string.h>

#ifdef __AVR__
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#endif

static const unsigned int max_tx_payload = COMMS_TXBUFFER_SIZE - 5;

enum comms_state
{
	STATE_IDLE = 0,
	STATE_WAIT_ACK = 1
};

enum message_nums
{
	MSG_LOG = 0x82,
};

void comms_init(comms_context_t* comms)
{
	memset(comms, 0, sizeof(comms_context_t));
}

void comms_set_handlers(comms_context_t* comms, sendfunc send, recvfunc receive)
{
	comms->send = send;
	comms->receive = receive;
}

static void process_receive(comms_context_t* comms)
{
	if(comms->buffer_level < COMMS_RXBUFFER_SIZE)
	{
		unsigned int got = comms->receive(comms->rxbuffer+comms->buffer_level, COMMS_RXBUFFER_SIZE-comms->buffer_level);
		if(got > 0)
		{
			comms->buffer_level += got;
		}
	}
}

// remove some bytes from the middle (or end) of the rx buffer
static void close_gap(comms_context_t* comms, unsigned int start, unsigned int count)
{
	for(unsigned int i = start; i < comms->buffer_level-count; ++i)
	{
		comms->rxbuffer[i] = comms->rxbuffer[i+count];
	}
	comms->buffer_level -= count;
}

static void process_message(comms_context_t* comms, unsigned int start, unsigned int length)
{

}

void comms_poll(comms_context_t* comms)
{
	process_receive(comms);
	
	// a single byte isn't much good to anyone
	if(comms->buffer_level < 2)
	{
		return;
	}

	unsigned int processed_to = 0;
	for(unsigned int i = 0; i < comms->buffer_level-1; ++i)
	{
		if(comms->state == STATE_WAIT_ACK)
		{
			if(comms->rxbuffer[i] == 0xfd && comms->rxbuffer[i+1] == 0x02)
			{
				// Woohoo this is an ack!
				comms->state = STATE_IDLE;
				i += 1; // the loop will increment by one but we grabbed two bytes
				processed_to = i+1;
				continue;
			}
			else if(comms->rxbuffer[i] == 0xfd && comms->rxbuffer[i+1] == 0x03)
			{
				// Ah a NAK. Remove it from the buffer and resend the last message
				comms->send(comms->txbuffer, comms->lastmsglength);
				i += 1; // the loop will increment by one but we grabbed two bytes
				processed_to = i+1;
				continue;
			}
		}
		else if(comms->rxbuffer[i] == 0xff && comms->rxbuffer[i+1] == 0xdd)
		{
			// do we have enough to be a plausible message?
			if((comms->buffer_level-i) >= 5) // 5 is the shortest possible message
			{
				unsigned int length = 4+comms->rxbuffer[i+3];
				if((comms->buffer_level-i) >= length)
				{
					process_message(comms, i, length);
					i += length;
					processed_to += length;
					continue;
				}
			}
		}
	}
	//Now we have processed as much as we can, remove anything already processed
	// shortcut for the case where we ate the entire buffer
	if(processed_to == comms->buffer_level)
	{
		comms->buffer_level = 0;
	}
	else
	{
		// remove the processed part from the buffer
		close_gap(comms, 0, processed_to);
	}
}

static void prepare_tx_buffer(comms_context_t* comms, unsigned char messagenum, unsigned int payloadLength)
{
	comms->txbuffer[0] = 0xff;
	comms->txbuffer[1] = 0xdd;
	comms->txbuffer[2] = messagenum;
	comms->txbuffer[3] = payloadLength+1; // include checksum in length
}

static unsigned char calculate_checksum(const unsigned char* data)
{
    unsigned char result = 0;

    for(unsigned int i = 0; i < data[3]+1; ++i)
    {
        result += data[2+i];
    }

    return (0xff-result)+1;
}

static void send_message(comms_context_t* comms)
{
	comms->lastmsglength = comms->txbuffer[3]+4;
	comms->send(comms->txbuffer, comms->lastmsglength);
	comms->state = STATE_WAIT_ACK;
}

void comms_send_log(comms_context_t* comms, int level, const char* context, const char* message, int length)
{
	#ifdef __AVR__
	size_t context_length = strlen_P(context);
	#else
	size_t context_length = strlen(context);
	#endif

	const int max_length = max_tx_payload - 3 - context_length; // leave space for size and level fields
	// make sure the buffer is ready - if not, keep trying
	while(comms->state != STATE_IDLE)
	{
		#ifdef __AVR__
		wdt_reset();
		#endif
		comms_poll(comms);
	}
	
	if(length > max_length)
	{
		length = max_length;
	}

	prepare_tx_buffer(comms, MSG_LOG, length+3+context_length);

	comms->txbuffer[4] = level;
	comms->txbuffer[5] = context_length;
	#ifdef __AVR__
	memcpy_P(comms->txbuffer+6, context, context_length);
	#else
	memcpy(comms->txbuffer+6, context, context_length);
	#endif
	comms->txbuffer[6+context_length] = length;
	memcpy(comms->txbuffer+7+context_length, message, length);
	comms->txbuffer[7+context_length+length] = calculate_checksum(comms->txbuffer);
	send_message(comms);
}

void comms_send_logz(comms_context_t* comms, int level, const char* context, const char* message)
{
	comms_send_log(comms, level, context, message, strlen(message));
}

#ifdef __AVR__
void comms_send_log_flash(comms_context_t* comms, int level, const char* context, const char* flashmessage, int length)
{
	size_t context_length = strlen_P(context);

	const int max_length = max_tx_payload - 3 - context_length; // leave space for size and level fields
	// make sure the buffer is ready - if not, keep trying
	while(comms->state != STATE_IDLE)
	{
		#ifdef __AVR__
		wdt_reset();
		#endif
		comms_poll(comms);
	}
	
	if(length > max_length)
	{
		length = max_length;
	}

	prepare_tx_buffer(comms, MSG_LOG, length+3+context_length);

	comms->txbuffer[4] = level;
	comms->txbuffer[5] = context_length;
	memcpy_P(comms->txbuffer+6, context, context_length);
	comms->txbuffer[6+context_length] = length;
	memcpy_P(comms->txbuffer+7+context_length, flashmessage, length);
	comms->txbuffer[7+length+context_length] = calculate_checksum(comms->txbuffer);
	send_message(comms);
}

void comms_send_logz_flash(comms_context_t* comms, int level, const char* context, const char* flashmessage)
{
	comms_send_log_flash(comms, level, context, flashmessage, strlen_P(flashmessage));
}

#endif
