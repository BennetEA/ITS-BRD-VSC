/**
 * @file    function.h
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
#ifndef FUNCTIONS_U
#define FUNCTIONS_U
#include "exception.h"
#include "terminal.h"

/**
 * @brief           Diese Funktion entnimmt dem Stack die letzten beiden
 *                  Integers und legt dessen Summe wieder auf den Stack.
 *                  Bei Fehlschlag wird der Stack nicht veränder.
 * @retval          Statuscode der Funktion.
 */
Exception add();
/**
 * @brief           Diese Funktion entnimmt dem Stack die letzten beiden
 *                  Integers und legt dessen Differnzwert wieder auf den Stack.
 *                  Bei Fehlschlag wird der Stack nicht veränder.
 * @retval          Statuscode der Funktion.
 */
Exception sub();
/**
 * @brief           Diese Funktion entnimmt dem Stack die letzten beiden
 *                  Integers und legt dessen Produkt wieder auf den Stack.
 *                  Bei Fehlschlag wird der Stack nicht veränder.
 * @retval          Statuscode der Funktion.
 */
Exception mul();
/**
 * @brief           Diese Funktion entnimmt dem Stack die letzten beiden
 *                  Integers und legt dessen Quotient wieder auf den Stack. 
 *                  Bei Fehlschlag wird der Stack nicht veränder.
 * @retval          Statuscode der Funktion.
 */
Exception div();
/**
 * @brief           Diese Funktion liest den letzten Integer auf dem Stack aus
 *                  und druckt dessen Wert auf ein Terminal.
 * @param *terminal Pointer des Terminal auf dem der Wert ausgegeben wird.
 * @retval          Statuscode der Funktion.
 */
Exception display_last(Terminal *terminal);
/**
 * @brief          Diese Funktion liest die letzten Integers auf dem Stack aus,
 *                  bis zu maximal 3 und drukt dessen Werte auf ein Terminal.
 * @param *terminal Pointer des Terminal auf dem der Wert ausgegeben wird.
 * @retval          Statuscode der Funktion.
 */
Exception display_last3(Terminal *terminal);
/**
 * @brief           Diese Funktion löscht alle Ausgaben auf einem Terminal
 *                  und setzt den Stackpointer auf 0.
 * @param *terminal Pointer des Terminal dessen Ausgaben gelöscht werden.
 * @retval          Statuscode der Funktion.
 */
void clear(Terminal *terminal);
/**
 * @brief           Diese Funktion kopiert den letzten Integer auf dem Stack
 *                  und legt die Kopie auf dem Stack ab.
 * @retval          Statuscode der Funktion.
 */
Exception dupe_last();
/**
 * @brief           Diese Funktion tauscht den Index der letzten Beiden Integer
 * @retval          Statuscode der Funktion.
 */
Exception swap_last2();

#endif // !FUNCTIONS_U
#define FUNCTIONS_U
