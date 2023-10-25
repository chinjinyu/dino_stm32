#pragma once

#include <stdint.h>

typedef struct {
    void (*callback)(void *arg);
    void *arg;
    uint32_t prev_time;
    uint16_t period;
    uint8_t run:1;
} sw_timer_t;

void sw_timer_start(sw_timer_t *tm, uint32_t period, void (*callback)(void *arg), void *arg);
void sw_timer_stop(sw_timer_t *tm);
void sw_timer_update(sw_timer_t *tm);
