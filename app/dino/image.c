#include <image.h>
#include <bsp.h>

uint8_t image_read_pixel(const image_t *img, uint8_t x, uint8_t y)
{
    return img->data[x + ((img->height >> 3) - 1 - (y >> 3)) * img->width] & (1 << (7 - (y & 0x07)));
}

void image_draw(const image_t *img, int16_t x, int16_t y)
{
    for (uint8_t i = 0; i < img->width; i++) {
        for (uint8_t j = 0; j < img->height; j++) {
            if (x + i < 0 || x + i >= 128 || y + j < 0 || y + j >= 64) {
                continue;
            }
            bsp_oled_draw_point(x + i, y + j, image_read_pixel(img, i, j));
        }
    }
}

void image_draw_with_mask(const image_t *img, int16_t x, int16_t y, const image_t *mask)
{
    for (uint8_t i = 0; i < img->width; i++) {
        for (uint8_t j = 0; j < img->height; j++) {
            if (x + i < 0 || x + i >= 128 || y + j < 0 || y + j >= 64 || !image_read_pixel(mask, i, j)) {
                continue;
            }
            bsp_oled_draw_point(x + i, y + j, image_read_pixel(img, i, j));
        }
    }
}
