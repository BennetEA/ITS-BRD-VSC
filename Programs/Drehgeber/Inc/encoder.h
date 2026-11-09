#ifndef ENCODER_U
#define ENCODER_U
#include "exception.h"
#include "phase.h"

typedef struct {
   int32_t count;
   uint32_t timestamp;
} Phase_count;

Exception update_encoder(Phase new_phase);
Exception init_encoder(Phase phase);
Phase_count get_phase_count();
#endif // !ENCODER_U
