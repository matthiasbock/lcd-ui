
// HAL_Delay
#include <stm32f4xx.h>

// for SystemClock_Config
#include <clock.h>

// for display control
#include <display.h>

// LCD
//#include <BD663474.h>


void main()
{
    SystemClock_Config();

    display_init();

//    BD663474 lcd;

    while (1)
    {
        backlight_on();
        HAL_Delay(1000);
        backlight_off();
        HAL_Delay(1000);
    }
}
