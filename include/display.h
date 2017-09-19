/**
 * This file contains generic functions
 * to access the attached display
 * and implements them in a
 * display-specific manner.
 */

#ifndef DISPLAY_H

// for SPI and GPIO handling
#include <stm32f4xx.h>


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
#define backlight_on()      HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY_PWM_PIN, GPIO_PIN_RESET);

/**
 * Turn off the display's backlight.
 */
#define backlight_off()     HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY_PWM_PIN, GPIO_PIN_SET);

/**
 * Set RS to 1
 */
#define LCD_RS_H()  HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY_RS_PIN, GPIO_PIN_SET);

/**
 * Set RS 0
 */
#define LCD_RS_L()  HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY_RS_PIN, GPIO_PIN_RESET);

/**
 * Set CS to 1
 */
#define LCD_CS_H()  HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY_CS_PIN, GPIO_PIN_SET);

/**
 * Set CS to 0
 */
#define LCD_CS_L()  HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY_CS_PIN, GPIO_PIN_RESET);

#endif // DISPLAY_H
