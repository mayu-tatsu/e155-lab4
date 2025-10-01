// main.c
// Mayu Tatsumi; mtatsumi@g.hmc.edu
// 2025-9-29

#include "notes.h"
#include "STM32L432KC_FLASH.h"
#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM23.h"
#include "STM32L432KC_TIM1516.h"

#define SPEAKER_PIN 2           // output pin for TIM15_CH1 (note freq)

int main(void) {
	
  configureFlash();
  configureClock();
  RCC->APB1ENR1 |= (1 << 0);    // enable TIM2  (note length)
  RCC->APB2ENR  |= (1 << 16);   // enable TIM15 (note freq)
  RCC->APB2ENR  |= (1 << 0);    // enable GPIOA for TIM15

  initTIM23(TIM2);              // PWM for duration
  initTIM1516(TIM15);           // note frequency

  pinMode(SPEAKER_PIN, GPIO_ALT);     // set pin 2 to alternate function mode
  GPIO->AFRL |= (0b1110 << 8);        // enable AF14 (1110) for GPIOB (pin 2: 8-11)

  for (volatile uint32_t i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {
    speaker_freq(TIM2, notes[i][0]);
    delay_ms(TIM15, notes[i][1]);
  }
}