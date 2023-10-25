#include <bsp.h>
#include <stm32g0xx_hal.h>
#include <stdio.h>

void bsp_init(void)
{
    bsp_clock_init();
    bsp_stdio_init();

    printf("SYSCLK: %luHz.\r\n", HAL_RCC_GetSysClockFreq());
    printf("HCLK: %luHz.\r\n", HAL_RCC_GetHCLKFreq());
    printf("PCLK1: %luHz.\r\n", HAL_RCC_GetPCLK1Freq());

    bsp_oled_init();
    bsp_key_init();
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    printf("%s:%lu assert failed!\r\n", file, line);
    for (;;);
}
#endif
