#include "calculations.h"
#include "encoder.h"

#define PHASE_ANGLE 0.3
#define MICROSECONDS_PER_SECOND 1000000.0

static Phase_count old_phase_count = {.count = 0, .timestamp = 0};

void calculate(Angular_values *values) {
   Phase_count phase_count = get_phase_count();
   values->angle = phase_count.count * PHASE_ANGLE;

   values->speed =
       (phase_count.count - old_phase_count.count) * PHASE_ANGLE /
       ((phase_count.timestamp - (double)old_phase_count.timestamp) /
        MICROSECONDS_PER_SECOND);
   old_phase_count = phase_count;
}
