#include "error.h"

const char *error_to_String(Error error) {
   switch (error) {
   case ERR_OK:
      return "OK";
   case ERR_STACK_FULL:
      return "STACK OVERFLOW";
   case ERR_STACK_EMPTY:
      return "STACK UNDERFLOW";
   case ERR_INVALID_INDEX:
      return "OUT OF BOUND INDEX";
   case ERR_DIVISION_BY_ZERO:
      return "DIVISION BY ZERO";
   }
}
