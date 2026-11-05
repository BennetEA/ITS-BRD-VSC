#include "timer.h"
#include "stm32f429xx.h"

void init_timer() {
   RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // reset and clock control
   TIM5->CR1 &= ~TIM_CR1_CEN;          // timer stoppen

   TIM5->PSC = 89;
   TIM5->ARR = 0xFFFFFFFFU;
   TIM5->EGR |= TIM_EGR_UG;

   TIM5->CNT &= 0;
   TIM5->SR |= ~TIM_SR_UIF;
   TIM5->CR1 |= TIM_CR1_CEN; // timer starten
}

void reset_timer() { TIM5->CNT &= 0; }

double time(time_unit unit) {
   uint32_t t = TIM5->CNT;
   switch (unit) {
   case US:
      return (double)t;
   case MS:
      return t / 1000.0;
   case S:
      return t / 1000000.0;
   case MIN:
      return t / 60000000.0;
   default:
      return -1;
   }
}
