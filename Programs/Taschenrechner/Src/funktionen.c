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
   return 0;
}

int sub(void) {
   int a;
   int b;
   if (pop(&a) == -1 || pop(&b) == -1) {
      lcdPrintlnS("Underflow");
      return -1;
   }
   push(b - a);
   return 0;
}

int mul(void) {
   int a;
   int b;
   if (pop(&a) == -1 || pop(&b) == -1) {
      lcdPrintlnS("Underflow");
      return -1;
   }
   push(a * b);
   return 0;
}

int div(void) {
   int a;
   int b;
   if (pop(&a) == -1 || pop(&b) == -1) {
      lcdPrintlnS("Underflow");
      return -1;
   }
   push(b / a);
   return 0;
}

int p(void) {
   int a;
   if (get_element(get_pointer(), &a) == -1) {
      return -1;
   }
   lcdPrintInt(a);
   return 0;
}

int P(void) {
   int i = get_pointer();
   if (i < 3) {
      return -1;
   }
   int a;
   int b;
   int c;
   get_element(i--, &a);
   get_element(i--, &b);
   get_element(i, &c);
   lcdPrintInt(a);
   lcdPrintC(' ');
   lcdPrintInt(b);
   lcdPrintC(' ');
   lcdPrintInt(c);
   return 0;
}

void C(void) { clear(); }

int d(void) {
   int a;
   if (get_element(get_pointer(), &a) == -1) {
      return -1;
   }
   push(a);
   return 0;
}

int r(void) {
   int a;
   int b;
   if (pop(&a) == -1 || pop(&b) == -1) {
      return -1;
   }
   push(b);
   push(a);
   return 0;
}
