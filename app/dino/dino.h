#pragma once

#include <stdint.h>
#include <image.h>

#define DINO_JUMP_HEIGHT    40
#define DINO_JUMP_STEP      5

#define DINO_RUN_DIST       10
#define DINO_RUN_STEP       1

typedef enum {
    DINO_NORMAL = 0,
    DINO_OVER,
    DINO_R,
    DINO_L
} dino_state_t;

typedef struct {
    const image_t *images;
    const image_t *mask_images;
    int16_t x;
    int16_t y;
    uint8_t state;

    uint8_t act;
    int8_t jump_dir;
    uint8_t left_or_right;
} dino_t;

void dino_init(dino_t *dino);
void dino_set_state(dino_t *dino, dino_state_t state);
dino_state_t dino_get_state(const dino_t *dino);
void dino_set_position(dino_t *dino, int16_t x, int16_t y);
void dino_get_position(const dino_t *dino, int16_t *x, int16_t *y);
const image_t *dino_get_mask(const dino_t *dino);
void dino_move(dino_t *dino, int16_t dx, int16_t dy);
void dino_update(dino_t *dino);

void dino_jump(dino_t *dino);
void dino_over(dino_t *dino);
uint8_t dino_is_dead(dino_t *dino);
