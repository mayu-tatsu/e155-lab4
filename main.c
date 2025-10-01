// main.c
// Mayu Tatsumi; mtatsumi@g.hmc.edu
// 2025-9-29

#include "notes.h"
#include "STM32L432KC_FLASH.h"
#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
// #include "STM32L432KC_TIM23.h"
#include "STM32L432KC_TIM1516.h"

#define SPEAKER_PIN 6           // output pin for TIM16_CH1 (note freq)

int main(void) {
	
  configureFlash();
  configureClock();
  RCC->APB2ENR |= (1 << 17);    // enable TIM16 (note freq)
  RCC->APB2ENR |= (1 << 16);    // enable TIM15 (note length)
  RCC->AHB2ENR |= (1 << 0);     // enable GPIOA for TIM15

  initTIM1516_PWM(TIM16);       // PWM for frequency
  initTIM1516(TIM15);           // note length

  pinMode(SPEAKER_PIN, 2);     // set pin 2 to alternate function mode
  GPIO->AFRL |= (0b1110 << 24);       // enable AF14 (1110) for GPIOA (pin 6: 24-27)

  //while (1) {
  //  speaker_freq(TIM16, 250);
  //}

  for (volatile uint32_t i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {
    speaker_freq(TIM16, notes[i][0]);
    delay_ms(TIM15, notes[i][1]);
  }
}