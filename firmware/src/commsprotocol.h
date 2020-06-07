/******************************************************************************
* ACNodeReader Firmware - Comms Protocol                                      *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef COMMSPROTOCOL_H
#define COMMSPROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

// Send/Receive function pointer definitions
typedef void(*sendfunc)(const unsigned char*,unsigned int);
typedef unsigned int(*recvfunc)(unsigned char*,unsigned int);


// Depending on which end of the link you're at, you might want to flip these
#define COMMS_TXBUFFER_SIZE 256
#define COMMS_RXBUFFER_SIZE 64

typedef struct
{
    sendfunc send;
    recvfunc receive;

    int state;

    // For handling outgoing message assembly
    unsigned char txbuffer[COMMS_TXBUFFER_SIZE];
    unsigned int lastmsglength;

    // For handling incoming messages
    unsigned char rxbuffer[COMMS_RXBUFFER_SIZE];
    unsigned int buffer_level;
} comms_context_t;

enum loglevels
{
	LOG_LEVEL_ERROR = 0,
	LOG_LEVEL_WARN = 1,
	LOG_LEVEL_INFO = 2,
	LOG_LEVEL_DEBUG  = 3,
};

void comms_init(comms_context_t* comms);
void comms_set_handlers(comms_context_t* comms, sendfunc send, recvfunc receive);
void comms_poll(comms_context_t* comms);

// On AVR, context is assumed to always be in PROGMEM as used by the logging macros
void comms_send_log(comms_context_t* comms, int level, const char* context, const char* message, int length);
void comms_send_logz(comms_context_t* comms, int level, const char* context, const char* message);

#ifdef __AVR__
void comms_send_log_flash(comms_context_t* comms, int level, const char* context, const char* flashmessage, int length);
void comms_send_logz_flash(comms_context_t* comms, int level, const char* context, const char* flashmessage);
#endif

#ifdef __cplusplus
}
#endif

#endif
