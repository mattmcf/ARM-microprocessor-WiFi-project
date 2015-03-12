/*
 * ADC.h provides templates for routines involving ADC modules
 */
#pragma once

#include "stm32f4xx_ADC.h"
#include "stdint.h"

/*
 * void ADC_int(void)
 *
 * initializes ADC1 unit to read analog readings of off PA1
 *
 * also enables ADC1 EOC interrupts when conversion finishes
 */
void ADC_init( void(*ADC_callback_fn)(uint16_t *, uint32_t ));

/*
 * uint32_t ADC_read( void );
 *
 * Reads ADC1 value and returns reading as uint32_t
 */
uint32_t ADC_read( void );

/*
 * Starts ADC conversion
 */
void ADC_start( void );
