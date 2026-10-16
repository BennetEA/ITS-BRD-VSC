#include "stack.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_SIZE 10

static int pointer = 0;
static int stack[MAX_SIZE + 1];

int push(int val) {
   if (pointer < MAX_SIZE) {
      stack[++pointer] = val;
      return 0;
   }
   return -1;
}

int *stack_addr(void) { return &stack[0]; }
int pop(int *val) {
   if (pointer < 1) {
      return -1;
   }
   *val = stack[pointer--];
   return 0;
}

int get_element(int index, int *val) {
   if (index > pointer || index < 1) {
      return -1;
   }
   *val = stack[index];
   return 0;
}

int get_pointer(void) { return pointer; }

void clear(void) { pointer = 0; }
