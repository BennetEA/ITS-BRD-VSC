/**
 * @file    function.c
 * @author  Bennet Stahmleder, Leon Voss
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor 7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    20.Oktober 2026
 * @brief   Dieses Modul implementiert Funktionen, eines Taschenrechners,
 *          in Umgekehrter polnischer Notation.
 */
#include "functions.h"
#include "stack.h"
#include "terminal.h"

#include <limits.h>
#include <stdio.h>

static char buffer[12];

Exception get2(int *x, int *y) {
   int e;
   if (e = pop(y)) {
      return e;
   }
   if (e = pop(x)) {
      push(*y);
      return e;
   }
   return ERR_OK;
}
Exception add(void) {
   int e, x, y, result;
   if (e = get2(&x, &y)) {
      return e;
   }
   if (__builtin_add_overflow(x, y, &result)) {
      return ERR_OVERFLOW;
   }
   return push(result);
}

Exception sub(void) {
   int e, x, y, result;
   if e = (get2(&x, &y)) {
      return e;
   }
   if (__builtin_sub_overflow(x, y, &result)) {
      return ERR_OVERFLOW;
   }
   return push(result);
}

Exception mul(void) {
   int e, x, y, result;
   if (e = get2(&x, &y)) {
      return e;
   }
   if (__builtin_mul_overflow(x, y, &result)) {
      return ERR_OVERFLOW;
   }
   return push(result);
}

Exception div(void) {
   int e, x, y, result;
   if (e = get2(&x, &y)) {
      return e;
   }
   if (y == 0) {
      return ERR_DIVISION_BY_ZERO;
   }
   if (x == INT_MIN && y == -1) {
      return ERR_OVERFLOW;
   }
   result = x / y;
   return push(result);
}

Exception display_last(Terminal *terminal) {
   int d;
   int e;
   if (e = pop(&d)) {
      return e;
   }
   snprintf(buffer, sizeof(buffer), "%d", d);
   push(d);
   printTerm(buffer, terminal);
   printTerm("\n", terminal);
   return ERR_OK;
}

Exception display_last3(Terminal *terminal) {
   int x[3];
   int i;
   for (i = 0; i < 3; i++) {
      if (pop(&x[i])) {
         break;
      }
   }
   if (i == 0) {
      return ERR_STACK_EMPTY;
   }
   for (i = i - 1; i >= 0; i--) {
      snprintf(buffer, sizeof(buffer), "%d", x[i]);
      push(x[i]);
      printTerm(buffer, terminal);
      printChar(' ', terminal);
   }
   printTerm("\n", terminal);
   return ERR_OK;
}

Exception dupe_last(void) {
   int x;
   int e;
   if (e = pop(&x)) {
      return e;
   }
   push(x);
   return push(x);
}

Exception swap_last2(void) {
   int x, y;
   get2(&x, &y);
   push(y);
   push(x);
   return ERR_OK;
}
