#include "lcd.h"
#include "stack.h"

int add(void) {
   int a;
   int b;
   if (pop(&a) == -1 || pop(&b) == -1) {
      lcdPrintlnS("Underflow");
      return -1;
   }
   push(a + b);
   return 1;
}

int sub(void) {
   int a;
   int b;
   if (pop(&a) == -1 || pop(&b) == -1) {
      lcdPrintlnS("Underflow");
      return -1;
   }
   push(b - a);
   return 1;
}

int mul(void) {
   int a;
   int b;
   if (pop(&a) == -1 || pop(&b) == -1) {
      lcdPrintlnS("Underflow");
      return -1;
   }
   push(a * b);
   return 1;
}

int div(void) {
   int a;
   int b;
   if (pop(&a) == -1 || pop(&b) == -1) {
      lcdPrintlnS("Underflow");
      return -1;
   }
   push(a / b);
   return 1;
}

int p(void) {
   int a;
   return get(get_pointer(), &a);
}

int P(void) {
   int a;
   int b;
   int c;
   int i = get_pointer();
   if (i < 3) {
      lcdPrintlnS("underflow");
      return -1;
   }
   get(i--, &a);
   get(i--, &b);
   get(i, &c);
   return 1;
}

void C(void) { clear(); }

int d(void) {
   int a;
   if (get(get_pointer(), &a) == -1) {
      return -1;
   }
   push(a);
   return 1;
}

int r(void) {
   int a;
   int b;
   if (pop(&a) == -1 || pop(&b) == -1) {
      lcdPrintlnS("underflow");
      return -1;
   }
   push(b);
   push(a);
   return 1;
}
