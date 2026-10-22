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
         error = push(token.val);
         break;
      case PLUS:
         error = add();
         break;
      case MINUS:
         error = sub();
         break;
      case MULT:
         error = mul();
         break;
      case DIV:
         error = div();
         break;
      case PRT:
         error = display_last(&overlay);
         break;
      case SWAP:
         error = swap_last2();
         break;
      case PRT_ALL:
         error = display_last3(&overlay);
         break;
      case CLEAR:
         clearTerm(&overlay);
         clear_stack();
         break;
      case DOUBLE:
         error = dupe_last();
         break;
      default:
         setTextColorTerm(RED, &overlay);
         printTerm("USELESS_BUTTON\n", &overlay);
         setTextColorTerm(BLACK, &overlay);
         break;
      }
      if(error) {
            setTextColorTerm(RED, &overlay);
            printTerm(exception_to_string(error), &overlay);
            setTextColorTerm(BLACK, &overlay);
      }
   }
}

// EOF
