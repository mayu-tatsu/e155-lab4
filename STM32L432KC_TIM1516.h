// STM32L432KC_TIM1516.h
// Mayu Tatsumi; mtatsumi@g.hmc.edu
// 2025-9-30

// Header file for onboard timers 15 and 16.
// Contains functions to initialize and delay any other
// updates in units of milliseconds, effectively
// lengthening any notes already being played by the 
// speaker.

#ifndef STM32L4_TIM1516_H
#define STM32L4_TIM1516_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base Addresses
#define TIM15_BASE (0x40014000UL)
#define TIM16_BASE (0x40014400UL)

#define TIM15_PSC  (20)

typedef struct {
  __IO uint32_t CR1;        /*!< TIM1516 control register 1,              Address Offset: 0x00 */
  __IO uint32_t CR2;        /*!< TIM1516 control register 2,              Address Offset: 0x04 */
  __IO uint32_t SMCR;       /*!< TIM1516 slave mode control register,     Address Offset: 0x08 */
  __IO uint32_t DIER;       /*!< TIM1516 DMA/Interrupt enable register,   Address Offset: 0x0C */
  __IO uint32_t SR;         /*!< TIM1516 status register,                 Address Offset: 0x10 */
  __IO uint32_t EGR;        /*!< TIM1516 event generation register,       Address Offset: 0x14 */
  __IO uint32_t CCMR1;      /*!< TIM1516 capture/compare mode register 1, Address Offset: 0x18 */
  __IO uint32_t RESERVED0;  /*!< Reserved,                                Address Offset: 0x1C */
  __IO uint32_t CCER;       /*!< TIM1516 capture/compare enable register, Address Offset: 0x20 */
  __IO uint32_t CNT;        /*!< TIM1516 counter,                         Address Offset: 0x24 */
  __IO uint32_t PSC;        /*!< TIM1516 prescalar,                       Address Offset: 0x28 */
  __IO uint32_t ARR;        /*!< TIM1516 auto-reload register,            Address Offset: 0x2C */
  __IO uint32_t RCR;        /*!< TIM1516 repetition counter register,     Address Offset: 0x30 */
  __IO uint32_t CCR1;       /*!< TIM1516 capture/compare register 1,      Address Offset: 0x34 */
  __IO uint32_t CCR2;       /*!< TIM1516 capture/compare register 2,      Address Offset: 0x38 */
  uint32_t      RESERVED1;  /*!< Reserved,                                Address Offset: 0x3C */
  uint32_t      RESERVED2;  /*!< Reserved,                                Address Offset: 0x40 */
  __IO uint32_t BDTR;       /*!< TIM1516 break and dead-time register,    Address Offset: 0x44 */
  __IO uint32_t DCR;        /*!< TIM1516 DMA control register,            Address Offset: 0x48 */
  __IO uint32_t DMAR;       /*!< TIM1516 DMA address for full transfer,   Address Offset: 0x4C */
  __IO uint32_t OR1;        /*!< TIM1516 option register 1,               Address Offset: 0x50 */
  uint32_t      RESERVED3;  /*!< Reserved,                                Address Offset: 0x54 */
  uint32_t      RESERVED4;  /*!< Reserved,                                Address Offset: 0x58 */
  uint32_t      RESERVED5;  /*!< Reserved,                                Address Offset: 0x5C */
  __IO uint32_t OR2;        /*!< TIM23 option register 2,               Address Offset: 0x60 */
} TIM1516_TypeDef;

#define TIM15 ((TIM1516_TypeDef*) TIM15_BASE)
#define TIM16 ((TIM1516_TypeDef*) TIM16_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initTIM1516(TIM1516_TypeDef* TIMX);
void delay_ms(TIM1516_TypeDef* TIMX, uint32_t ms);

#endif