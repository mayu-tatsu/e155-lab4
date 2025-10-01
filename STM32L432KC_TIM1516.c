// STM32L432KC_TIM1516.c
// Mayu Tatsumi; mtatsumi@g.hmc.edu
// 2025-9-30

#include "STM32L432KC_TIM1516.h"

void initTIM1516(TIM1516_TypeDef* TIMX) {

  TIMX->PSC = TIM15_PSC;      // Set prescaler
  
  // Disabling slave mode
  TIMX->SMCR &= ~(    1 << 16);
  TIMX->SMCR &= ~(0b111 << 0);

  TIMX->ARR = 0xFFFF;         // Max ARR to ensure no event spamming
  TIMX->EGR |= (1 << 0);      // Generates event to reinitialize counter
  TIMX->CR1 |= (1 << 0);      // Enable counter
  TIMX->CNT = 0;              // Reset counter to 0
}

void delay_ms(TIM1516_TypeDef* TIMX, uint32_t ms) {
  volatile uint32_t duration = ms * 80000 / (TIM15_PSC + 1);  // convert to ARR val given input clk+psc
  
  TIMX->EGR |=  (1 << 0);       // reset main counter via event flag
  TIMX->ARR  = duration;
  TIMX->SR  &= ~(1 << 0);       // clear update interrupt flag
  while((TIMX->SR & 1) == 0){};
}