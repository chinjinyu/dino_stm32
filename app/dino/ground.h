#pragma once

#include <stdint.h>

#define GROUND_HEIGHT       4
#define GROUND_INIT_WIDTH   24
#define GROUND_WIDTH        128

typedef struct {
    uint8_t random[GROUND_WIDTH];
    uint8_t end;
    uint8_t full;
} ground_t;

void ground_init(ground_t *g);
void ground_move(ground_t *g, int16_t dx);
void ground_update(ground_t *g);
