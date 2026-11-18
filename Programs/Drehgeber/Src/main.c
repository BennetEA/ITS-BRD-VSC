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

#define ERROR_LED 21
#define RESET_BUTTON_MASK (1U << 6U)
#define GPIOE_LED_MASK 255U
#define GPIO_RESET_SHIFT 16U
#define DISPLAY_UPDATE_INTERVAL_MS 300

int main(void) {
   initITSboard();               // Initialisierung des ITS Boards
   GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch

   init_overlay();

   Angular_values values = {.speed = 0, .angle = 0};

   double old_time = 0;
   double current_time;

   Exception err;
   update_display_values(values);

   init_timer();
   init_encoder(read_phase());
   while (1) {
      Phase phase = read_phase();
      err = update_encoder(phase);
      if (err != ERR_OK) {
         set_led(ERROR_LED);
      }
      do {
         if (~GPIOF->IDR & RESET_BUTTON_MASK) {
            reset_timer();
            init_encoder(read_phase());
            calculate(&values);
            update_display_values(values);
            GPIOE->BSRR = GPIOE_LED_MASK << GPIO_RESET_SHIFT;
            err = ERR_OK;
            old_time = 0;
         }
      } while (err);

      display_int((int8_t)get_phase_count().count);
      current_time = time(MS);
      if (current_time - old_time >= DISPLAY_UPDATE_INTERVAL_MS) {
         calculate(&values);
         update_display_values(values);
         old_time = current_time;
      }
      update_char();
   }
}

// EOF
