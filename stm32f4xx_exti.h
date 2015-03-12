#pragma once

#include <stdint.h>

/* Reset and Clock Control Registers, see User's Manual section 6.3.X */
volatile typedef struct
{
	uint32_t IMR;    /* Interrupt Mask Register */
	uint32_t EMR;    /* Event Mask Register */
	uint32_t RTSR;   /* Rising Edge Trigger Selection Register */
	uint32_t FTSR;   /* Falling Edge Trigger Selection Register */
	uint32_t SWIER;  /* Software Interrupt Event Register */
	uint32_t PR;     /* Event pending Register */
} EXTI_TypeDef;

#define EXTI_BASE     (0x40013C00)
#define EXTI          ((EXTI_TypeDef*)EXTI_BASE)

#define EXTI_IMR_MR0  (0x01)   /* Enable PORTx Pin 0 Interrupts */
#define EXTI_FTSR_TR0  (0x01)   /* Trigger Pin 0 on falling edge */
#define EXTI_RTSR_TR0	(0x01)	/* Trigger Pin 1 on rising edge */
#define EXTI_SWIER_SWIER0  (0x01)   /* Software interrupt/event generation on Pin 0 */
#define EXTI_PR_PR0   (0x01)   /* flag in pending register for interrupt/event pending on Pin 0 */

