#include "phase.h"
#include "stm32f429xx.h"

Phase read_phase() {
   Phase phase;

   phase.value = GPIOF->IDR & 0b11;
   phase.timestamp = TIM5->CNT;

   return phase;
}
