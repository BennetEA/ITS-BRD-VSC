/**
 * @file    exception.c
 * @author  Bennet Stahmleder, Leon Voss
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor 7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    20.Oktober 2026
 * @brief   Dieses Modul implementiert Fehlercode verarbeitung.
 */
#include "exception.h"

char *exception_to_string(Exception error) {
   switch (error) {
   case ERR_OK:
      return "OK";
   case ERR_STACK_FULL:
      return "STACK_FULL\nSTACK_UNCHANGED\n";
   case ERR_STACK_EMPTY:
      return "STACK_EMPTY\nSTACK_UNCHANGED\n";
   case ERR_INVALID_INDEX:
      return "INVALID_INDEX\nSTACK_UNCHANGED\n";
   case ERR_DIVISION_BY_ZERO:
      return "DIVISON_BY_ZERO\nSTACK_UNCHANGED\n";
   case ERR_OVERFLOW:
      return "OVERFLOW\nSTACK_UNCHANGED\n";
   case ERR_INSUFFICIENT_ELEMENTS:
      return "INSUFFICIENT-ELEMENTS\nFOR_CALCULATION\nSTACK_UNCHANGED\n";
   }
}
