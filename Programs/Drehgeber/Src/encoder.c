#include "encoder.h"
#include "led.h"
#include "phase.h"

static Phase_count phase_count = {.count = 0, .timestamp = 0};
static Phase old_phase = {.value = 0, .time = 0};

Exception update_encoder(Phase new_phase) {
   uint8_t a = old_phase.value;
   uint8_t b = new_phase.value;
   uint8_t c = a ^ b;

   phase_count.timestamp = new_phase.time;
   old_phase = new_phase;

   if (c == 0b11) {
      return ERR_PHASE_SKIP;
   }

   if (c == 0b00) {
      return ERR_OK;
   }

   if (((a & 1U) ^ ((b >> 1) & 1U)) == 0) {
      phase_count.count += 1;
      set_led(23);
      unset_led(22);
   } else {
      phase_count.count -= 1;
      set_led(22);
      unset_led(23);
   }
   return ERR_OK;
}

Exception init_encoder(Phase phase) {
   phase_count.count = 0;
   phase_count.timestamp = 0;

   old_phase = phase;
   return ERR_OK;
}
Phase_count get_phase_count() { return phase_count; }
