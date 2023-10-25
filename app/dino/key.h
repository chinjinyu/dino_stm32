#pragma once

#include <sw_timer.h>

#define KEY_NONE    0
#define KEY_DOWN    1
#define KEY_UP      2

typedef struct {
    sw_timer_t tm;
    uint8_t status;
    void (*callback)(uint8_t event, void *arg);
    void *arg;
} key_t;

void key_start(key_t *key, void (*callback)(uint8_t event, void *arg), void *arg);
void key_stop(key_t *key);
void key_update(key_t *key);
