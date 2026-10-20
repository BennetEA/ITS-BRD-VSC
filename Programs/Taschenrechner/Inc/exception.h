/**
 * @file    exception.h
 * @author  Bennet Stahmleder, Leon Voss
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor 7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    20.Oktober 2026
 * @brief   Dieses Modul implementiert Fehlercode verarbeitung.
 */
#ifndef EXCEPTION_U
#define EXCEPTION_U

typedef enum {
   ERR_OK = 0,
   ERR_STACK_FULL,
   ERR_STACK_EMPTY,
   ERR_INSUFFICIENT_ELEMENTS,
   ERR_INVALID_INDEX,
   ERR_DIVISION_BY_ZERO,
   ERR_OVERFLOW,
} Exception;

/**
 * @brief        Diese Funktion wandelt Fehlercode in Strings um.
 * @param error  Zu verabeitender Fehlercode.
 * @retval       Fehlercode als String.
 */
char *exception_to_string(Exception error);

#endif // !EXCEPTION_U
#define EXCEPTION_U
