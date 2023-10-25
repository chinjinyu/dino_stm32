#include <stm32g0xx_hal.h>
#include <stdio.h>
#include <bsp.h>

int main(void)
{
    HAL_Init();
    bsp_init();

    uint8_t i = 0;
    for (;;) {
        bsp_oled_clear();
        for (uint8_t j = 0; j < 64; j++) {
            if (i + j >= 128) {
                break;
            }
            bsp_oled_draw_point(i + j, j, 1);
        }
        bsp_oled_draw_char(0, 0, 'O');
        bsp_oled_draw_string(0, 30, "Hello, World!");
        bsp_oled_refresh();
        i = (i + 1) % 128;
        bsp_wait_ms(50);
    }
}
