#include "test.h"
#include "led.h"

void gpio_test() {
   for (int i = 8; i <= 23; i++) {
      set_led(i);
   }
   for (int i = 8; i <= 23; i++) {
      unset_led(i);
   }

   for (int i = 8; i <= 23; i++) {
      toggle_led(i);
   }

   for (int i = 8; i <= 23; i++) {
      toggle_led(i);
   }
}
