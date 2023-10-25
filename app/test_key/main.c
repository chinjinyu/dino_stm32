#include <stm32g0xx_hal.h>
#include <stdio.h>
#include <bsp.h>

int main(void)
{
    HAL_Init();
    bsp_init();

    uint32_t prev_time = bsp_get_uptime_ms();
    uint8_t k = 0;
    for (;;) {
        uint32_t curr_time = bsp_get_uptime_ms();
        if (curr_time - prev_time >= 10) {
            prev_time = curr_time;

            k <<= 1;
            k |= bsp_key_is_pressed();

            if ((k & 0x03) == 0x01) {
                printf("key is pressed!\r\n");
            } else if ((k & 0x03) == 0x02) {
                printf("key is released!\r\n");
            }
        }
    }
}
