#include "test.h"
#include "encoder.h"
#include "gui.h"
#include "led.h"
#include "phase.h"
#include "timer.h"

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

   double old_time = time(S);
   int i = 0;
   while (1) {
      if (time(S) - old_time >= 1) {
         display_int(i++);
         old_time = time(S);
      }
   }
}

void gui_test() {
   double speed = 0;
   double angel = 0;
   update_display_values(speed, angel);

   init_overlay();
   double old_time = time(MS);
   while (1) {
      update_char();
      if (time(MS) - old_time > 1000) {
         speed += 0.2;
         angel += 0.3;
         update_display_values(speed, angel);
         old_time = time(MS);
      }
   }
}

void encoder_phase_test() {
   Phase old_phase = read_phase();
   int counter;
   Exception err;
   while (1) {
      Phase new_phase = read_phase();
      if (err = update_encoder(new_phase)) {
         set_led(23);
      }
      counter = get_phase_count().count;
      display_int(counter);
      old_phase = new_phase;
   }
}
