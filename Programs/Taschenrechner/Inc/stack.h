#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
/*
 * Stack eigenschaften:
 * - Acending
 * - increment before
 * - decrement after
 */
int push(int val);            // legt val auf dem Stack ab
int pop(int *val);            // gibt das oberste Element des Stacks zurück
int get(int index, int *val); // gibt das element am index zurück
int clear(void);              // setzt den stackpointer zurück
int get_pointer(void);        // gibt den aktuellen stackpointer zurück
#endif                        // !STACH_H
