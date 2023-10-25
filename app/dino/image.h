#pragma once

#include <stdint.h>

typedef struct {
    uint8_t width;
    uint8_t height;
    const uint8_t * data;
} image_t;

uint8_t image_read_pixel(const image_t *img, uint8_t x, uint8_t y);
void image_draw(const image_t *img, int16_t x, int16_t y);
void image_draw_with_mask(const image_t *img, int16_t x, int16_t y, const image_t *mask);
