/**
 * This file contains generic functions
 * to access the attached display
 * and implements them in a
 * display-specific manner.
 */

#ifndef DISPLAY_H

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
