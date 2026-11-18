#include "led.h"
#include "exception.h"
#include "init.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include <stdint.h>

#define GPIOD_START 8
#define GPIOD_END 15
#define GPIOE_START 16
#define GPIOE_END 23
#define GPIOF_START 0
#define GPIOF_END 7
#define GPIO_RESET_SHIFT 16U
#define GPIOD_RESET_OFFSET 8U

void display_int(int8_t val) {
   GPIOD->BSRR = (uint32_t)(int32_t)val;
   GPIOD->BSRR = ~(uint32_t)(int32_t)val << GPIO_RESET_SHIFT;
}
Exception toggle_led(int led) {
   if (led < GPIOD_START || led > GPIOE_END) {
      return ERR_INVALID_LED;
   }

   int val;
   Exception err = led_value(led, &val);
   if (err != ERR_OK) {
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
      GPIOE->BSRR = 0x01U << ((uint32_t)(led - GPIOE_START));
   } else {
      GPIOD->BSRR = 0x01U << ((uint32_t)(led - GPIOD_START));
   }

   return ERR_OK;
}

Exception unset_led(int led) {
   if (led < GPIOD_START || led > GPIOE_END) {
      return ERR_INVALID_LED;
   }

   if (led > GPIOD_END) {
      GPIOE->BSRR = 0x01U << (uint32_t)led;
   } else {
      GPIOD->BSRR = 0x01U << ((uint32_t)led + GPIOD_RESET_OFFSET);
   }

   return ERR_OK;
}

Exception led_value(int led, int *val) {
   if (led < 0 || led > GPIOE_END) {
      return ERR_INVALID_LED;
   }
   if (led > GPIOD_END) {
      *val = (int)((GPIOE->IDR & (0x01U << ((uint32_t)(led - GPIOE_START)))) >>
                   ((uint32_t)(led - GPIOE_START)));
   } else {
      *val = (int)((GPIOD->IDR & (0x01U << ((uint32_t)(led - GPIOD_START)))) >>
                   ((uint32_t)(led - GPIOD_START)));
   }

   return ERR_OK;
}
