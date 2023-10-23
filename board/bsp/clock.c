#include <bsp/clock.h>
#include <stm32g0xx_hal.h>

void bsp_clock_init(void)
{
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitTypeDef osc_config = {
        .OscillatorType = RCC_OSCILLATORTYPE_HSI,
        .HSIState = RCC_HSI_ON,
        .HSIDiv = RCC_HSI_DIV1,
        .HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT,
        .PLL = {
            .PLLState = RCC_PLL_ON,
            .PLLSource = RCC_PLLSOURCE_HSI,
            .PLLM = RCC_PLLM_DIV1,
            .PLLN = 8,
            .PLLP = RCC_PLLP_DIV2,
            .PLLR = RCC_PLLR_DIV2
        }
    };
    HAL_RCC_OscConfig(&osc_config);

    RCC_ClkInitTypeDef clk_config = {
        .ClockType = RCC_CLOCKTYPE_ALL,
        .SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
        .AHBCLKDivider = RCC_SYSCLK_DIV1,
        .APB1CLKDivider = RCC_HCLK_DIV1
    };
    HAL_RCC_ClockConfig(&clk_config, FLASH_LATENCY_2);
}
