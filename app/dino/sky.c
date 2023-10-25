#include <sky.h>
#include <stdlib.h>

void sky_init(sky_t *sky)
{
    for (uint8_t i = 0; i < NUM_CLOUDS; i++) {
        cloud_init(&sky->clouds[i]);
        int16_t x = rand() % (SKY_WIDTH * 2) + SKY_WIDTH;
        int16_t y = rand() % SKY_HEIGHT + SKY_BASE;
        cloud_set_position(&sky->clouds[i], x, y);
    }
}

void sky_move(sky_t *sky, int16_t dx)
{
    if (dx >= 0) {
        return ;
    }

    for (uint8_t i = 0; i < NUM_CLOUDS; i++) {
        cloud_move(&sky->clouds[i], dx, 0);

        int16_t x, y;
        cloud_get_position(&sky->clouds[i], &x, &y);
        if (x < -SKY_WIDTH / 3) {
            x = rand() % (SKY_WIDTH * 2) + SKY_WIDTH;
            y = rand() % SKY_HEIGHT + SKY_BASE;
            cloud_set_position(&sky->clouds[i], x, y);
        }
    }
}

void sky_update(sky_t *sky)
{
    for (uint8_t i = 0; i < NUM_CLOUDS; i++) {
        cloud_update(&sky->clouds[i]);
    }
}
