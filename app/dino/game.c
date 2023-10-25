#include <game.h>
#include <bsp.h>
#include <stdlib.h>
#include <stdio.h>

// 27 x 24
static const uint8_t retry_image_data[] = {
    0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F,
    0x3F, 0x3F, 0x3F, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF,
    0xFF, 0x3F, 0x3F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFE, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x7E, 0x7E, 0x7E, 0x78, 0x7C,
    0x7E, 0x7F, 0x7F, 0x7F, 0x7E, 0x7E, 0x00, 0x00,
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x7F,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xFC, 0xFC,
    0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
    0xFC, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F,
    0x3F,
};

// 27 x 24
static const uint8_t retry_mask_image_data[] = {
    0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFE, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x7F,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F,
    0x3F,
};

static const image_t retry_image = {
    .width = 27,
    .height = 24,
    .data = retry_image_data
};

static const image_t retry_mask_image = {
    .width = 27,
    .height = 24,
    .data = retry_mask_image_data
};

static void game_timer_callback(void *arg);
static uint8_t is_overlap(const dino_t *dino, const cactus_t *c);

void game_start(game_t *g)
{
    g->state = 0;
    g->retry_image = &retry_image;
    g->retry_mask_image = &retry_mask_image;

    srand(bsp_get_uptime_ms());

    ground_init(&g->ground);
    sky_init(&g->sky);
    cactus_init(&g->cactus);
    cactus_set_position(&g->cactus, GROUND_WIDTH * 2, 0);
    dino_init(&g->dino);
    sw_timer_start(&g->timer, 90, game_timer_callback, g);
}

void game_update(game_t *g)
{
    sw_timer_update(&g->timer);
}

void game_key_handler(game_t *g, game_key_t key, game_key_event_t event)
{
    if (key == GAME_K0 && event == GAME_KEV_DOWN) {
        if (g->state == 0) {
            g->state = 1;
            dino_jump(&g->dino);
        } else if (g->state == 1) {
            dino_jump(&g->dino);
        } else if (g->state == 2) {
            game_start(g);
        }
    }
}

static void game_timer_callback(void *arg)
{
    game_t *g = (game_t *)arg;

    bsp_oled_clear();

    if (g->state == 1) {
        ground_move(&g->ground, -5);
        sky_move(&g->sky, -1);

        cactus_move(&g->cactus, -5, 0);
        int16_t x, y;
        cactus_get_position(&g->cactus, &x, &y);
        if (x < -GROUND_WIDTH / 2) {
            x = GROUND_WIDTH;
            cactus_set_position(&g->cactus, x, y);
            cactus_set_state(&g->cactus, rand() % NUM_CACTUS_STATE);
        }

        if (is_overlap(&g->dino, &g->cactus)) {
            dino_over(&g->dino);
            g->state = 2;
        }
    }

    ground_update(&g->ground);
    sky_update(&g->sky);
    cactus_update(&g->cactus);
    dino_update(&g->dino);

    if (g->state == 2) {
        image_draw_with_mask(g->retry_image, 50, 20, g->retry_mask_image);
    }
}

static uint8_t is_overlap(const  dino_t *dino, const cactus_t *c)
{
    const image_t *dmask = dino_get_mask(dino);
    const image_t *cmask = cactus_get_mask(c);
    int16_t dx, dy, cx, cy;
    dino_get_position(dino, &dx, &dy);
    cactus_get_position(c, &cx, &cy);

    // 以下这个判断两个目标是否重叠的方法太耗时了，迫切需要改进
    for (uint8_t di = 0; di < dmask->width; di++) {
        for (uint8_t dj = 0; dj < dmask->height; dj++) {
            uint8_t dp = image_read_pixel(dmask, di, dj);
            if (dp == 0) {
                continue;
            }

            int16_t ddx = dx + di;
            int16_t ddy = dy + dj;

            for (uint8_t ci = 0; ci < cmask->width; ci++) {
                for (uint8_t cj = 0; cj < cmask->height; cj++) {
                    uint8_t cp = image_read_pixel(cmask, ci, cj);
                    if (cp == 0) {
                        continue;
                    }

                    int16_t ccx = cx + ci;
                    int16_t ccy = cy + cj;

                    if (ddx == ccx && ddy == ccy) {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}
