#include "funktionen.h"
#include "stack.h"

static int a;
static int b;
static int c;

Error add(void) {
   if (pop(&a) == -1 || pop(&b) == -1) {
      return ERR_STACK_FULL;
   }
   push(a + b);
   return ERR_OK;
}

Error sub(void) {
   if (pop(&a) == -1 || pop(&b) == -1) {
      return ERR_STACK_EMPTY;
   }
   push(b - a);
   return ERR_OK;
}

Error mul(void) {
   if (pop(&a) == -1 || pop(&b) == -1) {
      return ERR_STACK_EMPTY;
   }
   push(a * b);
   return ERR_OK;
}

Error div(void) {
   if (pop(&a) == -1 || pop(&b) == -1) {
      return ERR_STACK_EMPTY;
   }
   if (a == 0) {
      return ERR_DIVISION_BY_ZERO;
   }
   push(b / a);
   return ERR_OK;
}

Error p(void) {
   if (get_element(get_pointer(), &a) == -1) {
      return ERR_STACK_EMPTY;
   }
   return ERR_OK;
}

Error P(void) {
   int i = get_pointer();
   if (i < 3) {
      return ERR_STACK_EMPTY;
   }
   get_element(i--, &a);
   get_element(i--, &b);
   get_element(i, &c);
   return ERR_OK;
}

void C(void) { clear(); }

Error d(void) {
   if (get_element(get_pointer(), &a) == -1) {
      return ERR_STACK_EMPTY;
   }
   push(a);
   return ERR_OK;
}

Error r(void) {
   if (pop(&a) == -1 || pop(&b) == -1) {
      return ERR_STACK_EMPTY;
   }
   push(b);
   push(a);
   return ERR_OK;
}
