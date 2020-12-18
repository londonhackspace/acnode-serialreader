/******************************************************************************
* ACNodeReader Firmware - SSD1306 I2C Display Interface                       *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "ssd1306.h"
#include "i2c.h"
#include "log.h"

#include <mcufont.h>
#include <string.h>
#include <avr/wdt.h>

ssd1306_control ssd1306;

#define I2C_FAIL_CATCHER(STUFF) if(!(STUFF)) WARN_LOG_LITERAL("Error sending i2c stuff")

void mf_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state)
{
    ssd1306_control* instance = (ssd1306_control*)state;
    for(int i=0; i < count; ++i)
    {
        ssd1306_set_pixel(instance, x+i, y, alpha==255);
    }
}

void ssd1306_init(ssd1306_control* instance, uint8_t address)
{
    memset(instance, 0, sizeof(ssd1306_control));
    instance->address = address;
    instance->display_found = i2c_polladdress(instance->address);
    instance->mode = SSD1306_MODE_PAGE;

    if(instance->display_found)
    {
        INFO_LOG_LITERAL("SSD1306 Display found");
    }
    else
    {
        INFO_LOG_LITERAL("SSD1306 Display NOT found");
        return;
    }
}

bool ssd1306_set_address_mode(ssd1306_control* instance, ssd1306_address_mode mode)
{
    if(!instance->display_found)
    {
        return true;
    }

    uint8_t data[] = { 0x00, 0x20, 0x00};

    if(mode == SSD1306_MODE_PAGE)
    {
        data[2] = 2;
    }    
    else if(mode == SSD1306_MODE_HORIZONTAL)
    {
        data[2] = 0;
    }
    else
    {
        data[2] = 1;
    }

    return i2c_write(instance->address, data, 3);
}

bool ssd1306_set_display_on(ssd1306_control* instance, bool on)
{
    if(!instance->display_found)
    {
        return true;
    }

    uint8_t data[] = { 0x00, 0xaf};

    if(!on)
    {
        data[1] = 0xae;
    }

    return i2c_write(instance->address, data, 2);
}

bool ssd1306_set_column_address(ssd1306_control* instance, uint8_t address)
{
    if(!instance->display_found)
    {
        return true;
    }

    uint8_t data[] = { 0x00, address & 0x0f, 0x10 | (((address & 0x10) >> 4) & 0x0f)};
    return i2c_write(instance->address, data, 3);
}

bool ssd1306_set_page(ssd1306_control* instance, uint8_t page)
{
    if(!instance->display_found)
    {
        return true;
    }
    uint8_t data[] = { 0x00, 0x22, page, 0x07};
    return i2c_write(instance->address, data, 4);
}

void ssd1306_update_page(ssd1306_control* instance, uint8_t page)
{
    ssd1306_set_page(instance, page);
    ssd1306_set_column_address(instance, 0);
    uint8_t* start = instance->buffer + page*128;
    i2c_start();
    i2c_address(instance->address, false);
    wdt_reset();
    i2c_senddata(0x40);
    for(int i=0; i < 128; ++i)
    {
        i2c_senddata(*(start++));
    }
    wdt_reset();
    i2c_stop();
}

enum
{
    STATE_INIT = 0,
    STATE_IDLE = 1,
    STATE_DRAWING = 2,
};

void ssd1306_poll(ssd1306_control* instance)
{
    switch(instance->state)
    {
        case STATE_INIT:
        { 
            instance->updated_needed = true;
            instance->draw_progress = 0;
            ssd1306_set_display_on(instance, true);
            ssd1306_clear(instance);
            const struct mf_font_s* font = mf_find_font("fixed_5x8");
            if(!font)
            {
                const struct mf_font_list_s* fonts = mf_get_font_list();
                const struct mf_font_list_s* cur_fonts = fonts;
                while(cur_fonts)
                {
                    WARN_LOG_LITERAL("Got Font:");
                    WARN_LOG(cur_fonts->font->short_name);
                    cur_fonts = cur_fonts->next;
                }
                if(!fonts)
                {
                    WARN_LOG_LITERAL("Unable to get any font!");
                }
                else
                {
                    font = fonts->font;
                    if(!font)
                    {
                        WARN_LOG_LITERAL("First font is missing!");
                        instance->state = STATE_IDLE;
                        return;
                    }
                    else
                    {
                        WARN_LOG_LITERAL("Using first font");
                        DEBUG_LOG_BUFFER("Font at", (uint8_t*)&font, 2);
                        WARN_LOG(font->short_name);
                    }
                }
            }
            
            const char* text = PSTR("LHS ACNode");
            int pos = 5;
            int len = strlen_P(text);
            for(int i=0;i < len; ++i)
            {
                char c = pgm_read_byte(text+i);
                pos += mf_render_character(font, pos, 5, c, mf_callback, instance);
            }
            instance->state = STATE_IDLE;
        } break;
        case STATE_IDLE:
        {
            if(instance->updated_needed)
            {
                instance->state = STATE_DRAWING;
                DEBUG_LOG_LITERAL("SSD1306 -> DRAWING");
                instance->draw_progress = 0;
            }
        } break;
        case STATE_DRAWING:
        {

            if(instance->draw_progress < 8)
            {
                ssd1306_update_page(instance, instance->draw_progress++);
            }
            else
            {
                instance->state = STATE_IDLE;
                instance->updated_needed = false;
                DEBUG_LOG_LITERAL("SSD1306 -> IDLE");
            }
        } break;
    };
}

void ssd1306_set_pixel(ssd1306_control* instance, uint8_t x, uint8_t y, bool state)
{
    if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
    {
        return;
    }

    uint8_t page = y/8;
    uint8_t *dataptr = instance->buffer + (page*SSD1306_WIDTH)+x;

    if(state)
    {
        (*dataptr) |= (1 << (y % 8));
    }
    else
    {
        (*dataptr) &= ~(1 << (y % 8));
    }
    instance->updated_needed = true;
}

void ssd1306_clear(ssd1306_control* instance)
{
    memset(instance->buffer, 0x00, (SSD1306_WIDTH*SSD1306_HEIGHT)/8);
    instance->updated_needed = true;
}
