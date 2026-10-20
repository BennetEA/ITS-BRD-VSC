/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf, Bennet Stahmleder, Leon Voss
 * @brief   main Programm für Taschenrechner in umgekehrter polnischer Notation.
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

Terminal overlay;

int main(void) {
   initITSboard(); // Initialisierung des ITS Boards
   overlay = init_display_term();
   setTextColorTerm(BLACK, &overlay);
   while (1) {
      token = next_token();
      if (is_bottom_line()) {
         clearTerm(&overlay);
      }
      switch (token.tok) {
      case NUMBER:
         if (error = push(token.val)) {
            setTextColorTerm(RED, &overlay);
            printTerm(exception_to_string(error), &overlay);
            setTextColorTerm(BLACK, &overlay);
         }
         break;
      case PLUS:
         if (error = add()) {
            setTextColorTerm(RED, &overlay);
            printTerm(exception_to_string(error), &overlay);
            setTextColorTerm(BLACK, &overlay);
         }
         break;
      case MINUS:
         if (error = sub()) {
            setTextColorTerm(RED, &overlay);
            printTerm(exception_to_string(error), &overlay);
            setTextColorTerm(BLACK, &overlay);
         }
         break;
      case MULT:
         if (error = mul()) {
            setTextColorTerm(RED, &overlay);
            printTerm(exception_to_string(error), &overlay);
            setTextColorTerm(BLACK, &overlay);
         }
         break;
      case DIV:
         if (error = div()) {
            setTextColorTerm(RED, &overlay);
            printTerm(exception_to_string(error), &overlay);
            setTextColorTerm(BLACK, &overlay);
         }
         break;
      case PRT:
         if (error = display_last(&overlay)) {
            setTextColorTerm(RED, &overlay);
            printTerm(exception_to_string(error), &overlay);
            setTextColorTerm(BLACK, &overlay);
         }
         break;
      case SWAP:
         if (error = swap_last2()) {
            setTextColorTerm(RED, &overlay);
            printTerm(exception_to_string(error), &overlay);
            setTextColorTerm(BLACK, &overlay);
         }
         break;
      case PRT_ALL:
         if (error = display_last3(&overlay)) {
            setTextColorTerm(RED, &overlay);
            printTerm(exception_to_string(error), &overlay);
            setTextColorTerm(BLACK, &overlay);
         }
         break;
      case CLEAR:
         clearTerm(&overlay);
         clear_stack();
         break;
      case DOUBLE:
         if (error = dupe_last()) {
            setTextColorTerm(RED, &overlay);
            printTerm(exception_to_string(error), &overlay);
            setTextColorTerm(BLACK, &overlay);
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
   }
}

// EOF
