/******************************************************************************
* ACNodeReader Firmware - Logging functions                                   *
*                                                                             *
* (c) 2019 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "log.h"

#include "string.h"

#if DEBUG_LEVEL > 0

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


char dbg_msg_buffer[256];

void emit_debug_log_buffer(const char* location, const char* name, uint8_t* buffer, uint8_t length)
{
    size_t bufferptr = 0;
    size_t namelength = strlen_P(name);
    memcpy_P(dbg_msg_buffer, name, namelength);
    dbg_msg_buffer[namelength] = ' ';
    bufferptr = namelength+1;

    for(int i=0; i < length; ++i)
    {
        dbg_msg_buffer[bufferptr++] = ' ';
        char scratch[16];
        uinttohexstring(buffer[i], scratch, 16);
        size_t scratchLength = strlen(scratch);
        memcpy(dbg_msg_buffer+bufferptr, scratch, scratchLength);
        bufferptr += scratchLength;
    }

    comms_send_log(&comms, LOG_DEBUG, location, dbg_msg_buffer, bufferptr);
}

#endif // DEBUG_LEVEL > 0
