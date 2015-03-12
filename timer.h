/*
 * timer.h contains routines for initializing and setting TIM3 interrupts
 *
 * Intended for debouncing
 */
#pragma once

#include "stdint.h"

/*
 * init function
 *
 * sets ARR and enables interrupts, and sets callback function
 *
 * time input should to be less then or equal to 0xffff (65535)
 */
void timer3_init(void(*timer3_callback)(void), uint32_t time);

/*
 * start timer
 *
 * clears count and enables timer
 */
void timer3_start( void );

/*
 * stop timer
 */
void timer3_disable( void );
