/******************************************************************************
* ACNodeReader Firmware - Logging functions                                   *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "log.h"

#if DEBUG_LEVEL > 0

// for now, log with basic serial messages
// TODO: Rework this once the proper protocol exists

#include "serial.h"

static void put_level(int level)
{
    switch(level)
    {
#if DEBUG_LEVEL > 1
    case LOG_DEBUG:
        {
            serial_put_P((const unsigned char*)PSTR("[DEBUG] "), 8);
        } break;
#endif
    case LOG_INFO:
        {
            serial_put_P((const unsigned char*)PSTR("[INFO] "), 7);
        } break;
    case LOG_WARN:
        {
            serial_put_P((const unsigned char*)PSTR("[WARN] "), 7);
        } break;
    case LOG_ERROR:
        {
            serial_put_P((const unsigned char*)PSTR("[ERROR] "), 8);
        } break;
    }
}

void emit_log(int level, const char* location, const char* message)
{
    put_level(level);
    serial_putz_P(location);
    serial_putchar(' ');
    serial_putz(message);
    serial_putchar('\n');
}

void emit_log_p(int level, const char* location, const char* message)
{
    put_level(level);
    serial_putz_P(location);
    serial_putchar(' ');
    serial_putz_P(message);
    serial_putchar('\n');
}

static int countHexDigits(unsigned long val, unsigned long* out_max_val)
{
    int count = 0;
    unsigned long currentPow = 1;

    // 0 is a bit of a special case
    if(val == 0)
    {
        if(out_max_val)
        {
            *out_max_val = 1;
        }
        return 1;
    }

    while(currentPow <= val)
    {
        ++count;
        currentPow = currentPow << 4;
    }

    if(out_max_val)
    {
        *out_max_val = currentPow >> 4;
    }

    return count;
}

static char intToHexDigit(unsigned char val)
{
    if(val < 10)
    {
        return '0' + val;
    }

    if(val < 16)
    {
        return 'a' + (val-10);
    }
    else
    {
        // that's not valid!
        return '?';
    }
}

static void uinttohexstring(unsigned int val, char* buffer, int bufferlength)
{
    unsigned long max_col_val;
    int digitcount = countHexDigits(val, &max_col_val);

    if(bufferlength < (digitcount+1))
    {
        if(bufferlength >= 1)
        {
            buffer[0] = '\0';
        }
        return;
    }

    int col = 0;
    while(col < bufferlength && col < digitcount)
    {
        buffer[col] = intToHexDigit(val/max_col_val);
        val %= max_col_val;
        max_col_val = max_col_val >> 4;
        ++col;
    }

    buffer[digitcount] = '\0';
}

void emit_debug_log_buffer(const char* location, const char* name, uint8_t* buffer, uint8_t length)
{
    put_level(LOG_DEBUG);
    serial_putz_P(location);
    serial_putchar(' ');
    serial_putz_P(name);
    for(int i=0; i < length; ++i)
    {
        serial_putchar(' ');
        serial_putz_P(PSTR("0x"));
        char dbg_msg_buffer[16]; \
        uinttohexstring(buffer[i], dbg_msg_buffer, 16); \
        serial_putz(dbg_msg_buffer);
    }
    serial_putchar('\n');
}

#endif // DEBUG_LEVEL > 0
