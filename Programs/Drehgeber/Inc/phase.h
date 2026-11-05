#ifndef PHASE_U
#define PHASE_U
#include <stdint.h>

typedef struct {
   uint8_t value;
   uint32_t timestamp;
} Phase;

Phase read_phase();

#endif // !PHASE_U
