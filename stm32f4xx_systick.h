#pragma once

#include "stdint.h"

/* USART Registers, see the reference manual sections 26.6.X */
volatile typedef struct
{
	uint32_t CTRL;			/* Control Register - offset 0x00 */
	uint32_t LOAD;			/* Reload value		- offset 0x04 */
	uint32_t VAL;			/* Current value	- offset 0x08 */
	uint32_t CALIB;			/* Ten MS			- offset 0x0c */
} systick_TypeDef;

/*
 * USARTs
 */
#define SYSTICK_BASE		(0xE000E010)
#define SYSTICK				((systick_TypeDef*)SYSTICK_BASE)
