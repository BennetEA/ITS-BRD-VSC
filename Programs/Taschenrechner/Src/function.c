
#include "functions.h"
#include "stack.h"
#include "terminal.h"

#include <limits.h>
#include <stdio.h>

static int a;
static char buffer[12];

Exception add(void) {
   int x, y, result;
   int p = get_pointer();

   if (p < 2) {
      return ERR_INSUFFICIENT_ELEMENTS;
   }

   get_element(p - 1, &x);
   get_element(p, &y);

   if (__builtin_add_overflow(x, y, &result)) {
      return ERR_OVERFLOW;
   }

   pop(&y);
   pop(&x);

   return push(result);
}

Exception sub(void) {
   int x, y, result;
   int p = get_pointer();

   if (p < 2) {
      return ERR_INSUFFICIENT_ELEMENTS;
   }

   get_element(p - 1, &x);
   get_element(p, &y);

   if (__builtin_sub_overflow(x, y, &result)) {
      return ERR_OVERFLOW;
   }

   pop(&y);
   pop(&x);

   return push(result);
}

Exception mul(void) {
   int x, y, result;
   int p = get_pointer();

   if (p < 2) {
      return ERR_INSUFFICIENT_ELEMENTS;
   }

   get_element(p - 1, &x);
   get_element(p, &y);

   if (__builtin_mul_overflow(x, y, &result)) {
      return ERR_OVERFLOW;
   }

   pop(&y);
   pop(&x);

   return push(result);
}

Exception div(void) {
   int x, y, result;
   int p = get_pointer();

   if (p < 2) {
      return ERR_INSUFFICIENT_ELEMENTS;
   }

   get_element(p - 1, &x);
   get_element(p, &y);

   if (y == 0) {
      return ERR_DIVISION_BY_ZERO;
   }

   if (x == INT_MIN && y == -1) {
      return ERR_OVERFLOW;
   }

   result = x / y;

   pop(&y);
   pop(&x);

   return push(result);
}

Exception display_last(Terminal terminal) {
   if (get_pointer() < 1) {
      return ERR_STACK_EMPTY;
   }

   get_element(get_pointer(), &a);
   snprintf(buffer, sizeof(buffer), "%d", a);
   printTerm(buffer, &terminal);

   return ERR_OK;
}

Exception display_last3(Terminal terminal) {
   int p = get_pointer();

   if (p < 1) {
      return ERR_STACK_EMPTY;
   }

   for (int i = (p - 2 < 1) ? 1 : p - 2; i <= p; i++) {
      get_element(i, &a);
      snprintf(buffer, sizeof(buffer), "%d", a);
      printTerm(buffer, &terminal);
      printChar(' ', &terminal);
   }

   return ERR_OK;
}

Exception dupe_last(void) {
   if (get_pointer() < 1) {
      return ERR_STACK_EMPTY;
   }

   get_element(get_pointer(), &a);
   return push(a);
}

Exception swap_last2(void) {
   if (get_pointer() < 2) {
      return ERR_STACK_EMPTY;
   }

   int x, y;

   pop(&y);
   pop(&x);

   push(y);
   push(x);

   return ERR_OK;
}
