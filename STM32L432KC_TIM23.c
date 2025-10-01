// STM32L432KC_TIM23.c
// Mayu Tatsumi; mtatsumi@g.hmc.edu
// 2025-9-30

#include "STM32L432KC_TIM23.h"

void initTIM23(TIM23_TypeDef* TIMX) {
  TIMX->PSC = TIM2_PSC;      // Set prescaler
  
  // Disabling slave mode
  TIMX->SMCR &= ~(    1 << 16);
  TIMX->SMCR &= ~(0b111 << 0);

  TIMX->CCR1 = 0x7FFF;            // Using CH1, set 50% duty cycle
  TIMX->CCMR1 &= ~(0b111 << 4);   // Cleaning
  TIMX->CCMR1 |=  (0b110 << 4);   // Set PWM mode 1
  TIMX->CCMR1 |=  (1     << 3);   // Enable CH1 preload register
  TIMX->CR1   |=  (1     << 7);   // Enable auto-reload preload

  TIMX->ARR  = 0xFFFF;        // Max ARR to ensure no event spamming
  TIMX->EGR |= (1 << 0);      // Generates event to reinitialize counter
  TIMX->CR1 |= (1 << 0);      // Enable counter
  TIMX->CNT  = 0;             // Reset counter to 0

  TIMX->CCER |= (1 << 0);     // Enable CH1 output
}

void speaker_freq(TIM23_TypeDef* TIMX, uint32_t freq) {
  if (freq == 0) {
    TIMX->ARR  = 0x0001;
    TIMX->CCR2 = 0;
  } else {
    volatile uint32_t arr_val = (80000000 / TIM2_PSC / freq)-1;   // find new ARR value
    TIMX->ARR   = arr_val;
    TIMX->CCR1  = arr_val / 2;                   // creates 50% duty cycle
    TIMX->EGR  |= (1 << 0);                      // update
  }
}