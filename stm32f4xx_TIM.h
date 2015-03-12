#pragma once

#include "stdint.h"

/* TIM 2-5 STRUCTURE */
volatile typedef struct
{
	uint32_t CR1;						/* control Register 1				- offset 0x00 */
	uint32_t CR2;						/* Control Register 2				- offset 0x04 */
	uint32_t SMCR;						/* Slave Mode Control Register		- offset 0x08 */
	uint32_t DIER;						/* DMA/Interrupt Enable Register	- offset 0x0C */
	uint32_t SR;						/* Status Register					- offset 0x10 */
	uint32_t EGR;						/* Event Generation Register		- offset 0x14 */
	uint32_t CCMR1;						/* Capture/Compare Mode Register 1	- offset 0x18 */
	uint32_t CCMR2;						/* Capture/Compare Mode Register 1	- offset 0x1C */
	uint32_t CCER;						/* Capture/Compare Enable Register	- offset 0x20 */
	uint32_t CNT;						/* Counter							- offset 0x24 */
	uint32_t PSC;						/* Prescalar						- offset 0x28 */
	uint32_t ARR;						/* Automatic Reload Register		- offset 0x2C */
	uint32_t reserved1;
	uint32_t CCR1;						/* Capture/Compare Register 1		- offset 0x34 */
	uint32_t CCR2;						/* Capture/Compare Register 2		- offset 0x38 */
	uint32_t CCR3;						/* Capture/Compare Register 3		- offset 0x3C */
	uint32_t CCR4;						/* Capture/Compare Register 4		- offset 0x40 */
	uint32_t reserved2;
	uint32_t DCR;						/* DMA Control Register				- offset 0x48 */
	uint32_t DMAR;						/* DMA Address For Full Transfer	- offset 0x4C */
	uint32_t TIME2_OR;					/* TIM2 Option Register				- offset 0x50 */
	//uint32_t TIME5_OR;					/* TIM5 Option Register				- offset 0x50 */
} TIM_TypeDef;

/* See datasheet for memory map / base addresses */

/*
 * TIM4
 */
#define TIM2_base 		(0x40000000)
#define TIM2			((TIM_TypeDef*)TIM2_base)

#define TIM4_base		(0x40000800)
#define TIM4			((TIM_TypeDef*)TIM4_base)

#define TIM3_base		(0x40000400)
#define TIM3			((TIM_TypeDef*)TIM3_base)

#define TIMx_CCMR1_OCM1_MASK	0x60	/* Set TIM to PWM mode 1 */
#define TIMx_CCER_CC1E_MASK		0x01	/* Set output of CCER */

#define TIMx_CCMR2_OCM3_MASK	0x60	/* set TIMx_CH3 to PWM mode 1 */
#define TIMx_CCER_CC3E_MASK		0x100	/* enable CC 3 */


#define TIMx_CR1_CEN_MASK		0X01			/* Enable timer */
#define TIMx_CR1_DES_MASK		0xfffffffe		/* disable timer */
#define TIMx_CR1_CDES_MASK		0xfffffffe	/* Disable timer */
#define TIMx_DIER_UIE_MASK		0x01		/* Enable Update Event Interrupts */
#define TIMx_SR_UID_MASK		0xfffffffe	/* clear update interrupt flag */


