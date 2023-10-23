#include <bsp/stdio.h>
#include <stm32g0xx_hal.h>

static UART_HandleTypeDef *stdio_huart = NULL;

void bsp_stdio_init(void)
{
    static UART_HandleTypeDef uart = {
        .Instance = USART2,
        .Init = {
            .BaudRate = 115200,
            .Mode = UART_MODE_TX_RX,
            .WordLength = UART_WORDLENGTH_8B,
            .Parity = UART_PARITY_NONE,
            .StopBits = UART_STOPBITS_1,
            .HwFlowCtl = UART_HWCONTROL_NONE,
            .OverSampling = UART_OVERSAMPLING_16,
            .OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE,
            .ClockPrescaler = UART_PRESCALER_DIV1
        }
    };
    HAL_UART_Init(&uart);
    stdio_huart = &uart;
}

int __io_putchar(int ch)
{
    uint8_t c = ch;
    HAL_UART_Transmit(stdio_huart, &c, 1, 20);
    return c;
}

int __io_getchar(void)
{
    uint8_t c = 0xFF;
    HAL_UART_Receive(stdio_huart, &c, 1, 20);
    return c;
}
