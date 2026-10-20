#include "exception.h"

char *exception_to_string(Exception error) {
   switch (error) {
   case ERR_OK:
      return "OK";
   case ERR_STACK_FULL:
      return "STACK_FULL\nSTACK_UNCHANGED";
   case ERR_STACK_EMPTY:
      return "STACK_EMPTY\nSTACK_UNCHANGED";
   case ERR_INVALID_INDEX:
      return "INVALID_INDEX\nSTACK_UNCHANGED";
   case ERR_DIVISION_BY_ZERO:
      return "DIVISON_BY_ZERO\nSTACK_UNCHANGED";
   case ERR_OVERFLOW:
      return "OVERFLOW\nSTACK_UNCHANGED";
   case ERR_INSUFFICIENT_ELEMENTS:
      return "INSUFFICIENT-\nELEMENTS\nFOR_CALCULATION\nSTACK_UNCHANGED";
   }
}
