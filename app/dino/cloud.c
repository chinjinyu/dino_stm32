#include <cloud.h>
#include <bsp.h>

static const uint8_t cloud_image_data[][24 * 8 / 8] = {
    {
        0x80, 0xC0, 0x40, 0x60, 0x20, 0xE0, 0xA0, 0xB0,
        0x90, 0x9C, 0x86, 0x82, 0x82, 0x82, 0x82, 0x96,
        0x8C, 0x88, 0x88, 0x88, 0x98, 0xB0, 0xE0, 0xC0,
    }
};

static const uint8_t cloud_mask_image_data[][24 * 8 / 8] = {
    {
        0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xF0,
        0xF0, 0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
        0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0,
    }
};

static const image_t cloud_images[] = {
    {
        .width = 24,
        .height = 8,
        .data = cloud_image_data[0]
    }
};

static const image_t cloud_mask_images[] = {
    {
        .width = 24,
        .height = 8,
        .data = cloud_mask_image_data[0]
    }
};

void cloud_init(cloud_t *c)
{
    c->x = 0;
    c->y = 0;
    c->image = &cloud_images[0];
    c->mask_image = &cloud_mask_images[0];
}

void cloud_set_position(cloud_t *c, int16_t x, int16_t y)
{
    c->x = x;
    c->y = y;
}

void cloud_get_position(cloud_t *c, int16_t *x, int16_t *y)
{
    *x = c->x;
    *y = c->y;
}

void cloud_move(cloud_t *c, int16_t dx, int16_t dy)
{
    c->x += dx;
    c->y += dy;
}

void cloud_update(cloud_t *c)
{
    image_draw_with_mask(c->image, c->x, c->y, c->mask_image);
}
