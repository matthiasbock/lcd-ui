
#include <display.h>

// from ushell for debug messages
#include <ushell/syslog.h>


#ifdef STM32CUBE
/**
 * SPI interface configuration handle
 */
SPI_HandleTypeDef display_spi =
{
    Instance: DISPLAY_SPI,
    Init:
    {
        Mode: SPI_MODE_MASTER,
        Direction: SPI_DIRECTION_2LINES,
        DataSize: SPI_DATASIZE_8BIT,
        CLKPolarity: SPI_POLARITY_HIGH,
        CLKPhase: SPI_PHASE_2EDGE,
        NSS: SPI_NSS_HARD_OUTPUT,
        BaudRatePrescaler: SPI_BAUDRATEPRESCALER_64,
        FirstBit: SPI_FIRSTBIT_MSB,
        TIMode: SPI_TIMODE_DISABLE,
        CRCCalculation: SPI_CRCCALCULATION_DISABLE,
    },
};


static inline void display_spi_init()
{
    // TODO: Bring this together with the new DSPI code
    syslog(LOGLEVEL_ERROR, __FILE__, __LINE__, "Failed to initialize SPI1 peripheral.");
    syslog(LOGLEVEL_SUCCESS, __FILE__, __LINE__, "Successfully initialized SPI1 peripheral.");
}


void display_init()
{
    display_spi_init();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = DISPLAY_SCLK_PIN | DISPLAY_MOSI_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DISPLAY_SPI_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DISPLAY_CS_PIN | DISPLAY_RS_PIN | DISPLAY_PWM_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DISPLAY_GPIO_PORT, &GPIO_InitStruct);
}
#endif


#ifdef LIBOPENCM3
static inline void display_spi_init()
{
    // Configure SPI peripheral pins
    gpio_set_af(
            GPIOA,
            GPIO_AF5,
            GPIO5 | GPIO6 | GPIO7
            );

    // Initialize SPI peripheral
    spi_init_master(
            SPI1,
            SPI_CR1_BAUDRATE_FPCLK_DIV_256,
            ?
            );
}


void display_init()
{
    display_spi_init();

    // SPI slave select pin
    gpio_mode_setup(
            GPIOA,
            GPIO_MODE_OUTPUT,
            GPIO_PUPD_NONE,
            GPIO8
            );

    // Configure display backlight control pin
    gpio_mode_setup(
            GPIOB,
            GPIO_MODE_OUTPUT,
            GPIO_PUPD_NONE,
            GPIO5
            );
}


void display_backlight_on()
{
    gpio_clear(
            GPIOB,
            GPIO4
            );
}


void display_backlight_off()
{
    gpio_set(
            GPIOB,
            GPIO4
            );
}
#endif // USE_LIBOPENCM3
