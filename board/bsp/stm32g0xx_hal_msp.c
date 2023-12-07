#include <stm32g0xx_hal.h>

void HAL_MspInit(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
}

void HAL_MspDeInit(void)
{
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();

        GPIO_InitTypeDef gpio_config = {
            .Pin = GPIO_PIN_2 | GPIO_PIN_3,
            .Pull = GPIO_NOPULL,
            .Mode = GPIO_MODE_AF_PP,
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Alternate = GPIO_AF1_USART2
        };
        HAL_GPIO_Init(GPIOA, &gpio_config);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) {
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
        
        __HAL_RCC_USART2_CLK_DISABLE();
    }
}
