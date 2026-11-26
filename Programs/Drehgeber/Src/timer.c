#include "timer.h"
#include "stm32f429xx.h"

#define TIMER_PRESCALER 89U
#define MICROSECONDS_PER_MILLISECOND 1000.0
#define MICROSECONDS_PER_SECOND 1000000.0
#define MICROSECONDS_PER_MINUTE 60000000.0

void init_timer() {          
   RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // reset and clock control
   TIM5->CR1 &= ~TIM_CR1_CEN;          // timer stoppen

   TIM5->PSC = TIMER_PRESCALER;
   TIM5->ARR = UINT32_MAX;
   TIM5->EGR |= TIM_EGR_UG;

   TIM5->CNT = 0;
   TIM5->SR |= ~TIM_SR_UIF;
   TIM5->CR1 |= TIM_CR1_CEN;           // timer starten
}

void reset_timer() { TIM5->CNT &= 0U; } // Setzt den Timer auf 0

double time(time_unit unit) {
   uint32_t t = TIM5->CNT;
   switch (unit) {                        // Gibt die Zeit in der gewünschten einheit
   case US:
      return (double)t;
   case MS:
      return t / MICROSECONDS_PER_MILLISECOND;
   case S:
      return t / MICROSECONDS_PER_SECOND;
   case MIN:
      return t / MICROSECONDS_PER_MINUTE;
   default:
      return -1;
   }
}
