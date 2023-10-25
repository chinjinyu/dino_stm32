#pragma once

#include <stdint.h>
#include <sw_timer.h>
#include <image.h>
#include <dino.h>
#include <ground.h>
#include <sky.h>
#include <cactus.h>

typedef enum {
    GAME_K0 = 0,
    GAME_K1,
} game_key_t;

typedef enum {
    GAME_KEV_UP,
    GAME_KEV_DOWN,
} game_key_event_t;

typedef struct {
    sw_timer_t timer;
    dino_t dino;
    cactus_t cactus;
    ground_t ground;
    sky_t sky;

    uint8_t state;
    const image_t *retry_image;
    const image_t *retry_mask_image;
} game_t;

void game_start(game_t *g);
void game_update(game_t *g);
void game_key_handler(game_t *g, game_key_t key, game_key_event_t event);
