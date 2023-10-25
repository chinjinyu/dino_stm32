#include <key.h>
#include <bsp.h>

static void key_tm_callback(void *arg);

void key_start(key_t *key, void (*callback)(uint8_t event, void *arg), void *arg)
{
    key->callback = callback;
    key->arg = arg;
    key->status = 0;
    sw_timer_start(&key->tm, 10, key_tm_callback, key);
}

void key_stop(key_t *key)
{
    sw_timer_stop(&key->tm);
}

void key_update(key_t *key)
{
    sw_timer_update(&key->tm);
}

static void key_tm_callback(void *arg)
{
    key_t *key = (key_t *)arg;

    key->status <<= 1;
    key->status |= bsp_key_is_pressed();

    if ((key->status & 0x07) == 0x03) {
        key->callback(KEY_DOWN, key->arg);
    } else if ((key->status & 0x07) == 0x04) {
        key->callback(KEY_UP, key->arg);
    }
}
