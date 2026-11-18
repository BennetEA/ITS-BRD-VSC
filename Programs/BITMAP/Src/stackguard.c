/**
 ******************************************************************************
 * @file    stackguard.c
 * @brief   Implementierung der Stack-Canary, siehe stackguard.h.
 *
 *          Stack_Mem (Unterkante des Stack-Bereichs) kommt aus der STACK-AREA
 *          in startup_stm32f429xx.s (EXPORT Stack_Mem). Der Stack waechst nach
 *          unten -- ein Overflow schreibt zuerst in die unteren Bytes des
 *          Stack-Bereichs, also genau in die Canary.
 ******************************************************************************
 */

#include "stackguard.h"
#include <stdbool.h>
#include <stdint.h>

/** Fuellmuster der Canary (ein Byte, 0xA5). */
#define STACK_GUARD_PATTERN 0xA5u

/* Unterkante des Stack-Bereichs: Label Stack_Mem aus startup_stm32f429xx.s.
   extern, da das Label im Assembler-File definiert ist. WICHTIG: Dort per
   "EXPORT Stack_Mem" exportieren (ITS_BRD_LIB, STACK-AREA-Block), sonst
   linkt das Modul nicht. */
extern uint8_t Stack_Mem[];

void stack_guard_init(void) {
   for (uint32_t i = 0; i < STACK_GUARD_SIZE; i++) {
      Stack_Mem[i] = (uint8_t)STACK_GUARD_PATTERN;
   }
}

bool stack_guard_check(void) {
   for (uint32_t i = 0; i < STACK_GUARD_SIZE; i++) {
      if (Stack_Mem[i] != (uint8_t)STACK_GUARD_PATTERN) {
         return false; /* Canary zerstoert: Stack-Overflow */
      }
   }
   return true;
}

// EOF
