#pragma once

#include <stdint.h>

void bsp_oled_init(void);
void bsp_oled_reset(void);
void bsp_oled_write_data(const uint8_t *ptr, uint16_t size);
void bsp_oled_write_command(const uint8_t *ptr, uint16_t size);

void bsp_oled_refresh(void);

void bsp_oled_clear(void);
void bsp_oled_draw_point(uint8_t x, uint8_t y, uint8_t c);
void bsp_oled_draw_char(uint8_t x, uint8_t y, char c);
void bsp_oled_draw_string(uint8_t x, uint8_t y, const char *str);
