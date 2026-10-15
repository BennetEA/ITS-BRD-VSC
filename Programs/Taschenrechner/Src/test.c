#include "stack.h"
#include <stdio.h>

void test_stack(void) {
   push(1);
   push(2);
   push(3);
   push(4);

   int erg;
   get(1, &erg); // erwartet 1
   get(2, &erg); // erwartet 2
   get(3, &erg); // erwartet 3
   get(4, &erg); // erwartet 4
   pop(&erg);    // erwartet 4
   pop(&erg);    // erwartet 3
   pop(&erg);    // erwartet 2
   pop(&erg);    // erwartet 1
   pop(&erg);    // erwartet 1
}
