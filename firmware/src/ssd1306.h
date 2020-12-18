/******************************************************************************
* ACNodeReader Firmware - SSD1306 I2C Display Interface                       *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <stdbool.h>

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

typedef enum ssd1306_address_mode
{
    SSD1306_MODE_PAGE,
    SSD1306_MODE_HORIZONTAL,
    SSD1306_MODE_VERTICAL,
} ssd1306_address_mode;

typedef struct ssd1306_control
{
    uint8_t address;
    bool display_found;
    bool updated_needed;
    uint8_t draw_progress;
    ssd1306_address_mode mode;
    uint8_t state;
    uint8_t buffer[(SSD1306_WIDTH*SSD1306_HEIGHT)/8];
} ssd1306_control;

void ssd1306_init(ssd1306_control* instance, uint8_t address);
void ssd1306_poll(ssd1306_control* instance);

bool ssd1306_set_address_mode(ssd1306_control* instance, ssd1306_address_mode mode);
bool ssd1306_set_column_address(ssd1306_control* instance, uint8_t address);
bool ssd1306_set_page(ssd1306_control* instance, uint8_t page);

bool ssd1306_set_display_on(ssd1306_control* instance, bool on);

// set a pixel to on or off
void ssd1306_set_pixel(ssd1306_control* instance, uint8_t x, uint8_t y, bool state);
void ssd1306_clear(ssd1306_control* instance);

extern ssd1306_control ssd1306;

#endif