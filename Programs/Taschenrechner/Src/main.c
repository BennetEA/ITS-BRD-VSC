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
#include "exception.h"
#include "functions.h"
#include "init.h"
#include "keypad.h"
#include "lcd.h"
#include "scanner.h"
#include "stack.h"
#include "stm32f4xx_hal.h"
#include "terminal.h"
#include "test.h"
#include "token.h"

static int error;
static T_token token;

int test_main(void) {
   initITSboard();               // Initialisierung des ITS Boards
   GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
   test_stack();
}
int main(void) {
   initITSboard();               // Initialisierung des ITS Boards
   GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
   init_display();
   TP_Init(false); // Initialisierung des LCD Boards mit Touch
   const int POLL_DELAY = 100;

   Terminal overlay = makeKeyPad();
   while (1) {
      token = next_token();
      switch (token.tok) {
      case NUMBER:
         if (error = push(token.val)) {
            printTerm(exception_to_string(error), &overlay);
         }
         break;
      case PLUS:
         if (error = add()) {
            printTerm(exception_to_string(error), &overlay);
         }
         break;
      case MINUS:
         if (error = sub()) {
            printTerm(exception_to_string(error), &overlay);
         }
         break;
      case MULT:
         if (error = mul()) {
            printTerm(exception_to_string(error), &overlay);
         }
         break;
      case DIV:
         if (error = div()) {
            printTerm(exception_to_string(error), &overlay);
         }
         break;
      case PRT:
         if (error = display_last(overlay)) {
            printTerm(exception_to_string(error), &overlay);
         }
         break;
      case SWAP:
         if (error = swap_last2()) {
            printTerm(exception_to_string(error), &overlay);
         }
         break;
      case PRT_ALL:
         if (error = display_last3(overlay)) {
            printTerm(exception_to_string(error), &overlay);
         }
         break;
      case CLEAR:
         clear(overlay);
         break;
      case DOUBLE:
         if (error = dupe_last()) {
            printTerm(exception_to_string(error), &overlay);
         }
         break;
      case ENTER:
         continue;
         break;
      case UNEXPECTED:
         continue;
         break;
      case OVERFLOW:
         continue;
         break;
      }
      // HAL_Delay(POLL_DELAY);
   }
}

// EOF
