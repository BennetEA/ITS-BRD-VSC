#ifndef LED_U
#define LED_U
#include "exception.h"
#include <stdint.h>

/*
 * LED_REGISTER = GPIOD + GPIOE
 * BUTTON_REGISTER = GPIOF
 */

void display_int(int8_t val);
Exception toggle_led(int led);
Exception set_led(int led);
Exception unset_led(int led);
Exception led_value(int led, int *val);

#endif // !GPIO_U
