#include "stack.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_SIZE 10

static int pointer = 0;
static int set[MAX_SIZE + 1];

int push(int val) {
   if (++pointer < MAX_SIZE) {
      set[pointer] = val;
      return 1;
   }
   return -1;
}

int pop(int *val) {
   if (pointer < 1) {
      return -1;
   }
   *val = set[pointer];
   pointer--;
   return 1;
}

int get(int index, int *val) {
   if (index > pointer || index < 1) {
      return -1;
   }
   *val = set[index];
   return 1;
}

int get_pointer(void) { return pointer; }

int clear(void) { pointer = 0; }
