#pragma once

#include <stdint.h>
#include <image.h>

typedef enum {
    CACTUS_L1   = 0,
    CACTUS_L2,
    CACTUS_L3,
    NUM_CACTUS_STATE
} cactus_state_t;

typedef struct {
    const image_t *images;
    const image_t *mask_images;
    int16_t x;
    int16_t y;
    uint8_t state;
} cactus_t;

void cactus_init(cactus_t *c);
void cactus_set_position(cactus_t *c, int16_t x, int16_t y);
void cactus_get_position(const cactus_t *c, int16_t *x, int16_t *y);
void cactus_set_state(cactus_t *c, cactus_state_t state);
cactus_state_t cactus_get_state(const cactus_t *c);
const image_t *cactus_get_mask(const cactus_t *c);
void cactus_move(cactus_t *c, int16_t dx, int16_t dy);
void cactus_update(cactus_t *c);
