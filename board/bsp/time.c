#include <bsp/time.h>
#include <stm32g0xx_hal.h>

void bsp_wait_us(uint32_t us)
{
    uint32_t prev_val = SysTick->VAL;
    uint32_t total = HAL_RCC_GetHCLKFreq() / 1000000 * us;
    uint32_t count = 0;

    do {
        uint32_t curr_val = SysTick->VAL;
        count += prev_val < curr_val ? prev_val + SysTick->LOAD + 1 - curr_val : prev_val - curr_val;
        prev_val = curr_val;
    } while (count < total);
}

void bsp_wait_ms(uint32_t ms)
{
    uint32_t prev_val = SysTick->VAL;
    uint32_t total = HAL_RCC_GetHCLKFreq() / 1000 * ms;
    uint32_t count = 0;

    do {
        uint32_t curr_val = SysTick->VAL;
        count += prev_val < curr_val ? prev_val + SysTick->LOAD + 1 - curr_val : prev_val - curr_val;
        prev_val = curr_val;
    } while (count < total);
}

uint32_t bsp_get_uptime(void)
{
    return HAL_GetTick() / (1000 / HAL_GetTickFreq());
}

uint32_t bsp_get_uptime_ms(void)
{
    return HAL_GetTick();
}
