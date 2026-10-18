#include "functions.h"
#include "stack.h"
#include "terminal.h"
#include <stdio.h>

static int a;
static int b;
static int c;
static char buffer[12];

Exception add() {
   if (get_pointer() < 2) {
      return ERR_STACK_EMPTY;
   }
   pop(&a);
   pop(&b);
   push(a + b);
   return ERR_OK;
}

Exception sub() {
   if (get_pointer() < 2) {
      return ERR_STACK_EMPTY;
   }
   pop(&a);
   pop(&b);
   push(b - a);
   return ERR_OK;
}

Exception mul() {
   if (get_pointer() < 2) {
      return ERR_STACK_EMPTY;
   }
   pop(&a);
   pop(&b);
   push(a * b);
   return ERR_OK;
}

Exception div() {
   if (get_pointer() < 2) {
      return ERR_STACK_EMPTY;
   }
   pop(&a);
   pop(&b);
   if (a == 0) {
      return ERR_DIVISION_BY_ZERO;
   }
   push(b / a);
   return ERR_OK;
}

Exception display_last(Terminal terminal) {
   if (get_pointer() < 1) {
      return ERR_STACK_EMPTY;
   }
   get_element(get_pointer(), &a);
   sprintf(buffer, "%d", a);
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
      sprintf(buffer, "%d", a);
      printTerm(buffer, &terminal);
      printChar(' ', &terminal);
   }
   return ERR_OK;
}

void clear(Terminal terminal) {
   clear_stack();
   clearTerm(&terminal);
}

Exception dupe_last() {
   if (get_pointer() < 1) {
      return ERR_STACK_EMPTY;
   }
   get_element(get_pointer(), &a);
   return push(a);
}

Exception swap_last2() {
   if (get_pointer() < 2) {
      return ERR_STACK_EMPTY;
   }
   pop(&a);
   pop(&b);
   push(a);
   push(b);
   return ERR_OK;
}
