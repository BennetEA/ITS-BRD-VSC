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
#include "init.h"
#include "lcd.h"
#include "led.h"
#include "stm32f4xx_hal.h"
#include "test.h"
#include "timer.h"

int main(void) {
   initITSboard(); // Initialisierung des ITS Boards
   // GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
   // TP_Init(false); // Initialisierung des LCD Boards mit Touch

   init_timer();
   double old_time = time('s');
   while (1) {
      display_int((int)time(S));
   }
}

// EOF
