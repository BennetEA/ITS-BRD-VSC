/**
 * @file    stack.c
 * @author  Bennet Stahmleder, Leon Voss
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor 7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    20.Oktober 2026
 * @brief   Dieses Modul implementiert einen full acending Integer-Stack.
 */
#include "stack.h"

#define HIGHEST_POINTER 10

static int stack[HIGHEST_POINTER + 1];
static int pointer = 0;

Exception push(int val) {
   if (pointer >= HIGHEST_POINTER) {
      return ERR_STACK_FULL;
   }
   stack[++pointer] = val;
   return ERR_OK;
}

Exception pop(int *val) {
   if (pointer <= 0) {
      return ERR_STACK_EMPTY;
   }
   *val = stack[pointer--];
   return ERR_OK;
}

Exception get_element(int index, int *val) {
   if (index > pointer || index <= 0) {
      return ERR_INVALID_INDEX;
   }
   *val = stack[index];
   return ERR_OK;
}

int get_pointer() { return pointer; }

void clear_stack() { pointer = 0; }
