#pragma once

#include <stdint.h>
#include <image.h>

typedef struct {
    const image_t *image;
    const image_t *mask_image;
    int16_t x;
    int16_t y;
} cloud_t;

void cloud_init(cloud_t *c);
void cloud_set_position(cloud_t *c, int16_t x, int16_t y);
void cloud_get_position(cloud_t *c, int16_t *x, int16_t *y);
void cloud_move(cloud_t *c, int16_t dx, int16_t dy);
void cloud_update(cloud_t *c);
