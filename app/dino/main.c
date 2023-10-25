#include <stm32g0xx_hal.h>
#include <stdio.h>
#include <bsp.h>
#include <key.h>
#include <sw_timer.h>
#include <game.h>

static void key_callback(uint8_t event, void *arg);
static void oled_timer_callback(void *arg);

static key_t key;
static sw_timer_t oled_timer;
static game_t game;

int main(void)
{
    HAL_Init();
    bsp_init();

    key_start(&key, key_callback, NULL);
    sw_timer_start(&oled_timer, 100, oled_timer_callback, NULL);
    game_start(&game);

    for (;;) {
        key_update(&key);
        game_update(&game);
        sw_timer_update(&oled_timer);
    }
}

static void key_callback(uint8_t event, void *arg)
{
    UNUSED(arg);

    if (event == KEY_DOWN) {
        game_key_handler(&game, GAME_K0, GAME_KEV_DOWN);
    }
}

static void oled_timer_callback(void *arg)
{
    UNUSED(arg);

    bsp_oled_refresh();
}
