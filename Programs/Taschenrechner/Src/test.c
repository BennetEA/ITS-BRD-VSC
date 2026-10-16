#include "funktionen.h"
#include "lcd.h"
#include "stack.h"
#include <stdint.h>
#include <stdio.h>

#define LIM 12

void clear_display(void) {
   lcdGotoXY(0, 0);
   for (int i = 0; i <= 16; i++) {
      lcdPrintlnS(" ");
   }
   lcdGotoXY(0, 0);
}

void test_stack(void) {
   int *addr = stack_addr();
   for (int i = 0; i <= LIM; i++) {
      push(i);
   }
   int erg;
   for (int i = 0; i <= LIM; i++) {
      pop(&erg);
   }
}

void test_funktionen(void) {
   int erg;
   int *addr = stack_addr();
   // Addition
   // Subtraktion
   // Multiplikation
   // Division
   // p
   clear_display();
   lcdPrintlnS("p (push):");
   for (int i = 0; i <= LIM; i++) {
      push(i);
      p();
   }
   lcdPrintlnS(" ");
   lcdPrintlnS("p (pop):");
   for (int i = 0; i <= LIM; i++) {
      pop(&erg);
      p();
   }
   // P
   clear_display();
   lcdPrintlnS("P (push):");
   for (int i = 0; i <= LIM; i++) {
      push(i);
      P();
      lcdPrintlnS(" ");
   }
   clear_display();
   lcdPrintReplS("P (pop):");
   for (int i = 0; i <= LIM; i++) {
      pop(&erg);
      P();
      lcdPrintlnS(" ");
   }

   // d
   // r
}
