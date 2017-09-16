
#include <display.h>
#include <gpio.h>

/**
 * SPI1
 * ====
 * SCLK: D13 / PA5
 * MISO: D12 / PA6
 * MOSI: D11 / PA7
 * CS:   D7  / PA8
 *
 * Backlight:
 * D5 / PB4
 */

void display_init()
{
    // Configure SPI peripheral pins
    gpio_set_af(
            GPIOA,
            GPIO_AF5,
            GPIO5 | GPIO6 | GPIO7
            );
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
    gpio_set(
            GPIOB,
            GPIO4
            );
}


void display_backlight_off()
{
    gpio_clear(
            GPIOB,
            GPIO4
            );
}
