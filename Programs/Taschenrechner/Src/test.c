#include "display.h"
#include "stack.h"
#include "terminal.h"

#define STACK_TEST_RANGE 12

static int error;

void test_stack(void) {
   init_display();
   int a;
   for (int i = 0; i <= STACK_TEST_RANGE; i++) {
      if (error = push(i)) {
         print_stdout(exception_to_string(error));
      }
      get_element(get_pointer(), &a);
   }
   for (int i = 0; i <= STACK_TEST_RANGE; i++) {
      if (error = pop(&a)) {
         print_stdout(exception_to_string(error));
      }
   }
}
