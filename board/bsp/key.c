#include <bsp/key.h>
#include <stm32g0xx_hal.h>

void bsp_key_init(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef gpio_config = {
        .Pin = GPIO_PIN_15,
        .Mode = GPIO_MODE_INPUT,
        .Pull = GPIO_PULLUP
    };
    HAL_GPIO_Init(GPIOC, &gpio_config);
}

uint8_t bsp_key_is_pressed(void)
{
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) ? 0 : 1;
}
