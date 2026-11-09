#include "calculations.h"
#include "encoder.h"

#define PHASE_ANGEL 0.3

static Phase_count old_phase_count = {.count = 0, .timestamp = 0};

void calculate(double *speed, double *angel) {
   Phase_count phase_count = get_phase_count();
   *angel = phase_count.count * PHASE_ANGEL;

   *speed = (phase_count.count - old_phase_count.count) * PHASE_ANGEL /
            ((phase_count.timestamp - old_phase_count.timestamp) / 1000000.0);
   old_phase_count = phase_count;
}
