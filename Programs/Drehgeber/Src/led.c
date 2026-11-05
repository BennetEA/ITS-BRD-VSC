#include "exception.h"
#include "init.h"
#include "led.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include <stdint.h>

#define GPIOD_START 8
#define GPIOD_END 15
#define GPIOE_START 16
#define GPIOE_END 23
#define GPIOF_START 0
#define GPIOF_END 7

void display_int(int8_t val) {
   GPIOD->BSRR = val;
   GPIOD->BSRR = ~val << 16;
}
Exception toggle_led(int led) {
   if (led < GPIOD_START || led > GPIOE_END) {
      return ERR_INVALID_LED;
   }

   int val;
   int err;
   if ((err = led_value(led, &val))) {
      return err;
   }
   if (val) {
      return unset_led(led);
   }
   return set_led(led);
}

Exception set_led(int led) {
   if (led < GPIOD_START || led > GPIOE_END) {
      return ERR_INVALID_LED;
   }
   if (led > GPIOD_END) {
      GPIOE->BSRR = 0x01U << (led - GPIOE_START);
   } else {
      GPIOD->BSRR = 0x01U << (led - GPIOD_START);
   }

   return ERR_OK;
}

Exception unset_led(int led) {
   if (led < GPIOD_START || led > GPIOE_END) {
      return ERR_INVALID_LED;
   }

   if (led > GPIOD_END) {
      GPIOE->BSRR = 0x01U << led;
   } else {
      GPIOD->BSRR = 0x01U << (led + 8);
   }

   return ERR_OK;
}

Exception led_value(int led, int *val) {
   if (led < 0 || led > GPIOE_END) {
      return ERR_INVALID_LED;
   }
   if (led > GPIOD_END) {
      *val =
          (GPIOE->IDR & (0x01U << (led - GPIOE_START))) >> (led - GPIOE_START);
   } else {
      *val =
          (GPIOD->IDR & (0x01U << (led - GPIOD_START))) >> (led - GPIOD_START);
   }

   return ERR_OK;
}

Exception button_value(int button, int *val) {
   if (button < GPIOF_START || button > GPIOF_END) {
      return ERR_INVALID_BUTTON;
   }
   *val = (GPIOF->IDR & (0x01U << button)) >> button;
   return ERR_OK;
}
