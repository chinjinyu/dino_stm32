#include <bsp/time.h>
#include <stm32g0xx_hal.h>

static uint32_t get_uptime_us(void)
{
    uint32_t tick1 = HAL_GetTick();
    uint32_t tick2, us;
    const uint32_t k = HAL_GetTickFreq() * 1000;
    const uint32_t p = SysTick->LOAD + 1;
    do {
        us = (SysTick->LOAD - SysTick->VAL) * k / p;
        tick2 = tick1;
        tick1 = HAL_GetTick();
    } while (tick1 != tick2);
    return us + tick1 * k;
}

void bsp_wait_us(uint32_t us)
{
    uint32_t prev = get_uptime_us();
    uint32_t count = 0;

    do {
        uint32_t curr = get_uptime_us();
        count += curr - prev;
        prev = curr;
    } while (count < us);
}

void bsp_wait_ms(uint32_t ms)
{
    uint32_t prev = get_uptime_us();
    uint32_t total = ms * 1000;
    uint32_t count = 0;

    do {
        uint32_t curr = get_uptime_us();
        count += curr - prev;
        prev = curr;
    } while (count < total);
}

uint32_t bsp_get_uptime(void)
{
    return HAL_GetTick() / (1000 / HAL_GetTickFreq());
}

uint32_t bsp_get_uptime_ms(void)
{
    return HAL_GetTick() * HAL_GetTickFreq();
}
