#include <sw_timer.h>
#include <bsp.h>

void sw_timer_start(sw_timer_t *tm, uint32_t period, void (*callback)(void *arg), void *arg)
{
    tm->prev_time = bsp_get_uptime_ms();
    tm->period = period;
    tm->callback = callback;
    tm->arg = arg;
    tm->run = 1;
}

void sw_timer_stop(sw_timer_t *tm)
{
    tm->run = 0;
}

void sw_timer_update(sw_timer_t *tm)
{
    uint32_t curr_time = bsp_get_uptime_ms();
    while (tm->run && curr_time - tm->prev_time >= tm->period) {
        tm->prev_time += tm->period;
        if (tm->callback) {
            tm->callback(tm->arg);
        }
        curr_time = bsp_get_uptime_ms();
    }
}
