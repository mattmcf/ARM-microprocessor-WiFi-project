/*
 * Timer.h contains routines for initializing and changing timer alerts
 */
#pragma once

#include "stdint.h"

/*
 * Initializes TIM4 for PWM mode output on GPIOB Pin 6
 */
void servo_init( void );

/*
 * Moves servo to corresponding angle to argument (0x000 - 0xFFF)
 */
void servo_change( uint32_t val );

/*
 * closes gate
 */
void servo_closegate( void );

/*
 * opens gate
 */
void servo_opengate( void );

/*
 * maps ADC signal to servo position (0-90 degrees)
 * Input range: (0x000 - 0xFFF)
 */
void servo_mapADC( uint32_t val );


/*
 * initializes TIM2_CH3 to a PWM mode output of 50% duty cycle at 10 Hz
 */
void TIM2_init( void );

/*
 * starts timer 2
 */
void TIM2_start( void );

/*
 * disables timer 2
 */
void TIM2_disable( void );
