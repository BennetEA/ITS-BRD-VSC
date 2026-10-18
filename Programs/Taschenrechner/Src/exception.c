#include "exception.h"

char *exception_to_string(Exception error) {
   switch (error) {
   case ERR_OK:
      return "OK";
   case ERR_STACK_FULL:
      return "STACK_FULL";
   case ERR_STACK_EMPTY:
      return "ERR_STACK_EMPTY";
   case ERR_INVALID_INDEX:
      return "INVALID_INDEX";
   case ERR_DIVISION_BY_ZERO:
      return "DIVISON_BY_ZERO";
   }
}
