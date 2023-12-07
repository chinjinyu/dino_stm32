#include <stm32g0xx_hal.h>
#include <stdio.h>
#include <bsp.h>

int main(void)
{
    HAL_Init();
    bsp_init();

    printf("HAL version: 0x%08lX.\r\n", HAL_GetHalVersion());
    printf("SYSCLK: %luHz.\r\n", HAL_RCC_GetSysClockFreq());
    printf("HCLK: %luHz.\r\n", HAL_RCC_GetHCLKFreq());
    printf("PCLK1: %luHz.\r\n", HAL_RCC_GetPCLK1Freq());

    for (;;) {
        printf("[%10lu] Hello, STM32G030F6!\r\n", bsp_get_uptime_ms());
        bsp_wait_ms(1000);
    }
}
