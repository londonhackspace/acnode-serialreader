/******************************************************************************
* ACNodeReader Firmware - Logging functions                                   *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef LOG_H
#define LOG_H

#include "commsprotocol.h"

#include <stdint.h>

enum
{
	LOG_ERROR = 0,
	LOG_WARN = 1,
	LOG_INFO = 2,
	LOG_DEBUG = 3
};

// from main.c
extern comms_context_t comms;

#if DEBUG_LEVEL > 0
#include <avr/pgmspace.h>

#define LOG_STRINGIFY_X(X) #X
#define LOG_STRINGIFY(X) LOG_STRINGIFY_X(X)

#define EMIT_LOG(LEVEL, MSG) emit_log(LEVEL, PSTR(__FILE__ ":" LOG_STRINGIFY(__LINE__)), MSG)

#define INFO_LOG(MSG) EMIT_LOG(LOG_INFO, MSG)
#define WARN_LOG(MSG) EMIT_LOG(LOG_WARN, MSG)
#define ERROR_LOG(MSG) EMIT_LOG(LOG_ERROR, MSG)

#define LOG_LITERAL(LEVEL, MSG) { \
						emit_log_p(LEVEL, PSTR(__FILE__ ":" LOG_STRINGIFY(__LINE__)), PSTR(MSG)); \
					} while(0)

#define INFO_LOG_LITERAL(MSG) LOG_LITERAL(LOG_INFO, MSG)
#define WARN_LOG_LITERAL(MSG) LOG_LITERAL(LOG_WARN, MSG)
#define ERROR_LOG_LITERAL(MSG) LOG_LITERAL(LOG_ERROR, MSG)

#if DEBUG_LEVEL > 1
#define DEBUG_LOG(MSG) EMIT_LOG(LOG_DEBUG, MSG)
#define DEBUG_LOG_LITERAL(MSG) LOG_LITERAL(LOG_DEBUG, MSG)

#define DEBUG_LOG_BUFFER(NAME, BUF, LEN) { \
                                            emit_debug_log_buffer(PSTR(__FILE__ ":" LOG_STRINGIFY(__LINE__)), PSTR(NAME), BUF, LEN); \
                                         } while(0)
#else
#define DEBUG_LOG(MSG) while(0)
#define DEBUG_LOG_LITERAL(MSG) while(0)
#define DEBUG_LOG_BUFFER(NAME, BUF, LEN) while(0)
#endif

#else
// no logging
#define INFO_LOG(MSG) while(0)
#define WARN_LOG(MSG) while(0)
#define ERROR_LOG(MSG) while(0)
#define DEBUG_LOG(MSG) while(0)
#define INFO_LOG_LITERAL(MSG) while(0)
#define WARN_LOG_LITERAL(MSG) while(0)
#define ERROR_LOG_LITERAL(MSG) while(0)
#define DEBUG_LOG_LITERAL(MSG) while(0)
#define DEBUG_LOG_BUFFER(NAME, BUF, LEN) while(0)
#endif

static inline void emit_log(int level, const char* location, const char* message)
{ 
    comms_send_logz(&comms, level, location, message);
}

static inline void emit_log_p(int level, const char* location, const char* message)
{
    comms_send_logz_flash(&comms, level, location, message);
}

void emit_debug_log_buffer(const char* location, const char* name, uint8_t* buffer, uint8_t length);

// Use these to determine if you should log a particular level or not
inline static int should_log(int level)
{
    #if DEBUG_LEVEL > 1
    return 1;
    #elif DEBUG_LEVEL > 0
    return (level < LOG_DEBUG) ? 1 : 0;
    #else
    return 0;
    #endif
}

#endif
