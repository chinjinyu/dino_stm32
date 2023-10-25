#include <cactus.h>
#include <bsp.h>

// 7 x 16
static const uint8_t cactus_image_data_l1[] = {
    0xF0, 0x00, 0xFE, 0xFF, 0xFE, 0x80, 0xFC, 0x03,
    0x06, 0xFF, 0xFF, 0xFF, 0x01, 0x01,
};

// 15 x 16
static const uint8_t cactus_image_data_l2[] = {
    0xF0, 0x00, 0xFE, 0xFF, 0xFE, 0x80, 0xFC, 0x00,
    0x7C, 0xF8, 0xC0, 0xFF, 0xFE, 0x00, 0xFC, 0x03,
    0x06, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00,
    0x00, 0xFF, 0xFF, 0xFF, 0x03, 0x03,
};

// 23 x 16
static const uint8_t cactus_image_data_l3[] = {
    0xF0, 0x00, 0xFE, 0xFF, 0xFE, 0x80, 0xFC, 0x00,
    0xFE, 0x00, 0xFE, 0xFF, 0xFE, 0x00, 0xF8, 0x00,
    0xFC, 0x80, 0xFE, 0xFF, 0xFE, 0x00, 0xFC, 0x03,
    0x06, 0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0x03,
    0x06, 0xFF, 0xFF, 0xFF, 0x0C, 0x0F, 0x00, 0x00,
    0x01, 0xFF, 0xFF, 0xFF, 0x03, 0x03,
};

static const image_t cactus_images[] = {
    {
        .width = 7,
        .height = 16,
        .data = cactus_image_data_l1
    },
    {
        .width = 15,
        .height = 16,
        .data = cactus_image_data_l2
    },
    {
        .width = 23,
        .height = 16,
        .data = cactus_image_data_l3
    }
};

void cactus_init(cactus_t *c)
{
    c->x = 0;
    c->y = 0;
    c->state = 1;
    c->images = cactus_images;
    c->mask_images = cactus_images;
}

void cactus_set_position(cactus_t *c, int16_t x, int16_t y)
{
    c->x = x;
    c->y = y;
}

void cactus_get_position(const cactus_t *c, int16_t *x, int16_t *y)
{
    *x = c->x;
    *y = c->y;
}

void cactus_set_state(cactus_t *c, cactus_state_t state)
{
    c->state = state;
}

cactus_state_t cactus_get_state(const cactus_t *c)
{
    return c->state;
}

const image_t *cactus_get_mask(const cactus_t *c)
{
    return &c->mask_images[c->state];
}

void cactus_move(cactus_t *c, int16_t dx, int16_t dy)
{

    c->x += dx;
    c->y += dy;
}

void cactus_update(cactus_t *c)
{
    image_draw_with_mask(&c->images[c->state], c->x, c->y, &c->mask_images[c->state]);
}
