/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "calculations.h"
#include "encoder.h"
#include "gui.h"
#include "init.h"
#include "lcd.h"
#include "led.h"
#include "phase.h"
#include "stm32f4xx_hal.h"
#include "test.h"
#include "timer.h"

int main(void) {
   initITSboard();               // Initialisierung des ITS Boards
   GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch

   init_overlay();

   double speed = 0;
   double angel = 0;

   double old_time = 0;
   double _time;

   Exception err;
   update_display_values(speed, angel);

   init_timer();
   init_encoder(read_phase());
   while (1) {
      Phase phase = read_phase();
      if (err = update_encoder(phase)) {
         set_led(21);
      }
      do {
         if (~GPIOF->IDR & 0b1 << 6) {
            reset_timer();
            init_encoder(read_phase());
            calculate(&speed, &angel);
            update_display_values(speed, angel);
            GPIOE->BSRR = 255 << 16;
            err = ERR_OK;
            old_time = 0;
         }
      } while (err);

      display_int(get_phase_count().count);
      _time = time(MS);
      if (_time - old_time >= 300) {
         calculate(&speed, &angel);
         update_display_values(speed, angel);
         old_time = _time;
      }
      update_char();
   }
}

// EOF
