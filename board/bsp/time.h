#pragma once

#include <stdint.h>

void bsp_wait_us(uint32_t us);
void bsp_wait_ms(uint32_t ms);
uint32_t bsp_get_uptime(void);
uint32_t bsp_get_uptime_ms(void);
