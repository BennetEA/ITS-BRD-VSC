#ifndef STACK_U
#define STACK_U
#include "exception.h"

Exception push(int val);
Exception pop(int *val);
Exception get_element(int index, int *val);
int get_pointer();
void clear_stack();

#endif // !STACK_U
#define STACK_U
