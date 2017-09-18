
// HAL_Delay
#include <stm32f4xx.h>

// for SystemClock_Config
#include <clock.h>

// for display control
#include <display.h>


void main()
{
    SystemClock_Config();

    display_init();

    while (1)
    {
        display_backlight_on();
        HAL_Delay(1000);
        display_backlight_off();
        HAL_Delay(1000);
    }
}
