#include "phase.h"
#include "stm32f429xx.h"
Phase read_phase() {
   Phase phase;

   phase.value = ~GPIOF->IDR & 0b11U;  //WICHTIG
   phase.time = TIM5->CNT;             //Zählerstand auslesen (?CNT?)          

   return phase;
}
