/**
 * @file    stack.h
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

#ifndef STACK_U
#define STACK_U
#include "exception.h"

/**
 * @brief        Diese Funktion fügt dem Stack ein Element hinzu.
 * @param val    Integer der auf dem Stack gespeichert wird.
 * @retval       Statuscode der Funktion.
 */
Exception push(int val);
/**
 * @brief        Diese Funktion entnimmt dem Stack ein Element.
 * @param val    Pointer an dem der entnommende Integer gespeichert wird.
 * @retval       Statuscode der Funktion.
 */
Exception pop(int *val);
/**
 * @brief        Diese Funktion liest ein Integer aus dem Stack.
 * @param index  Index des Itegers, welcher zurückgegeben werden soll.
 * @param val    Integer der auf dem Stack gespeichert wird.
 * @retval       Statuscode der Funktion.
 */
Exception get_element(int index, int *val);
/**
 * @brief        Diese Funktion liefert den Stackpointer.
 * @retval       Stackpointer.
 */
int get_pointer();
/**
 * @brief        Diese Funktion setzt den Stackpointer auf 0.
 * @retval       None
 */
void clear_stack();

#endif // !STACK_U
