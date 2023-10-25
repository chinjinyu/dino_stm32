#include <bsp/oled.h>
#include <bsp/time.h>
#include <stm32g0xx_hal.h>

#include <bsp/oled_font.h>

static const uint8_t oled_config[] = {
    0xAE,               // display off
    0xA8, 0x3F,         // set mux ratio
    0xD3, 0x00,         // set display offset
    0x40,               // set display start line
    0x20, 0x00,         // set memory addressing mode (0x00:H 0x01:V 0x02:Page)
    0x21, 0x00, 0x7F,   // set column address
    0x22, 0x00, 0x07,   // set page address
    0xA1,               // set segment re-map (0xA0/0xA1)
    0xC0,               // set com output scan direction (0xC0/0xC8)
    0xDA, 0x12,         // set com pins hardware configuration
    0x81, 0x7F,         // set contrast control
    0xA4,               // disable entire display on
    0xA6,               // set normal display
    0xD5, 0x80,         // set osc frequency
    0x8D, 0x14,         // enable charge pump regulator
    0xAF,               // display on
};

static SPI_HandleTypeDef *oled_hspi = NULL;
static uint8_t oled_gram[8][128];

void bsp_oled_init(void)
{
    static SPI_HandleTypeDef spi = {
        .Instance = SPI1,
        .Init = {
            .Mode = SPI_MODE_MASTER,
            .DataSize = SPI_DATASIZE_8BIT,
            .FirstBit = SPI_FIRSTBIT_MSB,
            .Direction = SPI_DIRECTION_2LINES,
            .BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8,
            .CLKPhase = SPI_PHASE_1EDGE,
            .CLKPolarity = SPI_POLARITY_LOW,
            .NSS = SPI_NSS_SOFT
        }
    };
    HAL_SPI_Init(&spi);

    // CS  -> PA4
    // RES -> PA0
    // DC  -> PA1
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef gpio_config = {
        .Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW
    };
    HAL_GPIO_Init(GPIOA, &gpio_config);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

    oled_hspi = &spi;

    bsp_oled_reset();
    bsp_oled_write_command(&oled_config[0], sizeof(oled_config));
    bsp_oled_clear();
    bsp_oled_refresh();
}

void bsp_oled_reset(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    bsp_wait_ms(20);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
}

void bsp_oled_write_data(const uint8_t *ptr, uint16_t size)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_SPI_Transmit(oled_hspi, (uint8_t *)ptr, size, 20);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void bsp_oled_write_command(const uint8_t *ptr, uint16_t size)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_SPI_Transmit(oled_hspi, (uint8_t *)ptr, size, 20);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void bsp_oled_refresh(void)
{
    bsp_oled_write_data(&oled_gram[0][0], sizeof(oled_gram));
}

void bsp_oled_clear(void)
{
    for (uint8_t *p = &oled_gram[0][0]; p < &oled_gram[0][0] + sizeof(oled_gram); p++) {
        *p = 0x00;
    }
}

void bsp_oled_draw_point(uint8_t x, uint8_t y, uint8_t c)
{
    uint8_t page = y >> 3;
    uint8_t mask = 1 << (y & 0x07);

    if (c) {
        oled_gram[page][x] |= mask;
    } else {
        oled_gram[page][x] &= ~mask;
    }
}

void bsp_oled_draw_char(uint8_t x, uint8_t y, char c)
{
    uint8_t idx = c - ' ';
    if (idx >= sizeof(ascii_6x8) / sizeof(ascii_6x8[0])) {
        return ;
    }

    for (const uint8_t *p = &ascii_6x8[idx][0]; p < &ascii_6x8[idx + 1][0]; p++, x++) {
        if (x > 127) {
            break;
        }
        for (uint8_t i = 0; i < 8; i++) {
            if (y + i > 63) {
                break;
            }
            bsp_oled_draw_point(x, y + i, *p & (1 << (7 - i)));
        }
    }
}

void bsp_oled_draw_string(uint8_t x, uint8_t y, const char *str)
{
    if (y > 63) {
        return ;
    }

    while (*str) {
        if (x > 127) {
            break;
        }
        bsp_oled_draw_char(x, y, *str++);
        x += 6;
    }
}
