#ifndef PHASE_U
#define PHASE_U
#include <stdint.h>

typedef struct {
   uint8_t value;    // Aktueller Zustand der beiden Drehgebersignale
   uint32_t time;    // Zeitpunkt der Messung
} Phase;

Phase read_phase();

#endif // !PHASE_U
