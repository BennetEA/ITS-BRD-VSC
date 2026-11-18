#include "exception.h"

char *exception_to_string(Exception error) {
   switch (error) {
   case ERR_OK:
      return "Ok";
   case ERR_PHASE_SKIP:
      return "PhaseSkip";
      return "Unknown error";
   }
}
