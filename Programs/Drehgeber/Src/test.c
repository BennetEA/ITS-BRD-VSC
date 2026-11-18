#include "test.h"
#include "encoder.h"
#include "gui.h"
#include "led.h"
#include "phase.h"
#include "timer.h"

#define FIRST_TEST_LED 8
#define LAST_TEST_LED 23
#define GUI_TEST_INTERVAL_MS 1000
#define TEST_SPEED_INCREMENT 0.2
#define TEST_ANGLE_INCREMENT 0.3

void gpio_test() {
   for (int i = FIRST_TEST_LED; i <= LAST_TEST_LED; i++) {
      set_led(i);
   }
   for (int i = FIRST_TEST_LED; i <= LAST_TEST_LED; i++) {
      unset_led(i);
   }

   for (int i = FIRST_TEST_LED; i <= LAST_TEST_LED; i++) {
      toggle_led(i);
   }

   for (int i = FIRST_TEST_LED; i <= LAST_TEST_LED; i++) {
      toggle_led(i);
   }

   double old_time = time(S);
   int i = 0;
   while (1) {
      if (time(S) - old_time >= 1) {
         display_int((int8_t)i++);
         old_time = time(S);
      }
   }
}

void gui_test() {
   Angular_values values = {.speed = 0, .angle = 0};
   update_display_values(values);

   init_overlay();
   double old_time = time(MS);
   while (1) {
      update_char();
      if (time(MS) - old_time > GUI_TEST_INTERVAL_MS) {
         values.speed += TEST_SPEED_INCREMENT;
         values.angle += TEST_ANGLE_INCREMENT;
         update_display_values(values);
         old_time = time(MS);
      }
   }
}

void encoder_phase_test() {
   (void)read_phase();
   int counter;
   while (1) {
      Phase new_phase = read_phase();
      if (update_encoder(new_phase) != ERR_OK) {
         set_led(LAST_TEST_LED);
      }
      counter = get_phase_count().count;
      display_int((int8_t)counter);
   }
}
