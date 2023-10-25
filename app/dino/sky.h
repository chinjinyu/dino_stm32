#pragma once

#include <cloud.h>

#define NUM_CLOUDS  3
#define SKY_BASE    32
#define SKY_HEIGHT  24
#define SKY_WIDTH   128

typedef struct {
    cloud_t clouds[NUM_CLOUDS];
} sky_t;

void sky_init(sky_t *sky);
void sky_move(sky_t *sky, int16_t dx);
void sky_update(sky_t *sky);
