/**
 ******************************************************************************
 * @file    stackguard.h
 * @brief   Stack-Canary am unteren Ende des Stack-Bereichs.
 *
 *          Problem: Der Stack waechst von __initial_sp nach unten. Laeuft er
 *          ueber die Unterkante (Stack_Mem) hinaus, landen die Schreibzugriffe
 *          lautlos im .bss darunter (z. B. USB-Handle, Ringpuffer) -- die
 *          Korruption bleibt lange unbemerkt (vgl. Incident 11/2026:
 *          Stack-Overflow durch pix_buf[255] auf dem Stack).
 *
 *          Idee: Die unteren STACK_GUARD_SIZE Bytes des Stack-Bereichs werden
 *          beim Start mit einem Muster gefuellt. Solange der Stack nur bis
 *          Stack_Mem + STACK_GUARD_SIZE benutzt wird, bleibt das Muster heil.
 *          Sobald SP tiefer sinkt (Overflow), wird das Muster zerstoert und
 *          stack_guard_check() meldet false.
 *
 *          Stack_Mem ist das Label der STACK-AREA in startup_stm32f429xx.s.
 *          WICHTIG: Dort muss es exportiert werden (EXPORT Stack_Mem, eine
 *          Zeile im STACK-AREA-Block) -- sonst linkt dieses Modul nicht.
 *          Die Canary belegt den unteren Stack-Rand -- erkannter Overflow =
 *          Belegung > Stack_Size - STACK_GUARD_SIZE.
 *
 *          Nutzung:
 *            int main(void) {
 *               stack_guard_init();        // erstes Statement in main()
 *               ...
 *               for (;;) {
 *                  ...                     // z. B. pro Bild:
 *                  if (!stack_guard_check()) {
 *                     // LCD-Meldung + Halt (Stack-Overflow erkannt)
 *                  }
 *               }
 *            }
 ******************************************************************************
 */

#ifndef STACKGUARD_H
#define STACKGUARD_H

#include <stdbool.h>
#include <stdint.h>

/** Groesse der Canary am unteren Stack-Rand in Bytes.
 *
 *  Die Canary liegt in den unteren GUARD Bytes des Stack-Bereichs, deshalb:
 *    - Erkannt wird ein Overflow ab Belegung > Stack_Size - STACK_GUARD_SIZE
 *      (SP stoesst in die Canary vor).
 *    - Die Canary darf NICHT in den legitim belegten Bereich hineinragen,
 *      sonst Fehlalarm. Faustregel: Stack_Size muss groesser sein als die
 *      groesste Aufrufkette (im Map/axf nachmessen, hier ~990 B inkl. ISR).
 *  Aktuell: Stack_Size 0x800 (2048 B) mit GUARD=128 -> Alarm ab > 1920 B
 *  Belegung. Worst Case lt. axf ~990 B (Main ~600 B + USB-ISR ~392 B, mit
 *  pix_buf static sogar ~860 B nach static-Locals) -> Reserve ~2x, keine
 *  Fehlalarme; der Overflow des Incidents (~1248 B mit pix_buf auf dem
 *  Stack) waere sicher erkannt worden. RAM: .bss ~68 KB + Stack 2 KB +
 *  Heap 2 KB < 128 KB (SRAM1+2 bis 0x20020000). */
#define STACK_GUARD_SIZE  128u

/**
 * Traegt das Canary-Muster am unteren Stack-Rand ein.
 *  erstes Statement in main() aufrufen (zu diesem Zeitpunkt ist der Stack
 *  oben bereits so wenig belegt, dass die Canary unten noch heil ist).
 */
void stack_guard_init(void);

/**
 * Prueft die Canary am unteren Stack-Rand.
 *  @return true: Muster intakt (kein Overflow erkannt);
 *          false: Muster zerstoert -- der Stack ist ueber die Unterkante
 *                 hinausgelaufen (bzw. bis in die Canary vorgedrungen)
 */
bool stack_guard_check(void);

#endif /* STACKGUARD_H */
