#include <ground.h>
#include <bsp.h>
#include <stdlib.h>

void ground_init(ground_t *g)
{
    g->end = GROUND_INIT_WIDTH;
    g->full = 0;

    for (uint8_t i = 0; i < g->end; i++) {
        g->random[i] = rand() % (GROUND_HEIGHT << 3);
    }
    for (uint8_t i = g->end; i < GROUND_WIDTH; i++) {
        g->random[i] = 0xFF;
    }
}

void ground_move(ground_t *g, int16_t dx)
{
    if (dx >= 0) {
        return ;
    }

    dx = -dx;

    while (dx != 0) {
        g->random[g->end++] = rand() % (GROUND_HEIGHT << 3);
        if (g->end == GROUND_WIDTH) {
            g->end = 0;
            g->full = 1;
        }
        dx--;
    }
}

void ground_update(ground_t *g)
{
    uint8_t i = g->full ? g->end : 0;
    uint8_t x = 0;
    do {
        for (uint8_t j = 0; j < GROUND_HEIGHT; j++) {
            bsp_oled_draw_point(x, j, g->random[i] == j ? 1 : 0);
        }
        bsp_oled_draw_point(x++, GROUND_HEIGHT, 1);
        i = (i + 1) % GROUND_WIDTH;
    } while (i != g->end);
}
