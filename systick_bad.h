/*
 * systick.h - routines for initializing and handling systick interrupt
 */
#pragma once

#include "stdint.h"       /* define uint16_t, etc... */

#define CS_reg			(0xE000E010)
#define RV_reg			(0xE000E014)
#define CV_reg			(0xE000E018)

/*
 * Initialize systick interrupt handler
 */
void systick_init(void(*systick_callback_fn)(void));

/*
 * systick_start( uint32_t secs);
 *
 * loads and then starts systick timer with argument in seconds
 */
void systick_start( uint32_t secs);

/*
 * void systick_stop( void );
 *
 * disables systick timer and sets current value to zero
 */
void systick_stop( void );

/*
 * void LED_update(uint32_t LED)
 *
 * Update LED states based on value of LED.
 * LED should be set using LED_<color>_ON or LED_<color>_OFF #defines
 */
void systick_handler( void );
