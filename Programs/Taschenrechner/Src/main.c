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
#include "display.h"
#include "funktionen.h"
#include "init.h"
#include "keypad.h"
#include "lcd.h"
#include "scanner.h"
#include "stm32f4xx_hal.h"
#include "terminal.h"
#include "test.h"
#include "token.h"

int main(void) {
   initITSboard();               // Initialisierung des ITS Boards
   GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
   TP_Init(false);               // Initialisierung des LCD Boards mit Touch

   const int POLL_DELAY = 10000;
   while (1) {
      HAL_Delay(POLL_DELAY);
   }
}

void calc(Token_t token)

    // EOF
