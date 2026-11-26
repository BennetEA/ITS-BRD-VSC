#ifndef ENCODER_U
#define ENCODER_U
#include "exception.h"
#include "phase.h"

typedef struct {
   int32_t count;       // Wie viele Drehschritte bisher gezählt wurden
   uint32_t timestamp;  // Der Zeitpunkt der letzten Auswertung.
} Phase_count;

Exception update_encoder(Phase new_phase);
Exception init_encoder(Phase phase);
Phase_count get_phase_count();
#endif // !ENCODER_U
