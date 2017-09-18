/**
 * This file contains generic functions
 * to access the attached display
 * and implements them in a
 * display-specific manner.
 */

#ifndef DISPLAY_H

/**
 * SPI1
 * ====
 * SCLK: D13 / PA5
 * MISO: n.c.
 * MOSI: D11 / PA7
 * CS:   D5 / PB4
 * RS:   D4 / PB5
 *
 * Backlight:
 * A3 / PB0
 */
#define DISPLAY_SPI         SPI1

#define DISPLAY_SPI_PORT    GPIOA
#define DISPLAY_SCLK_PIN    GPIO_PIN_5
#define DISPLAY_MOSI_PIN    GPIO_PIN_7

#define DISPLAY_GPIO_PORT   GPIOB
#define DISPLAY_CS_PIN      GPIO_PIN_4
#define DISPLAY_RS_PIN      GPIO_PIN_5
#define DISPLAY_PWM_PIN     GPIO_PIN_0


/**
 * Initialize the pins used to communicate with the display
 * and the display itself.
 */
void display_init();

/**
 * Turn on the display's backlight.
 */
void display_backlight_on();

/**
 * Turn off the display's backlight.
 */
void display_backlight_on();

#endif // DISPLAY_H
